#include <boost/asio.hpp>
#include <json/value.h>
#include <json/json.h>
#include <json/reader.h>

#include <memory>
#include <thread>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <unordered_set>
#include <chrono>

const short HEADER_LENGHT = 4;
const short MESSAGE_ID_LENGHT = 2;
const short MESSAGE_SIZE_LENGHT = 2;

void server(boost::asio::io_context& ioc, short port);
void session(std::shared_ptr<boost::asio::ip::tcp::socket> sock);

std::unordered_set<std::shared_ptr<std::thread>> threads;

int main()
{
    try{
        boost::asio::io_context ioc;
        server(ioc, 8080);

        for (auto& t : threads)
        {
            t->join();
        }
    }catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void server(boost::asio::io_context& ioc, short port)
{
    boost::asio::ip::tcp::endpoint server_endpoint(boost::asio::ip::tcp::v4(), port);
    boost::asio::ip::tcp::acceptor acc(ioc, server_endpoint);
    for (;;)
    {
        std::shared_ptr<boost::asio::ip::tcp::socket> sock = std::make_shared<boost::asio::ip::tcp::socket>(ioc);
        acc.accept(*sock);
        std::shared_ptr<std::thread> t = std::make_shared<std::thread>(session, sock);
        threads.insert(t);
    }
}

void session(std::shared_ptr<boost::asio::ip::tcp::socket> sock)
{
    try{
        for (;;)
        {
            // read header
            short message_id{0};
            short message_size{0};
            char buf[4];

            boost::system::error_code ec;
            std::memset(buf, 0, sizeof(buf));
            int read_len = boost::asio::read(*sock, boost::asio::buffer(buf, HEADER_LENGHT), ec);
            if (ec == boost::asio::error::eof)
            {
                std::cout << "remote closed." << std::endl;
                sock->close();
                break;
            }
            
            // message id
            std::memcpy(&message_id, buf, MESSAGE_ID_LENGHT);
            
            // message size
            std::memcpy(&message_size, buf + MESSAGE_ID_LENGHT, MESSAGE_SIZE_LENGHT);
            
            // transfer 
            message_id = boost::asio::detail::socket_ops::network_to_host_short(message_id);
            message_size = boost::asio::detail::socket_ops::network_to_host_short(message_size);

            // read data
            char *data = new char[message_size+1];
            std::memset(data, 0, message_size + 1);
            
            boost::asio::read(*sock, boost::asio::buffer(data, message_size));
            

            printf("received message: %s", data);


            // send data
            Json::Value root;
            root["id"] = message_id;
            root["data"] = "hello client.";
            std::string send_message = root.toStyledString();    
            
            short send_message_size = send_message.size();
            short send_message_id = message_id;
            char* send_data = new char[send_message_size + HEADER_LENGHT + 1];
            std::memset(send_data, 0, send_message_size);

            // transfer
            send_message_size = boost::asio::detail::socket_ops::host_to_network_short(send_message_size);
            send_message_id = boost::asio::detail::socket_ops::host_to_network_short(send_message_id);

            // fill buf
            std::memcpy(send_data, &send_message_id, MESSAGE_ID_LENGHT);
            std::memcpy(send_data + MESSAGE_ID_LENGHT, &send_message_size, MESSAGE_SIZE_LENGHT);
            std::memcpy(send_data + HEADER_LENGHT, send_message.c_str(), send_message.size());
            
            boost::asio::write(*sock, boost::asio::buffer(send_data, send_message.size() + HEADER_LENGHT));


            delete[] data;
            delete[] send_data;
            data = nullptr;
            send_data = nullptr;
        }
        sock->close();
    }catch(std::exception& e)
    {
        std::cerr << "Error. " << e.what() ;
    }
}
