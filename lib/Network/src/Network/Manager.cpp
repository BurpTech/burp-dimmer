#include "./Manager.hpp"
#include "Util/Debug.hpp"

namespace Network {

  void Manager::setup() {
    normalMode.setup();
    accessPointMode.setup();
    offMode.setup();
    wpsConfigMode.setup();
    _update();
  }

  void Manager::loop() {
    normalMode.loop();
    accessPointMode.loop();
    offMode.loop();
    wpsConfigMode.loop();
  }

  void Manager::notify() {
    const Config::Network::Manager::State * config = Config::store.state->network->manager;
    if (config != _config) {
      _config = config;
      _update();
    }
  }

  void Manager::_update() {
    Mode * mode = _getMode();
    if (mode != _mode) {
      _mode->stop();
      _mode = mode;
      _mode->start();
    }
  }

  Mode * Manager::_getMode() {
    if (_config->tempModeActive) {
      switch (_config->tempMode) {
        case Config::Network::Manager::TempMode::ACCESS_POINT:
          return &accessPointMode;
        case Config::Network::Manager::TempMode::WPS_CONFIG:
          return &wpsConfigMode;
      }
    } else {
      switch (_config->permMode) {
        case Config::Network::Manager::PermMode::NORMAL:
          return &normalMode;
        case Config::Network::Manager::PermMode::ACCESS_POINT:
          return &accessPointMode;
        case Config::Network::Manager::PermMode::OFF:
          return &offMode;
      }
    }
    BURP_DEBUG_ERROR("IMPOSSIBLE MODE!!");
    return nullptr;
  }

}
