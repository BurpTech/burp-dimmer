#ifndef WifiConfig_hpp
#define WifiConfig_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Wifi.hpp"
#include "../Json/Object.hpp"

#define WIFI_CONFIG_SSID_BUFFER_SIZE 33
#define WIFI_CONFIG_PASSWORD_BUFFER_SIZE 64

#define _WIFI_CONFIG_JSON_DOCUMENT_SIZE 256
#define _WIFI_CONFIG_SSID_FIELD_NAME "ssid"
#define _WIFI_CONFIG_PASSWORD_FIELD_NAME "password"

namespace Wifi {
  class Config: public Json::Object {
    using f_onChange = std::function<void()>;

    f_onChange _onChange;
    char _defaultSsid[WIFI_CONFIG_SSID_BUFFER_SIZE];
    char _defaultPassword[WIFI_CONFIG_PASSWORD_BUFFER_SIZE];

    public:
      char ssid[WIFI_CONFIG_SSID_BUFFER_SIZE];
      char password[WIFI_CONFIG_PASSWORD_BUFFER_SIZE];

      Config(const char * name, f_onChange onChange) :
        Json::Object(name),
        _onChange(onChange) {
      }

      void deserialize(JsonObject *pObj) {
        const char *newSsid = _defaultSsid;
        const char *newPassword = _defaultPassword;
        if (pObj->isNull()) {
          DEBUG_PRINT("Field is not present, using defaults: _defaultSsid: [%s]: _defaultPassword: [%s]", _defaultSsid, _defaultPassword);
        } else {
          newSsid = (*pObj)[_WIFI_CONFIG_SSID_FIELD_NAME] | _defaultSsid;
          newPassword = (*pObj)[_WIFI_CONFIG_PASSWORD_FIELD_NAME] | _defaultPassword;
        }
        setConfig(newSsid, newPassword);
      }

      void serialize(JsonObject *pObj) {
        (*pObj)[_WIFI_CONFIG_SSID_FIELD_NAME] = ssid;
        (*pObj)[_WIFI_CONFIG_PASSWORD_FIELD_NAME] = password;
      }

      void setDefaults(const char *newSsid, const char *newPassword) {
        strlcpy(_defaultSsid, newSsid, WIFI_CONFIG_SSID_BUFFER_SIZE);
        strlcpy(_defaultPassword, newPassword, WIFI_CONFIG_PASSWORD_BUFFER_SIZE);
        DEBUG_PRINT("default settings copied: ssid: [%s]: password: [%s]", _defaultSsid, _defaultPassword);
      }

      void setConfig(const char *newSsid, const char *newPassword) {
        strlcpy(ssid, newSsid, WIFI_CONFIG_SSID_BUFFER_SIZE);
        strlcpy(password, newPassword, WIFI_CONFIG_PASSWORD_BUFFER_SIZE);
        DEBUG_PRINT("settings copied: ssid: [%s]: password: [%s]", ssid, password);
        // Always notify last as we don't know what will happen
        // in the onChange callback
        _onChange();
      }

      void reset() {
        setConfig(_defaultSsid, _defaultPassword);
      }
  };
};

#endif
