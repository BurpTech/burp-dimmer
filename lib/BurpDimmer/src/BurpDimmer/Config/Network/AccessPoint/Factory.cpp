#include "Serialization.hpp"
#include "Factory.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        constexpr int defaultChannel = 1;
        constexpr int defaultSsidHidden = 0;
        constexpr int defaultMaxConnections = 4;
        constexpr IPConfig * defaultIpConfig = nullptr;

        bool Factory::deserialize(const JsonVariant & serialized) {
          return create([&]() -> const State * {
            Serialization serialization;
            auto code = serialization.deserialize(serialized);
            if (code == Status::ok) {
              const char * ssid = _defaultSsid;
              const char * passphrase = _defaultPassphrase;
              IPConfig * ipConfig = defaultIpConfig;
              IPConfig _ipConfig;
              if (!serialization.root.securityConfig.isNull) {
                ssid = serialization.root.securityConfig.ssid;
                passphrase = serialization.root.securityConfig.passphrase;
              }
              if (!serialization.root.ipConfig.isNull) {
                _ipConfig.localIp = serialization.root.ipConfig.localIp.value;
                _ipConfig.gateway = serialization.root.ipConfig.gateway.value;
                _ipConfig.subnet = serialization.root.ipConfig.subnet.value;
                ipConfig = &_ipConfig;
              }
              return ok(new(getAddress()) State(
                ssid,
                passphrase,
                serialization.root.channel.isNull ? defaultChannel : serialization.root.channel.value,
                serialization.root.ssidHidden.isNull ? defaultSsidHidden : serialization.root.ssidHidden.value,
                serialization.root.maxConnections.isNull ? defaultMaxConnections : serialization.root.maxConnections.value,
                ipConfig
              ));
            }
            return error(code);
          });
        }

        bool Factory::createDefault() {
          return create([&]() -> const State * {
              return ok(new(getAddress()) State(
                _defaultSsid,
                _defaultPassphrase,
                defaultChannel,
                defaultSsidHidden,
                defaultMaxConnections,
                defaultIpConfig
              ));
          });
        }

        void Factory::setDefaults(const char * defaultSsid, const char * defaultPassphrase) {
          _defaultSsid = defaultSsid;
          _defaultPassphrase = defaultPassphrase;
        }

      }
    }
  }
}
