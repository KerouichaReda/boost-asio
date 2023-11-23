#include <iostream>
#include <boost/asio.hpp>
#include "client.h"
#include "conf.h"

int main(){
    boost::asio::io_context ioc_;
    Conf conf_;
    Client client_(ioc_,conf_);
    client_.run();
    return EXIT_SUCCESS;
}