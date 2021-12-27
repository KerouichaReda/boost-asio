/**
* \project server
* \file main.cpp
* contain the main function of 
*/
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>

#include "header_files/server.h"

int main(){
    Conf project_conf;    
    boost::asio::io_context ioc;
    Server server(ioc, project_conf);
    server.run();
    return EXIT_SUCCESS;
}




