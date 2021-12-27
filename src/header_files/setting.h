#ifndef SETTING_H
#define SETTING_H

#include <boost/asio.hpp>
#include <vector>

class TalkToClient;
typedef std::shared_ptr<TalkToClient> client_ptr;
typedef std::vector<client_ptr> clients_array;

struct Conf {
   unsigned int server_port = 8001;
};



#endif