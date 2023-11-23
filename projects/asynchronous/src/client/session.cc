
#include "session.h"

Session::Session(boost::asio::io_context& ioc, Conf& conf)
    : sock_(ioc),
      ioc_(ioc),
      ep_(boost::asio::ip::tcp::resolver(ioc).resolve(
          conf.address_, std::to_string(conf.port_))) {}

Session::~Session() {}

void Session::do_read() {
  boost::asio::async_read_until(
      sock_, boost::asio::dynamic_buffer(buffer_), '\n',
      std::bind(&Session::on_read, shared_from_this(), std::placeholders::_1,
                std::placeholders::_2));
}
void Session::on_read(const boost::system::error_code& ec, std::size_t bytes) {
  if (!ec) {
    do_write();
  } else {
    close(ec);
  }
}
void Session::do_write() {
  std::string msg = "ping";
  boost::asio::async_write(
      sock_, boost::asio::buffer(msg),
      std::bind(&Session::on_write, shared_from_this(), std::placeholders::_1,
                std::placeholders::_2));
}
void Session::on_write(const boost::system::error_code& ec, std::size_t bytes) {
  if (!ec) {
    do_read();
  } else {
    close(ec);
  }
}
void Session::do_connect() {
  boost::asio::async_connect(sock_, ep_,
                             std::bind(&Session::on_connect, shared_from_this(),
                                       std::placeholders::_1));
}
void Session::on_connect(const boost::system::error_code& ec) {
  if (!ec) {
    do_write();
  } else {
    close(ec);
  }
}

void Session::close(const boost::system::error_code& ec) {
  boost::asio::post(ioc_, [this]() {
    boost::system::error_code ec;
    sock_.close(ec);
  });
}

void Session::run() { do_connect(); }