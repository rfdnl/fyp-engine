#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <sstream>
#include <iostream>

class Logger{
    const std::string INFO = "INFO";
    const std::string WARN = "WARN";
    const std::string ERROR = "ERROR";
    const char* CLASS_NAME = "Logger";

    std::ostringstream ss;
    std::string filename;
public:
    Logger(std::string filename):filename(filename){
        ss << "() " << filename << std::endl;
    }

    ~Logger(){
        ss << "~() " << filename << std::endl;
        Close();
    }

    void Write(std::string type, std::string className, std::string msg);
    void Info(std::string className, std::string msg);
    void Warn(std::string className, std::string msg);
    void Error(std::string className, std::string msg);

    void Write(std::string type, std::string className, std::ostream& ostr);
    void Info(std::string className, std::ostream& ostr);
    void Warn(std::string className, std::ostream& ostr);
    void Error(std::string className, std::ostream& ostr);
    void Close();
};

#endif // LOGGER_HPP
