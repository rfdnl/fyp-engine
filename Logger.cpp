#include "Logger.hpp"

void Logger::Write(std::string type, std::string className, std::string msg){
    ss << type << ":\t" << className << "\t:\t" << msg << std::endl;
}

void Logger::Info(std::string className, std::string msg){
    Write(INFO, className, msg);
}

void Logger::Warn(std::string className, std::string msg){
    Write(WARN, className, msg);
}

void Logger::Error(std::string className, std::string msg){
    Write(ERROR, className, msg);
}

void Logger::Write(std::string type, std::string className, std::ostream& ostr){
    Write(type, className, dynamic_cast<std::ostringstream&>(ostr).str());
}

void Logger::Info(std::string className, std::ostream& ostr){
    Write(INFO, className, ostr);
}

void Logger::Warn(std::string className, std::ostream& ostr){
    Write(WARN, className, ostr);
}

void Logger::Error(std::string className, std::ostream& ostr){
    Write(ERROR, className, ostr);
}

void Logger::Close(){
    std::ofstream outFile;
    outFile.open(filename);
    outFile << ss.str() << std::endl;
    outFile.close();
    ss.clear();
    ss.str(std::string());
}
