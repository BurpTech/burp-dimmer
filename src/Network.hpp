#ifndef Network_hpp
#define Network_hpp

#include <Arduino.h>

#include "Debug.hpp"

#include "Network/Manager.hpp"
#include "Network/Mode/Normal.hpp"
#include "Network/Mode/AccessPoint.hpp"
#include "Network/Mode/WpsConfig.hpp"
#include "Network/Mode/Off.hpp"

namespace Network {
  namespace Mode {
    enum {
      NORMAL,
      ACCESS_POINT,
      WPS_CONFIG,
      OFF,
      _LENGTH
    };
  }

  namespace {
    Mode::Normal _modeNormal("normal", "Normal");
    Mode::AccessPoint _modeAccessPoint("access-point", "Access Point");
    Mode::WpsConfig _modeWpsConfig("wps-config", "WPS Config", Mode::NORMAL);
    Mode::Off _modeOff("off", "Off");
    Mode::Mode * _networkModes[Mode::_LENGTH + 1] = {
      &_modeNormal,
      &_modeAccessPoint,
      &_modeWpsConfig,
      &_modeOff,
      NULL,
    };
  }

  Manager manager(_networkModes);
}

#endif
