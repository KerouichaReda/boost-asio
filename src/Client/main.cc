#include<iostream>
#include<vector>
#include<string>

#include<boost/asio.hpp>

#include "header_files/talk_to_server.h"


int main(int argc, char* argv[]) { 
    boost::asio::io_context ioc;
    TalkToServer client(ioc,"reda","127.0.0.1",8001);
    client.run();

    return EXIT_SUCCESS;
}
