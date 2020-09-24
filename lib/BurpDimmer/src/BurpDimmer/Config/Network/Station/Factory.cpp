#include "Serialization.hpp"
#include "Factory.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        constexpr char * defaultSsid = nullptr;
        constexpr char * defaultPassphrase = nullptr;
        constexpr uint8_t defaultChannel = 0;
        constexpr uint8_t * defaultBssid = nullptr;
        constexpr IPConfig * defaultIpConfig = nullptr;
        constexpr uint32_t defaultDns1 = 0;
        constexpr uint32_t defaultDns2 = 0;

        bool Factory::deserialize(const JsonVariant & serialized) {
          return create([&]() -> const State * {
            Serialization serialization;
            auto code = serialization.deserialize(serialized);
            if (code == Status::ok) {
              IPConfig * ipConfig = defaultIpConfig;
              IPConfig _ipConfig;
              if (!serialization.root.ipConfig.isNull) {
                _ipConfig.localIp = serialization.root.ipConfig.localIp.value;
                _ipConfig.gateway = serialization.root.ipConfig.gateway.value;
                _ipConfig.subnet = serialization.root.ipConfig.subnet.value;
                _ipConfig.dns1 = serialization.root.ipConfig.dns1.isNull ? defaultDns1 : serialization.root.ipConfig.dns1.value;
                _ipConfig.dns2 = serialization.root.ipConfig.dns2.isNull ? defaultDns1 : serialization.root.ipConfig.dns2.value;
                ipConfig = &_ipConfig;
              }
              return ok(new(getAddress()) State(
                serialization.root.hostname ? serialization.root.hostname : _defaultHostname,
                serialization.root.ssid,
                serialization.root.passphrase,
                serialization.root.channel.isNull ? defaultChannel : serialization.root.channel.value,
                serialization.root.bssid.isNull ? defaultBssid : serialization.root.bssid.value,
                ipConfig
              ));
            }
            return error(code);
          });
        }

        bool Factory::createDefault() {
          return create([&]() -> const State * {
              return ok(new(getAddress()) State(
                _defaultHostname,
                defaultSsid,
                defaultPassphrase,
                defaultChannel,
                defaultBssid,
                defaultIpConfig
              ));
          });
        }

        void Factory::setDefaultHostname(const char * defaultHostname) {
          _defaultHostname = defaultHostname;
        }

      }
    }
  }
}
