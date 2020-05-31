#ifndef Network_Manager_hpp
#define Network_Manager_hpp

#include "../Util/Debug.hpp"

#include "../Redux/Subscriber.hpp"
#include "../Config.hpp"

#include "./NormalMode.hpp"
#include "./AccessPointMode.hpp"
#include "./OffMode.hpp"
#include "./WpsConfigMode.hpp"
#include "Config/Network/Manager.hpp"

namespace Network {

  class Manager : Redux::Subscriber {

    public:

      NormalMode  normalMode;
      AccessPointMode accessPointMode;
      OffMode offMode;
      WpsConfigMode wpsConfigMode;

      void setup() {
        normalMode.setup();
        accessPointMode.setup();
        offMode.setup();
        wpsConfigMode.setup();
        _update();
      }

      void loop() {
        normalMode.loop();
        accessPointMode.loop();
        offMode.loop();
        wpsConfigMode.loop();
      }

      void notify() override {
        const Config::Network::Manager * config = Config::store.getState<Config::State>()->network->manager;
        if (config != _config) {
          _config = config;
          _update();
        }
      }

    private:

      Mode * _mode = &offMode;
      const Config::Network::Manager * _config = nullptr;

      void _update() {
        Mode * mode = _getMode();
        if (mode != _mode) {
          _mode->stop();
          _mode = mode;
          _mode->start();
        }
      }

      Mode * _getMode() {
        switch (_config->mode) {
          case Config::Network::Manager::Mode::NORMAL:
            return &normalMode;
          case Config::Network::Manager::Mode::ACCESS_POINT:
            return &accessPointMode;
          case Config::Network::Manager::Mode::OFF:
            return &offMode;
          case Config::Network::Manager::Mode::WPS_CONFIG:
            return &wpsConfigMode;
        }
      }

  };
};

#endif
