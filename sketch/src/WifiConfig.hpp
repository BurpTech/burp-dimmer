#ifndef WifiConfig_hpp
#define WifiConfig_hpp

#include <ArduinoJson.h>

#include "Debug.hpp"

#define WIFI_CONFIG_SSID_BUFFER_SIZE 33
#define WIFI_CONFIG_PASSWORD_BUFFER_SIZE 64

#define _WIFI_CONFIG_JSON_DOCUMENT_SIZE 256
#define _WIFI_CONFIG_SSID_FIELD_NAME "ssid"
#define _WIFI_CONFIG_PASSWORD_FIELD_NAME "password"

class WifiConfig {
  using f_callback = std::function<void()>;

  f_callback _onChange;
  const char *_defaultSsid;
  const char *_defaultPassword;

  public:
    char ssid[WIFI_CONFIG_SSID_BUFFER_SIZE];
    char password[WIFI_CONFIG_PASSWORD_BUFFER_SIZE];
    WifiConfig(const char *defaultSsid, const char *defaultPassword, f_callback onChange)
    : _defaultSsid(defaultSsid),
      _defaultPassword(defaultPassword),
      _onChange(onChange)
    {}
    void deserialize(JsonObject *pObj);
    void serialize(JsonObject *pObj);
    void setConfig(const char *newSsid, const char *newPassword);
    void reset();
};

void WifiConfig::deserialize(JsonObject *pObj) {
  const char *newSsid = _defaultSsid;
  const char *newPassword = _defaultPassword;
  if (pObj->isNull()) {
    DEBUG_LIST_START(F("Field is not present, using defaults"));
    DEBUG_LIST_VAL(F("_defaultSsid"), _defaultSsid);
    DEBUG_LIST_VAL(F("_defaultPassword"), _defaultPassword);
    DEBUG_LIST_END;
  } else {
    newSsid = (*pObj)[_WIFI_CONFIG_SSID_FIELD_NAME] | _defaultSsid;
    newPassword = (*pObj)[_WIFI_CONFIG_PASSWORD_FIELD_NAME] | _defaultPassword;
  }
  setConfig(newSsid, newPassword);
}

void WifiConfig::serialize(JsonObject *pObj) {
  (*pObj)[_WIFI_CONFIG_SSID_FIELD_NAME] = ssid;
  (*pObj)[_WIFI_CONFIG_PASSWORD_FIELD_NAME] = password;
}

void WifiConfig::setConfig(const char *newSsid, const char *newPassword) {
  strlcpy(ssid, newSsid, WIFI_CONFIG_SSID_BUFFER_SIZE);
  strlcpy(password, newPassword, WIFI_CONFIG_PASSWORD_BUFFER_SIZE);
  DEBUG_LIST_START(F("settings copied"));
  DEBUG_LIST_VAL(F("ssid"), ssid);
  DEBUG_LIST_VAL(F("password"), password);
  DEBUG_LIST_END;
  // Always notify last as we don't know what will happen
  // in the onChange callback
  _onChange();
}

void WifiConfig::reset() {
  setConfig(_defaultSsid, _defaultPassword);
}

#endif
