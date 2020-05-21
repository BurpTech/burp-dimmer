#ifndef Network_hpp
#define Network_hpp

#include <ESP8266WiFi.h>

#include "Debug.hpp"

#include "ConfigFile.hpp"
#include "WifiConfig.hpp"

#define NETWORK_STATION_WIFI_CONFIG "wifi-station"
#define NETWORK_STATION_AP_CONFIG "wifi-ap"

#define _NETWORK_STATION_DEFAULT_SSID ""
#define _NETWORK_STATION_DEFAULT_PASSWORD ""
#define _NETWORK_AP_DEFAULT_SSID "smart-dimmer"
#define _NETWORK_AP_DEFAULT_PASSWORD "12345678"

class Network {
  public:
    enum class Mode {
      NONE,
      AP,
      STATION,
      BOTH
    };

    enum class State {
      IDLE,
      AP_ACTIVE
    };

  using f_onStateChange = std::function<void(State state)>;
  using f_onConfigChange = std::function<void()>;

  private:
    static f_onStateChange _onStateChange;
    static f_onConfigChange _onConfigChange;
    static Mode _mode;
    static State _state;
    static void _setState(State state);
    static void _onStationConfigInit();
    static void _onStationConfigChange();
    static void _onApConfigInit();
    static void _onApConfigChange();

  public:
    static WifiConfig stationConfig;
    static WifiConfig apConfig;
    static void setup(f_onStateChange onStateChange, f_onConfigChange onConfigChange);
    static void loop();
    static State getState();
    static void setMode(Mode);
    static Mode getMode();
    static void scan();
};

Network::Mode Network::_mode = Network::Mode::NONE;
Network::State Network::_state = Network::State::IDLE;
Network::f_onStateChange Network::_onStateChange;
Network::f_onConfigChange Network::_onConfigChange;
WifiConfig Network::stationConfig(_NETWORK_STATION_DEFAULT_SSID, _NETWORK_STATION_DEFAULT_PASSWORD, _onStationConfigInit, _onStationConfigChange);
WifiConfig Network::apConfig(_NETWORK_AP_DEFAULT_SSID, _NETWORK_AP_DEFAULT_PASSWORD, _onApConfigInit, _onApConfigChange);

void Network::setup(f_onStateChange onStateChange, f_onConfigChange onConfigChange) {
  _onStateChange = onStateChange;
  _onConfigChange = onConfigChange;
  _setState(State::IDLE);
}

void Network::loop() {
  // TODO: Check status and notify state changes
  if (_state == State::IDLE) {
    if (WiFi.softAP(apConfig.ssid, apConfig.password)) {
      DEBUG_VAL(F("started AP"), F("IP"), WiFi.softAPIP());
      _setState(State::AP_ACTIVE);
    } else {
      DEBUG_MSG(F("failed to start AP"));
    }
  }
}

Network::State Network::getState() {
  return _state;
}

void Network::_setState(State state) {
  _state = state;
  _onStateChange(_state);
}

void Network::setMode(Mode mode) {
  _mode = mode;
  // TODO
}

Network::Mode Network::getMode() {
  return _mode;
}

void Network::_onStationConfigInit() {
  DEBUG_LIST_START(F("new station config"));
  DEBUG_LIST_VAL(F("ssid"), stationConfig.ssid);
  DEBUG_LIST_VAL(F("password"), stationConfig.password);
  DEBUG_LIST_END;
  // TODO: restart station?
  // Initialising so don't notify a change
}

void Network::_onStationConfigChange() {
  DEBUG_LIST_START(F("new station config"));
  DEBUG_LIST_VAL(F("ssid"), stationConfig.ssid);
  DEBUG_LIST_VAL(F("password"), stationConfig.password);
  DEBUG_LIST_END;
  // TODO: restart station?
  _onConfigChange();
}

void Network::_onApConfigInit() {
  DEBUG_LIST_START(F("new AP config"));
  DEBUG_LIST_VAL(F("ssid"), apConfig.ssid);
  DEBUG_LIST_VAL(F("password"), apConfig.password);
  DEBUG_LIST_END;
  // TODO: restart AP?
  // Initialising so don't notify a change
}

void Network::_onApConfigChange() {
  DEBUG_LIST_START(F("new AP config"));
  DEBUG_LIST_VAL(F("ssid"), apConfig.ssid);
  DEBUG_LIST_VAL(F("password"), apConfig.password);
  DEBUG_LIST_END;
  // TODO: restart AP?
  _onConfigChange();
}

void Network::scan() {
  // TODO
}

#endif
