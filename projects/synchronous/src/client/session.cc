#include "session.h"

Session::Session(boost::asio::io_context& ioc, Conf& conf)
    : sock_(ioc),
      ep_(boost::asio::ip::tcp::endpoint(
          boost::asio::ip::address::from_string(conf.server_address_),
          conf.server_port_)) {}

Session::~Session() {}

void Session::connect() { sock_.connect(ep_); }
void Session::write(const std::string& msg) {
  boost::system::error_code ec;
  boost::asio::write(sock_, boost::asio::buffer(msg), ec);
}
void Session::read() {
  already_read_ = sock_.read_some(boost::asio::buffer(buffer_));
  std::cout << std::string(buffer_, buffer_ + already_read_) << std::endl;
}