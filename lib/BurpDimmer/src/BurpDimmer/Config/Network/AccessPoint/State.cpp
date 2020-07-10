#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        constexpr char ssidField[] = "ssid";
        constexpr char passphraseField[] = "passphrase";
        constexpr char channelField[] = "channel";
        constexpr char ssidHiddenField[] = "ssidHidden";
        constexpr char maxConnectionsField[] = "maxConnections";
        constexpr char ipConfigField[] = "ipConfig";
        constexpr char localIpField[] = "localIp";
        constexpr char gatewayField[] = "gateway";
        constexpr char subnetField[] = "subnet";

        const char * defaultSsid(const FactorySettings::Interface & factorySettings) {
          return factorySettings.getSsid();
        }

        const char * defaultPassphrase(const FactorySettings::Interface & factorySettings) {
          return factorySettings.getPassword();
        }

        constexpr int defaultChannel = 1;
        constexpr int defaultSsidHidden = 0;
        constexpr int defaultMaxConnections = 4;
        constexpr IPConfig * defaultIpConfig = nullptr;

        State::State(
          const FactorySettings::Interface & factorySettings,
          const char * ssid,
          const char * passphrase,
          const int channel,
          const int ssidHidden,
          const int maxConnections,
          const IPConfig * ipConfig
        ) :
          factorySettings(factorySettings),
          channel(channel),
          ssidHidden(ssidHidden),
          maxConnections(maxConnections),
          hasPassphrase(passphrase != nullptr),
          hasIpConfig(ipConfig != nullptr)
        {
          strncpy(this->ssid, ssid, WL_SSID_MAX_LENGTH + 1);
          if (hasPassphrase) {
            strncpy(this->passphrase, passphrase, WL_WPA_KEY_MAX_LENGTH + 1);
          }
          if (hasIpConfig) {
            this->ipConfig = *ipConfig;
          }
        }

        State::State(const FactorySettings::Interface & factorySettings) :
          State(
            factorySettings,
            defaultSsid(factorySettings),
            defaultPassphrase(factorySettings),
            defaultChannel,
            defaultSsidHidden,
            defaultMaxConnections,
            defaultIpConfig
          )
        {}

        void State::serialize(const JsonObject & object) const {
          object[ssidField] = ssid;
          if (hasPassphrase) {
            object[passphraseField] = passphrase;
          }
          object[channelField] = channel;
          object[ssidHiddenField] = ssidHidden;
          object[maxConnectionsField] = maxConnections;
          if (hasIpConfig) {
            object[ipConfigField][localIpField] = static_cast<uint32_t>(ipConfig.localIp);
            object[ipConfigField][gatewayField] = static_cast<uint32_t>(ipConfig.gateway);
            object[ipConfigField][subnetField] = static_cast<uint32_t>(ipConfig.subnet);
          }
        }

        Factory::Factory(const FactorySettings::Interface & factorySettings) :
          _factorySettings(factorySettings)
        {}

        bool Factory::deserialize(const JsonObject & object) {
          return false;
          // return create([&]() -> const State * {
          //   if (!object.isNull()) {
          //     if (object.containsKey(testField)) {
          //       const JsonVariant v = object[testField];
          //       if (!v.is<int>()) {
          //         return error(Status::invalidTest);
          //       }
          //       return ok(new(getAddress()) State(v.as<int>()));
          //     }
          //     return error(Status::noTest);
          //   }
          //   return error(Status::noObject);
          // });
        }

        bool Factory::createDefault() {
          return create([&]() -> const State * {
              return ok(new(getAddress()) State(_factorySettings));
          });
        }

        #define C_STR_LABEL "BurpDimmer::Config::Network::AccessPoint"
        #define C_STR_CASE(CODE) BURP_STATUS_C_STR_CASE(C_STR_LABEL, CODE)
        #define C_STR_DEFAULT BURP_STATUS_C_STR_DEFAULT(C_STR_LABEL)
        const char * Status::c_str() const {
          switch (getCode()) {
            C_STR_CASE(ok);
            C_STR_CASE(noObject);
            C_STR_CASE(noTest);
            C_STR_CASE(invalidTest);
            C_STR_DEFAULT;
          }
        }

      }
    }
  }
}
