#include "Status.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        #define C_STR_LABEL "BurpDimmer::Config::Network::AccessPoint"
        #define C_STR_CASE(CODE) BURP_STATUS_C_STR_CASE(C_STR_LABEL, CODE)
        #define C_STR_DEFAULT BURP_STATUS_C_STR_DEFAULT(C_STR_LABEL)
        const char * Status::c_str() const {
          switch (getCode()) {
            C_STR_CASE(ok);
            C_STR_CASE(missingSsid);
            C_STR_CASE(invalidSsid);
            C_STR_CASE(ssidTooLong);
            C_STR_CASE(invalidPassphrase);
            C_STR_CASE(passphraseTooShort);
            C_STR_CASE(passphraseTooLong);
            C_STR_CASE(invalidSecurityConfig);
            C_STR_CASE(invalidChannel);
            C_STR_CASE(invalidSsidHidden);
            C_STR_CASE(invalidMaxConnections);
            C_STR_CASE(missingLocalIp);
            C_STR_CASE(invalidLocalIp);
            C_STR_CASE(invalidGateway);
            C_STR_CASE(missingGateway);
            C_STR_CASE(invalidSubnet);
            C_STR_CASE(missingSubnet);
            C_STR_CASE(invalidIpConfig);
            C_STR_CASE(noObject);
            C_STR_CASE(invalidConfig);
            C_STR_DEFAULT;
          }
        }

      }
    }
  }
}
