#pragma once

#include <ESP8266WiFi.h>
#include <BurpStatus/Status.hpp>
#include <BurpTree/State.hpp>
#include <BurpTree/Factory.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        struct IPConfig {
          IPAddress localIp;
          IPAddress gateway;
          IPAddress subnet;
        };

        class State : public BurpTree::State {

          public:

            const char ssid[WL_SSID_MAX_LENGTH + 1];
            const bool hasPassphrase;
            const char passphrase[WL_WPA_KEY_MAX_LENGTH + 1];
            const int channel;
            const int ssidHidden;
            const int maxConnections;
            const bool hasIpConfig;
            const IPConfig ipConfig;

            State(
              const char * ssid,
              const char * passphrase,
              const int channel,
              const int ssidHidden,
              const int maxConnections,
              const IPConfig ipConfig
            );
            State(const char * defaultSsid, const char * defaultPassphrase);
            void serialize(const JsonObject & object) const override;

        };

        class Status : public BurpStatus::Status {
          public:
            enum : BurpStatus::Status::Code {
              ok,
              noObject,
              noTest,
              invalidTest
            };
            const char * c_str() const override;
        };

        class Factory : public BurpTree::Factory<State, Status> {

          public:

            void setDefaults(const char * defaultSsid, const char * defaultPassphrase);
            bool deserialize(const JsonObject & serialized) override ;
            bool createDefault() override;

          private:

            const char * _defaultSsid;
            const char * _defaultPassphrase;

        };

      }
    }
  }
}
