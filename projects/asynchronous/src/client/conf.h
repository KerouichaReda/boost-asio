#ifndef CONF_H
#define CONF_H
#include <string>

struct Conf {
    std::string address_{"127.0.0.1"};
    std::int16_t port_{8080};
};



#endif  //! CONF_H