#ifndef CLIENT_H
#define CLIENT_H
#include <boost/asio.hpp>
#include "session.h"
#include "conf.h"
class Client {
 public:
  Client(boost::asio::io_context&, Conf&);
  ~Client();
  void run();

 private:
  boost::asio::io_context& ioc_;
  boost::asio::ip::tcp::resolver resolver_;
  Conf& conf_;
};

#endif  //! CLIENT_H