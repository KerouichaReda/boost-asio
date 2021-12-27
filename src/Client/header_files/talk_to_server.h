#ifndef TALK_TO_CLIENT_H
#define TALK_TO_CLIENT_H
/// @brief TalkToServer Class
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
class TalkToServer
{
public:
    TalkToServer(boost::asio::io_context& _ioc,const std::string& username , const std::string adresse, const short port);
    void run();
private:
    void loop();
    void connect();
    std::string username() const;
    void write(const std::string& msg);
    size_t read_complete(const boost::system::error_code& err, size_t bytes);
    void do_ask_clients();
    void on_clients(const std::string& msg);
    void on_ping(const std::string& msg);
    void on_login();
    void process_msg();
    void read_answer();
    void write_request();
    boost::asio::ip::tcp::endpoint ep_;
    boost::asio::ip::tcp::socket sock_;
    enum {
        max_msg = 1024,
    };
    size_t already_read_;
    char buff_[max_msg];
    bool started_;
    std::string username_;
};

#endif //!TalkToServer
