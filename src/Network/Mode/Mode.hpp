#ifndef Network_Mode_Mode_hpp
#define Network_Mode_Mode_hpp

#include <Arduino.h>
#include <functional>

#include "../../Error.hpp"

namespace Network {
  namespace Mode {
    class Mode {
      public:
        using f_callback = std::function<void(Error * error)>;
        using f_done = std::function<void(int next)>;

        const char * name;
        const char * displayName;
        Mode(const char * name, const char * displayName) :
          name(name),
          displayName(displayName) {
        }

        virtual void start(f_callback started, f_done done) = 0;
        virtual void stop(f_callback stopped) = 0;
        virtual void setup();
        virtual void loop();
    };
  }
}

#endif
