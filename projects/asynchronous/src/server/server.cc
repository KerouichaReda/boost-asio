#include "server.h"

Server::Server(boost::asio::io_context& ioc, Conf& conf)
    : ioc_(ioc),
      conf_(conf),
      acceptor_(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                    conf.port_)) {}

Server::~Server() {}

void Server::run() { listen(); }

void Server::listen() {
  acceptor_.async_accept([this](const boost::system::error_code& ec,
                                boost::asio::ip::tcp::socket socket) {
    if (!ec) {
      std::make_shared<Session>(std::move(socket), conf_)->run();
    }
    listen();
  });
}