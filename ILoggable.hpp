#ifndef ILOGGABLE_HPP
#define ILOGGABLE_HPP
#include "Logger.hpp"
#include <sstream>
#include <iostream>

class ILoggable{
private:
    Logger* log;
    const char* owner;
protected:
    std::ostringstream ss;
    void SetLog(Logger* log, const char* owner);
    void INFO(std::ostream& ostr);
    void INFO(const char* message);
    void WARN(std::ostream& ostr);
    void WARN(const char* message);
    void ERROR(std::ostream& ostr);
    void ERROR(const char* message);
    void ClearStream();
    void CloseLog();
};

#endif // ILOGGABLE_HPP
