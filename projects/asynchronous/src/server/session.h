#ifndef SESSION_H
#define SESSION_H
#include <boost/asio.hpp>
#include <memory>
#include "conf.h"

class Session : std::enable_shared_from_this<Session> {
 public:
  Session(boost::asio::ip::tcp::socket , const Conf);
    void run();
  ~Session();

 private:
    void do_read();
    void on_read(boost::system::error_code ec, std::size_t);
    void do_write();
    void on_write(boost::system::error_code ec, std::size_t);

    
    boost::asio::ip::tcp::socket sock_;
    boost::asio::steady_timer timer_;
    const Conf conf_;
    const std::chrono::seconds session_lifetime_;
    std::string buffer_;
    
};
#endif  //! SESSION_H