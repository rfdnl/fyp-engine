
#include "ILoggable.hpp"

void ILoggable::SetLog(Logger* logPtr, const char* owner){
    this->log = logPtr;
    this->owner = owner;
}

void ILoggable::INFO(std::ostream& ostr){
    log->Info(owner, ostr);
    ClearStream();
}

void ILoggable::INFO(const char* message){
    log->Info(owner, message);
}

void ILoggable::WARN(std::ostream& ostr){
    log->Warn(owner, ostr);
    ClearStream();
}

void ILoggable::WARN(const char* message){
    log->Warn(owner, message);
}

void ILoggable::ERROR(std::ostream& ostr){
    log->Error(owner, ostr);
    ClearStream();
}

void ILoggable::ERROR(const char* message){
    log->Error(owner, message);
}

void ILoggable::CloseLog(){
    log->Close();
    delete log;
}

void ILoggable::ClearStream(){
    ss.clear();
    ss.str(std::string());
}
