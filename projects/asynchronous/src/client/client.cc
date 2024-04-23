#include "client.h"

Client::Client(boost::asio::io_context& ioc, Conf& conf)
    : ioc_(ioc), conf_(conf), resolver_(ioc) {}

Client::~Client() {}

void Client::run() {
  ep_ = resolver_.resolve(conf_.address_, std::to_string(conf_.port_)); 
  try {
    std::make_shared<Session>(ioc_, ep_, conf_)->run();    
  } catch (const std::exception& e ) {
    std::cout << "Error : " << e.what() << std::endl;
    return;
  }
}