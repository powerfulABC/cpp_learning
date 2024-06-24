#include <iostream>
#include <boost/asio.hpp>

#include "const.h"
#include "server.h"

int main()
{
    try{
        boost::asio::io_context ioc;
        Server server(ioc, SERVER_LISTENNING_PORT);
        ioc.run();
    }catch(std::exception& e)
    {
        log_error_message("Server running has exception. " + std::string(e.what()));
    }
}