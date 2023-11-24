#include "session.h"
// Server session
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
  timer_.expires_after(session_lifetime_);
  if (!ec) {
    std::cout << "Read : " << buffer_ << std::endl;
    do_write();
  }
}
void Session::do_write() {
  boost::asio::async_write(
      sock_, boost::asio::buffer(buffer_),
      std::bind(&Session::on_write, shared_from_this(), std::placeholders::_1,
                std::placeholders::_2));
}
void Session::on_write(boost::system::error_code ec, std::size_t) {
  if (!ec) {
    buffer_.clear();
    do_read();
  }
}

void Session::stop(boost::system::error_code ec) {
  sock_.close(ec);
  timer_.cancel();
}
void Session::check_deadline(boost::asio::steady_timer& timer) {
  auto self(shared_from_this());
  timer_.async_wait([this, self, &timer](const boost::system::error_code& ec) {
    if (timer.expiry() <= boost::asio::steady_timer::clock_type::now()) {
      stop(ec);
    } else {
      check_deadline(timer);
    }
  });
}