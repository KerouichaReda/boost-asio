
#include "session.h"
Session::Session(boost::asio::io_context& ioc)
    : sock_(ioc), last_ping_(std::chrono::system_clock::now()) {}

boost::asio::ip::tcp::socket& Session::sock() { return sock_; }
void Session::answer() {
  if (sock_.available()) {
    already_read_ += sock_.read_some(
        boost::asio::buffer(buffer_ + already_read_, max_size - already_read_));
  }
  bool eos = std::find(buffer_, buffer_ + already_read_, '\n');
  if (!eos) {
    return;
  }
  last_ping_ = std::chrono::system_clock::now();
  std::string msg(buffer_, buffer_ + already_read_);
  sock_.write_some(boost::asio::buffer(msg));
  already_read_ = 0;
  std::fill(buffer_, buffer_ + max_size, 0x00);
}
Session::~Session() {}

bool Session::timed_out() const {
    return (std::chrono::system_clock::now() - last_ping_) > std::chrono::seconds(1);
}