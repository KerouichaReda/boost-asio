#ifndef SESSION_H
#define SESSION_H
#include <boost/asio.hpp>
#include <memory>

#include "conf.h"
#include "session.h"

class Session : std::enable_shared_from_this<Session> {
 public:
  Session(boost::asio::io_context&, Conf&);
  ~Session();
  void run();

 private:
  void do_read();
  void on_read(const boost::system::error_code& ec, std::size_t bytes);
  void do_write();
  void on_write(const boost::system::error_code& ec, std::size_t bytes);
  void do_connect();
  void on_connect(const boost::system::error_code& ec);
  void close(const boost::system::error_code& ec);
  boost::asio::ip::tcp::socket sock_;
  boost::asio::ip::tcp::resolver::results_type ep_;
  boost::asio::io_context& ioc_;
    std::string buffer_;

};

#endif  //! SESSION_H