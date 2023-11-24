#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <boost/asio.hpp>
#include "conf.h"
#include "session.h"
class Server {
 public:
  Server(boost::asio::io_context& , Conf& );
    void run();

  ~Server();

 private:
    void listen();
    Conf& conf_;
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::acceptor acceptor_; 
    
};
#endif  //! SERVER_H