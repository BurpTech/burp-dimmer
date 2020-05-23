#ifndef WifiAp_hpp
#define WifiAp_hpp

#include <ESP8266WiFi.h>

#include "../Debug.hpp"

#include "Wifi.hpp"

#define WIFI_AP_CONFIG_SECTION "wifi-ap"

namespace Wifi {
  class Ap {
    public:
      enum class State {
        IDLE,
        AP_ACTIVE
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
        if (_state == State::IDLE) {
          if (WiFi.softAP(_ssid, _password)) {
            DEBUG_VAL(F("started AP"), F("IP"), WiFi.softAPIP());
            _setState(State::AP_ACTIVE);
          } else {
            DEBUG_MSG(F("failed to start AP"));
          }
        }
      }

      static void setConfig(const char * ssid, const char * password) {
        DEBUG_LIST_START(F("new config"));
        DEBUG_LIST_VAL(F("ssid"), ssid);
        DEBUG_LIST_VAL(F("password"), password);
        DEBUG_LIST_END;
        _ssid = ssid;
        _password = password;
        // TODO: restart AP?
      }

      static State getState() {
        return _state;
      }

      static void start() {
        // TODO
      }

      static void stop() {
        // TODO
      }
  };

  const char * Ap::_ssid;
  const char * Ap::_password;
  Ap::f_onStateChange Ap::_onStateChange;
  Ap::State Ap::_state = Ap::State::IDLE;
};

#endif
