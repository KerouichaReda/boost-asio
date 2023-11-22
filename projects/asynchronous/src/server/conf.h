#ifndef CONF_H
#define CONF_H
#include <chrono>
struct Conf {

  Conf();
  ~Conf();
 
    std::int16_t port_{8080};
    std::chrono::seconds session_lifetime_{std::chrono::seconds(1)};
};
#endif  //! CONF_H