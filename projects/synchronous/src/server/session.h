#ifndef SESSION_H
#define SESSION_H
#include <memory>
#include <chrono>
#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session> {
 public:
  Session(boost::asio::io_context& ioc);
  ~Session();
    boost::asio::ip::tcp::socket& sock();

    void answer();
    bool timed_out() const;
 private:
    boost::asio::ip::tcp::socket sock_;
    std::chrono::time_point<std::chrono::system_clock> last_ping_;
    static constexpr std::size_t max_size{1024};
    std::int8_t buffer_[max_size] = {};
    std::size_t already_read_{0};
};



#endif  //! SESSION_H