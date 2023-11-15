
#ifndef CONF_H
#define CONF_H

#include <string>

struct Conf
{
    Conf() {}
    std::string address_{"127.0.0.1"};
    std::uint16_t port_{8000};
};
#endif  //! CONF_H