#ifndef Network_OffMode_hpp
#define Network_OffMode_hpp

#include "../Util/Debug.hpp"

#include "./Mode.hpp"

namespace Network {

  class OffMode : public Mode {

    public:

      void start() override {
        DEBUG_PRINT("TODO");
      }

      void stop() override {
        DEBUG_PRINT("TODO");
      }

      void setup() override {
        DEBUG_PRINT("TODO");
      }

      void loop() override {
      }

  };

}

#endif
