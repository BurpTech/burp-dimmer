#pragma once

#include <ESP8266WiFi.h>
#include <BurpStatus/Status.hpp>
#include <BurpTree/State.hpp>
#include <BurpTree/Factory.hpp>
#include "../../../FactorySettings/Interface.hpp"

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

            const FactorySettings::Interface & factorySettings;
            char ssid[WL_SSID_MAX_LENGTH + 1];
            const int channel;
            const int ssidHidden;
            const int maxConnections;

            const bool hasPassphrase;
            char passphrase[WL_WPA_KEY_MAX_LENGTH + 1];

            const bool hasIpConfig;
            IPConfig ipConfig;

            State(
              const FactorySettings::Interface & factorySettings,
              const char * ssid,
              const char * passphrase,
              const int channel,
              const int ssidHidden,
              const int maxConnections,
              const IPConfig * ipConfig
            );
            State(const FactorySettings::Interface & factorySettings);
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

            void setFactorySettings(const FactorySettings::Interface & factorySettings);

            bool deserialize(const JsonObject & serialized) override ;
            bool createDefault() override;

          private:

            const FactorySettings::Interface & _factorySettings;

        };

      }
    }
  }
}
