#include <boost/asio.hpp>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <string>
#include <memory>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>

const std::string server_addr = "127.0.0.1";
const short port = 8080;
const short HEADER_LENGHT = 4;
const short MESSAGE_ID_LENGHT = 2;
const short MESSAGE_SIZE_LENGHT = 2;
boost::asio::io_context ioc;
boost::asio::ip::tcp::endpoint server_end(boost::asio::ip::address::from_string(server_addr), port);
boost::asio::ip::tcp::socket sock(ioc);



int main()
{
    sock.connect(server_end);
    // send
    {
        printf("client send message begin.\n");
        short message_id{0};
        short message_size{0};
        std::string message;
        
        Json::Value root;
        root["id"] = 1001;
        root["data"] = "hello server.";
        
        message = root.toStyledString();
        message_id = root["id"].asInt();
        message_size = message.size();

       
        char * data = new char[message_size + HEADER_LENGHT + 1];
        std::memset(data, 0, message_size + HEADER_LENGHT + 1);
        
        message_id = boost::asio::detail::socket_ops::host_to_network_short(message_id);
        message_size = boost::asio::detail::socket_ops::host_to_network_short(message_size);

        std::memcpy(data, &message_id, MESSAGE_ID_LENGHT); 
        std::memcpy(data + MESSAGE_ID_LENGHT, &message_size, MESSAGE_SIZE_LENGHT);
        std::memcpy(data + HEADER_LENGHT, message.c_str(), message.size());

        boost::asio::write(sock, boost::asio::buffer(data, message.size() + HEADER_LENGHT));
        printf("client send message end.\n");
        delete [] data;
    }

    // read
    {
        printf("client read message begin.\n");
        short recv_message_id{0};
        short recv_message_size{0};
        boost::asio::read(sock, boost::asio::buffer(&recv_message_id, MESSAGE_ID_LENGHT));
        boost::asio::read(sock, boost::asio::buffer(&recv_message_size, MESSAGE_SIZE_LENGHT));
        recv_message_id = boost::asio::detail::socket_ops::network_to_host_short(recv_message_id);
        recv_message_size = boost::asio::detail::socket_ops::network_to_host_short(recv_message_size);
        char *recv_data = new char[recv_message_size+1];
        std::memset(recv_data, 0, recv_message_size + 1);
        boost::asio::read(sock, boost::asio::buffer(recv_data, recv_message_size));

        printf("server say: %s", recv_data);
        printf("client read message end.\n");
        delete[] recv_data;
    }

    sock.close();
    return 0;
}