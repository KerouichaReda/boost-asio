#ifndef CLIENT_H
#define CLIENT_H
#include <boost/asio.hpp>
#include <memory>
#include <set>
#include "conf.h"
#include "session.h"
class Client {
 public:
  Client(boost::asio::io_context&, Conf&);
  ~Client();
  void run();

 private:

    void create();
    void connect();
    void loop();
  boost::asio::io_context& ioc_;
  Conf& conf_;
  std::set<std::shared_ptr<Session>> set_;
};

#endif  //! SERVER_H