#include "const.h"
#include <cstdio>

void log_error_message(const boost::system::error_code& code, const std::string& message)
{
    printf("<Error> %s. code: %d, message: %s", message.c_str(), code.value(), code.message().c_str());
}

void log_error_message(const std::string &message)
{
    printf("<Error> %s.", message.c_str());
}

void log_message(const std::string & message)
{
    printf("<Info> %s.", message.c_str());
}
