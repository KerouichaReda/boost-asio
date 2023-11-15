#ifndef SERVER_H
#define SERVER_H
#include <boost/asio.hpp>
#include "conf.h"
class Server {
 public:
  Server(boost::asio::io_context&, Conf&); 
    void run() ;
 private:
    boost::asio::io_context& io_context_;
};

#endif  //! SERVER_H