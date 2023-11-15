
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>

#include "conf.h"
#include "client.h"

int main(){
    Conf conf_;    
    boost::asio::io_context ioc;
    Client client(ioc, conf_);
    client.run();
    return EXIT_SUCCESS;
}
