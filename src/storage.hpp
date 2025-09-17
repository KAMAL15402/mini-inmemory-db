#ifndef STORAGE_HPP
#define STORAGE_HPP
#pragma once
#include <unordered_map>
#include <string>
#include <optional>
#include <mutex>
#include "logger.hpp"

class Storage {
private:
    std::unordered_map<std::string, std::string> data;
    mutable std::mutex mtx;
    Logger logger; // new

public:
    Storage();
    bool set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool del(const std::string& key);

    void loadFromFile(const std::string& filename = "db.aof");
};

#endif