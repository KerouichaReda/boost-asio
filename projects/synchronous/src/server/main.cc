
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>


#include "conf.h"
#include "server.h"

int main(){
    Conf conf_;    
    boost::asio::io_context ioc;
    Server server(ioc, conf_);
    server.run();
    return EXIT_SUCCESS;
}




