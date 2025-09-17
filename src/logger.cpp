#include "logger.hpp"

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::app); // append mode
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::append(const std::string& command) {
    std::lock_guard<std::mutex> lock(mtx);
    if (logFile.is_open()) {
        logFile << command << std::endl;
    }
}
