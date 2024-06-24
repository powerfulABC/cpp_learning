#include "const.h"
#include <iostream>

void log_error_message(const boost::system::error_code& code, const std::string& message)
{
    std::cout << "<Error> " << message << ". code: " << code.value() << ", message: " << code.message() << std::endl;
}

void log_error_message(const std::string &message)
{
    std::cout << "<Error> " << message << std::endl;
}

void log_message(const std::string & message)
{
    std::cout << "<Info> " << message << std::endl;
}
