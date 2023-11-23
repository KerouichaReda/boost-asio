#include <iostream>
#include <boost/asio.hpp>
#include "conf.h"
#include "server.h"

int main(){
    boost::asio::io_context ioc;
    Conf conf;
    Server server(ioc,conf);
    server.run();    
    return EXIT_SUCCESS;
}