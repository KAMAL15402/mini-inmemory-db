#include "server.hpp"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

Server::Server(int port, Storage& s) : port(port), store(s) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    stop();
}

void Server::start() {
    std::cout << "Server listening on port " << port << "...\n";
    while (running) {
        sockaddr_in client_addr{};
        socklen_t addrlen = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);
        if (client_fd < 0) {
            if (!running) break;
            perror("accept failed");
            continue;
        }

        // Launch a thread for this client
        threads.emplace_back(&Server::handleClient, this, client_fd);
    }

    // Join all client threads
    for (auto& t : threads) {
        if (t.joinable())
            t.join();
    }
}

void Server::handleClient(int client_fd) {
    char buffer[1024] = {0};
    int valread;

    while ((valread = read(client_fd, buffer, sizeof(buffer)-1)) > 0) {
        buffer[valread] = '\0';
        std::string input(buffer);
        std::istringstream iss(input);
        std::string cmd, key, value;
        iss >> cmd >> key >> value;

        std::string response;
        if (cmd == "SET") {
            store.set(key, value);
            response = "OK\n";
        } else if (cmd == "GET") {
            auto val = store.get(key);
            response = val.has_value() ? val.value() + "\n" : "NULL\n";
        } else if (cmd == "DEL") {
            response = store.del(key) ? "DELETED\n" : "NULL\n";
        } else if (cmd == "EXIT") {
            break; // close this client
        } else {
            response = "ERR unknown command\n";
        }

        send(client_fd, response.c_str(), response.size(), 0);
    }

    close(client_fd);
}

void Server::stop() {
    running = false;
    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
}
