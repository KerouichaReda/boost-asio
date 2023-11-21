
#include "server.h"
Server::Server(boost::asio::io_context& ioc, Conf& conf)
    : ioc_(ioc), conf_(conf) {}

void Server::run() {
  std::vector<std::thread> threads;
  threads.reserve(2);
  threads.emplace_back(std::thread(&Server::accept, this));
  threads.emplace_back(std::thread(&Server::answer, this));
  for (std::thread& t : threads) {
    t.join();
  }
  ioc_.run();
}

void Server::accept() {
  boost::asio::ip::tcp::acceptor acceptor(
      ioc_, boost::asio::ip::tcp::endpoint(
                boost::asio::ip::make_address(conf_.address_), conf_.port_));
  while (true) {
    std::shared_ptr<Session> session = std::make_shared<Session>(ioc_);
    acceptor.accept(session->sock());
    {
      std::lock_guard<std::mutex> lock_(mutex_);
      set_.insert(session);
    }
  }
}
void Server::answer() {
  std::chrono::milliseconds ms{1};
  while (true) {
    for (std::shared_ptr<Session> session : set_) {
      session->answer();
    }
    for (std::set<std::shared_ptr<Session>>::iterator itr = set_.begin(),
                                                      end = set_.end();
         itr != end;) {
      if ((*itr)->timed_out()) {
        itr = set_.erase(itr);
      } else {
        ++itr;
      }
    }
    std::this_thread::sleep_for(ms);
  }
}