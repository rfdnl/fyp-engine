#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <iostream>
#include <sstream>

class Logger{
    std::string INFO = "INFO";
    std::string WARN = "WARN";
    std::string ERROR = "ERROR";
    std::string CLASS_NAME = "Logger.cpp";
    std::string filename;
    std::ostringstream ss;
public:
    void Write(std::string logtype, std::string owner, std::ostream& ostr);
    Logger(const char* file = "log.txt");
    void Info(std::string owner, std::ostream& ostr);
    void Warn(std::string owner, std::ostream& ostr);
    void Error(std::string owner, std::ostream& ostr);

    void Write(std::string logtype, std::string owner, std::string msg);
    void Info(std::string owner, std::string msg);
    void Warn(std::string owner, std::string msg);
    void Error(std::string owner, std::string msg);
    void Close();
};

#endif // LOGGER_HPP
