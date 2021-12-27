#ifndef TALK_TO_CLIENT_H
#define TALK_TO_CLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>

#include "setting.h"

class TalkToClient : public std::enable_shared_from_this<TalkToClient> {
public:
    TalkToClient(boost::asio::io_context& _io_context , clients_array& _clients, std::recursive_mutex& _mutex);
    std::string username() const;
    void answer_to_clients();
    void set_clients_changed();
    boost::asio::ip::tcp::socket& sock();
    bool timed_out() const;
    void stop();
    void read_request();
    //~TalkToClient();

private:
    void write(const std::string& msg);
    void on_clients();
    void on_ping();
    void on_login(const std::string& msg);
    void process_request();
    void update_client_changed();
    boost::asio::ip::tcp::socket sock_;
    clients_array& clients_;
    std::recursive_mutex& mutex_;
    enum  {
        max_msg = 1024,
        max_time = 1200,
    };
    size_t already_read_;
    char buff_[max_msg];
    bool started_;
    std::string username_;
    bool clients_changed_;
    std::chrono::time_point<std::chrono::steady_clock> last_ping;
};

#endif //!TALK_TO_CLIENT_H