#pragma once

#include <Redux/Subscriber.hpp>
#include "./Mode.hpp"

namespace Network {

  class AccessPointMode : public Mode {

    public:

      void start() override;
      void stop() override;
      void setup() override;
      void loop() override;
      void notify() override;

  };

}
