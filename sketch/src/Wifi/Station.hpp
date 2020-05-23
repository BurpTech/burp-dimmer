#ifndef WifiStation_hpp
#define WifiStation_hpp

#include <ESP8266WiFi.h>

#include "../Debug.hpp"

#include "Wifi.hpp"

#define WIFI_STATION_CONFIG_SECTION "wifi-station"

namespace Wifi {
  class Station {
    public:
      enum class State {
        IDLE,
      };

    using f_onStateChange = std::function<void(State state)>;

    private:
      static const char * _ssid;
      static const char * _password;
      static f_onStateChange _onStateChange;
      static State _state;

      static void _setState(State state) {
        _state = state;
        _onStateChange(_state);
      }

    public:
      static void setup(f_onStateChange onStateChange) {
        _onStateChange = onStateChange;
        _setState(State::IDLE);
      }

      static void loop() {
        // TODO: Check status and notify state changes
      }

      static void setConfig(const char * ssid, const char * password) {
        DEBUG_LIST_START(F("new config"));
        DEBUG_LIST_VAL(F("ssid"), ssid);
        DEBUG_LIST_VAL(F("password"), password);
        DEBUG_LIST_END;
        _ssid = ssid;
        _password = password;
        // TODO: restart station?
      }

      static State getState() {
        return _state;
      }

      static void scan() {
        // TODO
      }
  };

  const char * Station::_ssid;
  const char * Station::_password;
  Station::f_onStateChange Station::_onStateChange;
  Station::State Station::_state = Station::State::IDLE;
};

#endif
