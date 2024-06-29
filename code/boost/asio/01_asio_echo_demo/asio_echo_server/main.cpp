#include <boost/asio.hpp>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <iostream>
#include <cstdio>
#include <string>

int main()
{
    const short port = 8080;
    boost::system::error_code ec;
    char buf[1025];
    boost::asio::io_context ioc;
    
    boost::asio::ip::tcp::socket sock(ioc);
    boost::asio::ip::tcp::acceptor acc(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
    acc.accept(sock, ec);

    // read
    memset(buf, 0, sizeof(buf));
    std::size_t recv_len;
    std::string recv_message(""); 
    printf("client say:\n");
    while((recv_len = sock.read_some(boost::asio::buffer(buf, 1024))) > 0)
    {
        std::string str(buf);
        recv_message += str;
        printf("%s", buf);
    }

    printf("send to server:\n");
    sock.send(boost::asio::buffer(recv_message.c_str(), recv_message.size()));

    printf("send over");
}