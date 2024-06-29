#include <boost/asio.hpp>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <iostream>
#include <string>

int main()
{
    const std::string server_addr = "127.0.0.1";
    const short port = 8080;
    char buf[1025];
    
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::socket sock(ioc);
    sock.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(server_addr), port));
    
    // 发送
    Json::Value root;
    root["id"] = 1001;
    root["data"] = "hello server.";

    std::string send_message = root.toStyledString();
    sock.send(boost::asio::buffer(send_message));
    
    memset(buf, 0, sizeof(buf));
    std::size_t recv_len;
    std::string recv_message("");
    recv_len = sock.read_some(boost::asio::buffer(buf, 1024));
    recv_message = std::string(buf, recv_len);
    std::cout << "server say:\n";
    std::cout << recv_message;
}