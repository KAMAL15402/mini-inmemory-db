#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger {
private:
    std::ofstream logFile;
    std::mutex mtx;

public:
    Logger(const std::string& filename = "db.aof");
    ~Logger();

    void append(const std::string& command);
};
