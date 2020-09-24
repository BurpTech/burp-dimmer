#include "Serialization.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        State::State(
          const char * _ssid,
          const char * _passphrase,
          const int8_t channel,
          const bool ssidHidden,
          const int8_t maxConnections,
          const IPConfig * ipConfig
        ) :
          hasPassphrase(_passphrase != nullptr),
          channel(channel),
          ssidHidden(ssidHidden),
          maxConnections(maxConnections),
          hasIpConfig(ipConfig != nullptr),
          ipConfig(ipConfig ? *ipConfig : IPConfig({0, 0, 0}))
        {
          strncpy(ssid, _ssid, WL_SSID_MAX_LENGTH);
          if (hasPassphrase) {
            strncpy(passphrase, _passphrase, WL_WPA_KEY_MAX_LENGTH);
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
