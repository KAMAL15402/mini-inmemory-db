#include "storage.hpp"
#include "server.hpp"

int main() {
    Storage store;
    store.loadFromFile("db.aof");

    Server server(8080, store);
    server.start();

    return 0;
}
