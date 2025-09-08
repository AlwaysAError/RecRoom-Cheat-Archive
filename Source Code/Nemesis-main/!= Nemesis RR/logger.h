#pragma once
#include <iostream>
#include <fstream>     
#include <mutex>
#include <filesystem>  
#include <string>   

// Make A Check For It so users dont have it unless u want to
namespace Log {
    std::mutex logMutex;
    bool logfileEnabled = true;


    void init() {
        std::lock_guard<std::mutex> guard(logMutex); 

        std::filesystem::path logPath("log.txt");
        std::filesystem::path prevLogPath("log-prev.txt");

        if (std::filesystem::exists(prevLogPath)) {
            std::filesystem::remove(prevLogPath);
        }


        if (std::filesystem::exists(logPath)) {
            std::filesystem::rename(logPath, prevLogPath);
        }
    }

    void writeToLogFile(const std::string& message) {
        std::lock_guard<std::mutex> guard(logMutex);
        std::ofstream logFile("log.txt", std::ios_base::app);
        if (logFile.is_open()) {
            logFile << message << std::endl;
            logFile.close();
        }
    }

    void logAsync(const std::string& prefixSymbol, const std::string& message) {
        std::lock_guard<std::mutex> guard(logMutex);

        if (logfileEnabled) {
            std::ofstream logFile("log.txt", std::ios_base::app);
            if (logFile.is_open()) {
                logFile << "[" + prefixSymbol + "] " + message << std::endl;
            }
        }

        std::cout << "[" << prefixSymbol << "] " << message << std::endl;
    }



    void error(const std::string& message) {

        logAsync("-", "Error: " + message);

    }

    void prod(const std::string& message) {
        logAsync(">>", "PROD LOG: " + message);
    }

    void debug(const std::string& message) {

        logAsync(">", "Debug: " + message);

    }

    void log(const std::string& message) {

        logAsync("+", "Log: " + message);

    }
}