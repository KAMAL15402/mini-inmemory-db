#include "storage.hpp"
#include <fstream>
#include <sstream>

Storage::Storage() : logger("db.aof") {}

bool Storage::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mtx);
    data[key] = value;
    logger.append("SET " + key + " " + value);
    return true;
}

std::optional<std::string> Storage::get(const std::string& key) const {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool Storage::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(mtx);
    size_t erased = data.erase(key);
    if (erased > 0) {
        logger.append("DEL " + key);
    }
    return erased > 0;
}

void Storage::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string cmd, key, value;
        iss >> cmd >> key;
        if (cmd == "SET") {
            iss >> value;
            data[key] = value;
        } else if (cmd == "DEL") {
            data.erase(key);
        }
    }
}
