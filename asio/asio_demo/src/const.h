#ifndef CONST_H_
#define CONST_H_

#include <string>
#include <boost/asio.hpp>

//> Message
// message id length
inline constexpr short MESSAGE_ID_LENGTH = 2;
// message data size length
inline constexpr short MESSAGE_SIZE_LENGTH = 2;
// message header
inline constexpr short HEADER_LENGTH = 4;

void log_error_message(const boost::system::error_code& code, const std::string& message);
void log_error_message(const std::string& message);
void log_message(const std::string& message);

#endif