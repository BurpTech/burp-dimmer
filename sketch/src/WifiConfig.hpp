#ifndef WifiConfig_hpp
#define WifiConfig_hpp

#include <ArduinoJson.h>

#include "Debug.hpp"

#include "ConfigFile.hpp"

#define WIFI_CONFIG_SSID_BUFFER_SIZE 33
#define WIFI_CONFIG_PASSWORD_BUFFER_SIZE 64

#define _WIFI_CONFIG_JSON_DOCUMENT_SIZE 256
#define _WIFI_CONFIG_SSID_FIELD_NAME "ssid"
#define _WIFI_CONFIG_PASSWORD_FIELD_NAME "password"

class WifiConfig {
  using f_onChange = std::function<void(const char *ssid, const char *password)>;

  f_onChange _onChange;
  ConfigFile *_pConfigFile;
  const char *_defaultSsid;
  const char *_defaultPassword;
  char _ssid[WIFI_CONFIG_SSID_BUFFER_SIZE];
  char _password[WIFI_CONFIG_PASSWORD_BUFFER_SIZE];
  void _applyConfig(const char *ssid, const char *password);

  public:
    WifiConfig(ConfigFile *pConfigFile, const char *defaultSsid, const char *defaultPassword, f_onChange onChange);
    void init();
    void setConfig(const char *ssid, const char *password);
    char *getSsid();
    char *getPassword();
    void reset();
};

WifiConfig::WifiConfig(ConfigFile *pConfigFile, const char *defaultSsid, const char *defaultPassword, f_onChange onChange) {
  _pConfigFile = pConfigFile;
  _defaultSsid = defaultSsid;
  _defaultPassword = defaultPassword;
  _onChange = onChange;
}

void WifiConfig::init() {
  const char *ssid = _defaultSsid;
  const char *password = _defaultPassword;
  StaticJsonDocument<_WIFI_CONFIG_JSON_DOCUMENT_SIZE> doc;
  _pConfigFile->read(&doc);
  if (doc.isNull()) {
    ssid = doc[_WIFI_CONFIG_SSID_FIELD_NAME] | _defaultSsid;
    password = doc[_WIFI_CONFIG_PASSWORD_FIELD_NAME] | _defaultPassword;
  } else {
    DEBUG_MSG(F("JSON document is NULL, applying defaults"));
  }
  // Always notify last as we don't know what will happen
  // in the onChange callback
  _applyConfig(ssid, password);
}

void WifiConfig::setConfig(const char *ssid, const char *password) {
  StaticJsonDocument<_WIFI_CONFIG_JSON_DOCUMENT_SIZE> doc;
  doc[_WIFI_CONFIG_SSID_FIELD_NAME] = ssid;
  doc[_WIFI_CONFIG_PASSWORD_FIELD_NAME] = password;
  DEBUG_VAL(F("JSON document created"), F("field count"), doc.size());
  _pConfigFile->write(&doc);
  // Always notify last as we don't know what will happen
  // in the onChange callback
  _applyConfig(ssid, password);
}

char *WifiConfig::getSsid() {
  return _ssid;
}

char *WifiConfig::getPassword() {
  return _password;
}

void WifiConfig::reset() {
  _pConfigFile->remove();
  // Always notify last as we don't know what will happen
  // in the onChange callback
  _applyConfig(_defaultSsid, _defaultPassword);
}

void WifiConfig::_applyConfig(const char *ssid, const char *password) {
  strlcpy(_ssid, ssid, WIFI_CONFIG_SSID_BUFFER_SIZE);
  strlcpy(_password, password, WIFI_CONFIG_PASSWORD_BUFFER_SIZE);
  // Always notify last as we don't know what will happen
  // in the onChange callback
  _onChange(_ssid, _password);
}

#endif
