
#include "client.h"
Client::Client(boost::asio::io_context& ioc, Conf& conf)
    : ioc_(ioc), conf_(conf) {}

Client::~Client() {}

void Client::run() {
  create();
  connect();
}

void Client::create() { set_.insert(std::make_shared<Session>(ioc_, conf_)); }
void Client::connect() {
  for (std::shared_ptr<Session> s : set_) {
    s->connect();
  }
}
void Client::loop() {
  std::chrono::milliseconds ms{1};
  while (true) {
    for (std::shared_ptr<Session> s : set_) {
      s->write("ping");
      s->read();
    }
    std::this_thread::sleep_for(ms);
  }
}