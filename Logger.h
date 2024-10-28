#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Logger {
private:
    ofstream logFile;

public:
    Logger() {
        logFile.open("log.txt", std::ios::app);
        if (!logFile.is_open()) {
            cerr << "Error log.txt\n";
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }



    void log(const std::string &message) {
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }
};

extern Logger logger;

#endif  LOGGER_H
