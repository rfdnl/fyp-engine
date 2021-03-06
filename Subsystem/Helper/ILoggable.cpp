#include "ILoggable.hpp"

ILoggable::ILoggable(std::shared_ptr<Logger> logPtr, std::string className):logPtr(logPtr), className(className){
	INFO(ss << CLASS_NAME << "(" << className << "), logPtr addr(" << logPtr.get() << "), count(" << logPtr.use_count() << ")");
}

ILoggable::~ILoggable(){
	INFO(ss << "~" << CLASS_NAME << "(" << className << "), logPtr addr(" << logPtr.get() << "), count(" << logPtr.use_count() << ")");
}

void ILoggable::INFO(std::ostream& ostr){
    logPtr.get()->Info(className, ostr);
    ClearStream();
}

void ILoggable::INFO(std::string message){
    logPtr.get()->Info(className, message);
}

void ILoggable::WARN(std::ostream& ostr){
    logPtr.get()->Warn(className, ostr);
    ClearStream();
}

void ILoggable::WARN(std::string message){
    logPtr.get()->Warn(className, message);
}

void ILoggable::ERROR(std::ostream& ostr){
    logPtr.get()->Error(className, ostr);
    ClearStream();
}

void ILoggable::ERROR(std::string message){
    logPtr.get()->Error(className, message);
}

void ILoggable::ClearStream(){
    ss.clear();
    ss.str(std::string());
}
