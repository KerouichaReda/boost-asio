#ifndef SERVER_H
#define SERVER_H
/// @brief Server Class
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>

#include "setting.h"
#include "talk_to_client.h"

class Server
{
public:
    Server(boost::asio::io_context& _io_context , Conf& _conf );
    
    //~Server();
    void run();

private:
    void accept_thread();
    void handle_clients_thread();

    /* data */
    boost::asio::io_context& io_context;
    Conf& conf_;
    clients_array clients_; ///< This is a private variable member
    std::recursive_mutex mutex_;
    
    
};

#endif //!SERVER_H
