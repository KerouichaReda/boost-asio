#include "client.h"

Client::Client(boost::asio::io_context& ioc, Conf& conf)
    : ioc_(ioc), conf_(conf) {}

Client::~Client() {}

void Client::run() { std::make_shared<Session>(ioc_, conf_)->run(); }