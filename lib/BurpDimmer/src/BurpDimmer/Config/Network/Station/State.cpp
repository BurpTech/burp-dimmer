#include "Serialization.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        State::State(
          const char * _hostname,
          const char * _ssid,
          const char * _passphrase,
          const uint8_t channel,
          const uint8_t * _bssid,
          const IPConfig * ipConfig
        ) :
          hasSsid(_ssid != nullptr),
          hasPassphrase(_passphrase != nullptr),
          channel(channel),
          hasBssid(_bssid != nullptr),
          hasIpConfig(ipConfig != nullptr),
          ipConfig(ipConfig ? *ipConfig : IPConfig({0, 0, 0, 0, 0}))
        {
          strlcpy(hostname, _hostname, MAX_HOSTNAME_LENGTH + 1);
          if (hasSsid) {
            strlcpy(ssid, _ssid, MAX_SSID_LENGTH + 1);
          }
          if (hasPassphrase) {
            strlcpy(passphrase, _passphrase, MAX_PASSPHRASE_LENGTH + 1);
          }
          if (hasBssid) {
            memcpy(bssid, _bssid, BSSID_LENGTH);
          }
        }

        bool State::serialize(const JsonVariant & serialized) const {
          Serialization serialization;
          serialization.root.hostname = hostname;
          serialization.root.ssid = ssid;
          serialization.root.passphrase = hasPassphrase ? passphrase : nullptr;
          serialization.root.channel.value = channel;
          if (hasBssid) {
            memcpy(serialization.root.bssid.value, bssid, BSSID_LENGTH);
          } else {
            serialization.root.bssid.isNull = true;
          }
          if (hasIpConfig) {
            serialization.root.ipConfig.localIp.value = ipConfig.localIp;
            serialization.root.ipConfig.gateway.value = ipConfig.gateway;
            serialization.root.ipConfig.subnet.value = ipConfig.subnet;
            serialization.root.ipConfig.dns1.value = ipConfig.dns1;
            serialization.root.ipConfig.dns2.value = ipConfig.dns2;
          } else {
            serialization.root.ipConfig.isNull = true;
          }
          return serialization.serialize(serialized);
        }

      }
    }
  }
}
