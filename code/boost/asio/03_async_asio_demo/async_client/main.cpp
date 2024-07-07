#include <boost/asio.hpp>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <string>
#include <iostream>


const std::string server_address = "127.0.0.1";
const short port = 8080;
const short HEADER_LENGTH = 4;
const short MESSAGE_ID_LENGTH = 2;
const short MESSAGE_SIZE_LENGTH = 2;

// 读消息
std::string read_from_socket(boost::asio::ip::tcp::socket& sock);
// 送信
void send_to_socket(boost::asio::ip::tcp::socket& sock, std::string message, short message_id);

// 读消息头
void handle_read_header(boost::system::error_code ec, std::size_t bytes_tranferred, char* header, boost::asio::ip::tcp::socket& sock);

// 读消息体
void handle_read_data(boost::system::error_code ec, std::size_t bytes_tranferred, char* data);

int main()
{
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::endpoint server_ep(boost::asio::ip::address::from_string(server_address), port);
    boost::asio::ip::tcp::socket sock(ioc);

    boost::system::error_code ec;
    sock.connect(server_ep, ec);
    if (!ec)
    {
        std::cerr << "Error. Connnect to server failed. code: " << ec.value() << ". message: " << ec.what() << std::endl; 
        sock.close();
    }

    send_to_socket(sock, "hello, server.", 1001);
    std::string recv_message = read_from_socket(sock);
    sock.close();
}

void send_to_socket(boost::asio::ip::tcp::socket &sock, std::string message, short message_id)
{
    short message_length = message.size();

    // 开始封装消息
    char* data = new char(message_length + HEADER_LENGTH);

    // 转换为网络字节序
    message_id = boost::asio::detail::socket_ops::host_to_network_short(message_id);
    message_length = boost::asio::detail::socket_ops::host_to_network_short(message_length);

    // 填充消息
    std::memcpy(data, &message_id, MESSAGE_ID_LENGTH);
    std::memcpy(data + MESSAGE_ID_LENGTH, &message_length, MESSAGE_SIZE_LENGTH);
    std::memcpy(data + HEADER_LENGTH, message.c_str(), message.size());

    // 发送消息
    boost::system::error_code ec;
    sock.send(boost::asio::buffer(data, message.size() + HEADER_LENGTH));

    delete[] data;
}


void send_to_socket(boost::asio::ip::tcp::socket& sock, std::string message, short message_id)
{
    char* header = new char[HEADER_LENGTH];
    std::memset(header, 0, HEADER_LENGTH);
    // 注册异步事件 : 读消息头
    boost::asio::async_read(
        sock,
        boost::asio::buffer(header, HEADER_LENGTH),
        std::bind(handle_read_header, std::placeholders::_1, std::placeholders::_2, header, sock)
    );
}

// 读消息头
void handle_read_header(boost::system::error_code ec, std::size_t bytes_tranferred, char* header, boost::asio::ip::tcp::socket& sock)
{
    if (!ec)
    {
        // 从头部中取出消息id和消息体长度
        short message_id, message_length;
        std::memcpy(&message_id, header, MESSAGE_ID_LENGTH);
        std::memcpy(&message_length, header + MESSAGE_ID_LENGTH, MESSAGE_SIZE_LENGTH);

        message_id = boost::asio::detail::socket_ops::network_to_host_short(message_id);
        message_length = boost::asio::detail::socket_ops::network_to_host_short(message_length);
        
        char* data = new char[message_length + 1];
        std::memset(data, 0, message_length + 1);
        
        // 注册异步读事件： 读消息体
        boost::asio::async_read(
            sock,
            boost::asio::buffer(data, message_length),
            std::bind(handle_read_data, std::placeholders::_1, std::placeholders::_2, data)
        );

    }
    else{
        std::cerr << "Error occured when reading headers. code: " << ec.value() << ". message: " << ec.what();
        sock.close();
    }
}


void handle_read_data(boost::system::error_code ec, std::size_t bytes_tranferred, char* data)
{
    if (!ec)
    {
        printf("recv from server: %s\n", data);
    }
    else{
        std::cerr << "Error occured when reading headers. code: " << ec.value() << ". message: " << ec.what();
    }
}