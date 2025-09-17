#pragma once
#include "storage.hpp"
#include <atomic>
#include <thread>
#include <vector>

class Server {
private:
    int server_fd;
    int port;
    Storage& store;
    std::atomic<bool> running{true};

    std::vector<std::thread> threads; // track client threads

    void handleClient(int client_fd);  // handle single client

public:
    Server(int port, Storage& s);
    ~Server();

    void start();
    void stop();
};
