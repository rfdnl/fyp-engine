#ifndef ILOGGABLE_HPP
#define ILOGGABLE_HPP

#include "Logger.hpp"
#include <iostream>
#include <memory>

class ILoggable{
private:
    std::shared_ptr<Logger> logPtr;
    const std::string CLASS_NAME = "ILoggable";
    std::string className;
protected:
    std::ostringstream ss;

    ILoggable(std::shared_ptr<Logger> logPtr, std::string className);
    ~ILoggable();

    void INFO(std::ostream& ostr);
    void INFO(std::string message);
    void WARN(std::ostream& ostr);
    void WARN(std::string message);
    void ERROR(std::ostream& ostr);
    void ERROR(std::string message);
    void ClearStream();
};

#endif // ILOGGABLE_HPP
