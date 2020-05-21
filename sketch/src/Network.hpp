#ifndef Network_hpp
#define Network_hpp

#include <ESP8266WiFi.h>

#include "Debug.hpp"

#include "ConfigFile.hpp"
#include "WifiConfig.hpp"

#define _NETWORK_STATION_CONFIG_FILE_PATH "/config/network/station.json"
#define _NETWORK_AP_CONFIG_FILE_PATH "/config/network/ap.json"
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

  private:
    static f_onStateChange _onStateChange;
    static Mode _mode;
    static State _state;
    static ConfigFile _stationConfigFile;
    static WifiConfig _stationConfig;
    static ConfigFile _apConfigFile;
    static WifiConfig _apConfig;
    static void _setState(State state);
    static void _onStationConfigChange(const char *ssid, const char *password);
    static void _onApConfigChange(const char *ssid, const char *password);

  public:
    static void setup(f_onStateChange onStateChange);
    static void loop();
    static State getState();
    static void setMode(Mode);
    static Mode getMode();
    static void setStationConfig(const char *ssid, const char *password);
    static void resetStationConfig();
    static char *getStationSsid();
    static char *getStationPassword();
    static void setApConfig(const char *ssid, const char *password);
    static void resetApConfig();
    static char *getApSsid();
    static char *getApPassword();
    static void scan();
};

Network::Mode Network::_mode = Network::Mode::NONE;
Network::State Network::_state = Network::State::IDLE;
Network::f_onStateChange Network::_onStateChange;
ConfigFile Network::_stationConfigFile(_NETWORK_STATION_CONFIG_FILE_PATH);
WifiConfig Network::_stationConfig(&_stationConfigFile, _NETWORK_STATION_DEFAULT_SSID, _NETWORK_STATION_DEFAULT_PASSWORD, _onStationConfigChange);
ConfigFile Network::_apConfigFile(_NETWORK_AP_CONFIG_FILE_PATH);
WifiConfig Network::_apConfig(&_apConfigFile, _NETWORK_AP_DEFAULT_SSID, _NETWORK_AP_DEFAULT_PASSWORD, _onApConfigChange);

void Network::setup(f_onStateChange onStateChange) {
  _onStateChange = onStateChange;

  _stationConfig.init();
  _apConfig.init();

  _setState(State::IDLE);
}

void Network::loop() {
  // TODO: Check status and notify state changes
  if (_state == State::IDLE) {
    if (WiFi.softAP(_apConfig.getSsid(), _apConfig.getPassword())) {
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

void Network::setStationConfig(const char *ssid, const char *password) {
  _stationConfig.setConfig(ssid, password);
}

void Network::resetStationConfig() {
  _stationConfig.reset();
}

char *Network::getStationSsid() {
  return _stationConfig.getSsid();
}

char *Network::getStationPassword() {
  return _stationConfig.getPassword();
}

void Network::_onStationConfigChange(const char *ssid, const char *password) {
  DEBUG_LIST_START(F("new station config"));
  DEBUG_LIST_VAL(F("ssid"), ssid);
  DEBUG_LIST_VAL(F("password"), password);
  DEBUG_LIST_END;
  // TODO: restart station?
}

void Network::setApConfig(const char *ssid, const char *password) {
  _apConfig.setConfig(ssid, password);
}

void Network::resetApConfig() {
  _apConfig.reset();
}

char *Network::getApSsid() {
  return _apConfig.getSsid();
}

char *Network::getApPassword() {
  return _apConfig.getPassword();
}

void Network::_onApConfigChange(const char *ssid, const char *password) {
  DEBUG_LIST_START(F("new AP config"));
  DEBUG_LIST_VAL(F("ssid"), ssid);
  DEBUG_LIST_VAL(F("password"), password);
  DEBUG_LIST_END;
  // TODO: restart AP?
}

void Network::scan() {
  // TODO
}

#endif
