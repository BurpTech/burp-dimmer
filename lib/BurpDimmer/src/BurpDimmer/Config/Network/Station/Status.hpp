#pragma once

#include <BurpStatus/Status.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        class Status : public BurpStatus::Status {
          public:
            enum : BurpStatus::Status::Code {
              ok,
              invalidHostname,
              hostnameTooLong,
              missingSsid,
              invalidSsid,
              ssidTooLong,
              invalidPassphrase,
              passphraseTooShort,
              passphraseTooLong,
              invalidChannel,
              invalidBssid,
              missingLocalIp,
              invalidLocalIp,
              missingGateway,
              invalidGateway,
              missingSubnet,
              invalidSubnet,
              invalidDns1,
              invalidDns2,
              invalidIpConfig,
              noObject,
              invalidConfig
            };
            const char * c_str() const override;
        };

      }
    }
  }
}
