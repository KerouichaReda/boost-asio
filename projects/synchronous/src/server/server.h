#ifndef SERVER_H
#define SERVER_H
#include <boost/asio.hpp>
#include <mutex>
#include <set>
#include <thread>

#include "conf.h"
#include "session.h"
class Server {
 public:
  Server(boost::asio::io_context&, Conf&);
  void run();

private:
    void accept();
    void answer();

 private:
  boost::asio::io_context& ioc_;
    Conf conf_;
  std::set<std::shared_ptr<Session>> set_;
  std::mutex mutex_;
};

#endif  //! SERVER_H