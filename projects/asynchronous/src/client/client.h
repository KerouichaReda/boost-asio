#ifndef CLIENT_H
#define CLIENT_H
#include <boost/asio.hpp>

#include "conf.h"
#include "session.h"
class Client {
 public:
  Client(boost::asio::io_context&, Conf&);
  ~Client();
  void run();

 private:
  boost::asio::io_context& ioc_;
  Conf& conf_;
  boost::asio::ip::tcp::resolver resolver_;
  boost::asio::ip::tcp::resolver::results_type ep_;
};

#endif  //! CLIENT_H