#pragma once

#include <BurpStatus/Status.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        class Status : public BurpStatus::Status {
          public:
            enum : BurpStatus::Status::Code {
              ok,
              missingSsid,
              invalidSsid,
              ssidTooLong,
              invalidPassphrase,
              passphraseTooLong,
              invalidSecurityConfig,
              invalidChannel,
              invalidSsidHidden,
              invalidMaxConnections,
              missingLocalIp,
              invalidLocalIp,
              invalidGateway,
              missingGateway,
              invalidSubnet,
              missingSubnet,
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
