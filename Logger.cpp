#include "Logger.hpp"

Logger::Logger(const char* file){
    filename = file;
    Info(CLASS_NAME, "Logger()");
}

void Logger::Write(std::string logtype, std::string owner, std::ostream& ostr){
    Write(logtype, owner, dynamic_cast<std::ostringstream&>(ostr).str());
}

void Logger::Info(std::string owner, std::ostream& ostr){
    Write(INFO, owner, ostr);
}

void Logger::Warn(std::string owner, std::ostream& ostr){
    Write(WARN, owner, ostr);
}

void Logger::Error(std::string owner, std::ostream& ostr){
    Write(ERROR, owner, ostr);
}

void Logger::Write(std::string logtype, std::string owner, std::string msg){
    ss << logtype << ":\t" << owner << ":\t" << msg << std::endl;
}

void Logger::Info(std::string owner, std::string msg){
    Write(INFO, owner, msg);
}

void Logger::Warn(std::string owner, std::string msg){
    Write(WARN, owner, msg);
}

void Logger::Error(std::string owner, std::string msg){
    Write(ERROR, owner, msg);
}

void Logger::Close(){
    std::ofstream log;
    log.open(filename);
    log << ss.str() << std::endl;
    log.close();
    ss.clear();
    ss.str(std::string());
}
