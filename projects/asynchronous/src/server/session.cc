#include "session.h"

Session::Session(boost::asio::ip::tcp::socket sock, const Conf conf)
    : sock_(std::move(sock)),
      timer_(sock_.get_executor()),
      conf_(conf),
      session_lifetime_(conf.session_lifetime_) {}

Session::~Session() {}

void Session::run() { do_read(); }

void Session::do_read() {
  boost::asio::async_read_until(
      sock_, boost::asio::dynamic_buffer(buffer_), '\n',
      std::bind(&Session::on_read, shared_from_this(), std::placeholders::_1,
                std::placeholders::_2));
}
void Session::on_read(boost::system::error_code ec, std::size_t) {
  if (!ec) {
    do_write();
  }
}
void Session::do_write() {
  boost::asio::async_write(
      sock_, boost::asio::buffer(buffer_),
      std::bind(&Session::do_write, shared_from_this(), std::placeholders::_1,
                std::placeholders::_2));
}
void Session::on_write(boost::system::error_code ec, std::size_t) {
  if (!ec) {
    do_read();
  }
}