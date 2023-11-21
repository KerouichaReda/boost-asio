#ifndef SESSION_H
#define SESSION_H
#include <boost/asio.hpp>
#include <iostream>
#include <memory>

#include "conf.h"
class Session : public std::enable_shared_from_this<Session> {
 public:
  Session(boost::asio::io_context&, Conf&);
  ~Session();
  void connect();
  void write(const std::string& msg);
  void read();

 private:
  boost::asio::ip::tcp::endpoint ep_;
  boost::asio::ip::tcp::socket sock_;
  static constexpr std::size_t max_size_{1024};
  char buffer_[max_size_] = {};
  std::size_t already_read_{0};
};

#endif