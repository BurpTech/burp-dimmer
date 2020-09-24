#include "Serialization.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        State::State(
          const char * _ssid,
          const char * _passphrase,
          const uint8_t channel,
          const bool ssidHidden,
          const uint8_t maxConnections,
          const IPConfig * ipConfig
        ) :
          hasPassphrase(_passphrase != nullptr),
          channel(channel),
          ssidHidden(ssidHidden),
          maxConnections(maxConnections),
          hasIpConfig(ipConfig != nullptr),
          ipConfig(ipConfig ? *ipConfig : IPConfig({0, 0, 0}))
        {
          strlcpy(ssid, _ssid, MAX_SSID_LENGTH + 1);
          if (hasPassphrase) {
            strlcpy(passphrase, _passphrase, MAX_PASSPHRASE_LENGTH + 1);
          }
        }

        bool State::serialize(const JsonVariant & serialized) const {
          Serialization serialization;
          serialization.root.securityConfig.ssid = ssid;
          serialization.root.securityConfig.passphrase = hasPassphrase ? passphrase : nullptr;
          serialization.root.channel.value = channel;
          serialization.root.ssidHidden.value = ssidHidden;
          serialization.root.maxConnections.value = maxConnections;
          if (hasIpConfig) {
            serialization.root.ipConfig.localIp.value = ipConfig.localIp;
            serialization.root.ipConfig.gateway.value = ipConfig.gateway;
            serialization.root.ipConfig.subnet.value = ipConfig.subnet;
          } else {
            serialization.root.ipConfig.isNull = true;
          }
          return serialization.serialize(serialized);
        }

      }
    }
  }
}
