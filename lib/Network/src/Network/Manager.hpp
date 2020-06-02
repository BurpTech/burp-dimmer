#pragma once

#include <Redux/Subscriber.hpp>
#include <Config.hpp>

#include "./NormalMode.hpp"
#include "./AccessPointMode.hpp"
#include "./OffMode.hpp"
#include "./WpsConfigMode.hpp"

namespace Network {

  class Manager : Redux::Subscriber {

    public:

      NormalMode  normalMode;
      AccessPointMode accessPointMode;
      OffMode offMode;
      WpsConfigMode wpsConfigMode;

      void setup();
      void loop();
      void notify() override;

    private:

      Mode * _mode = &offMode;
      const Config::Network::Manager::State * _config = nullptr;

      void _update();
      Mode * _getMode();

  };
};
