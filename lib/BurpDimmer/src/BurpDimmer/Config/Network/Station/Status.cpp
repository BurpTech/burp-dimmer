#include "Status.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        #define C_STR_LABEL "BurpDimmer::Config::Network::Station"
        #define C_STR_CASE(CODE) BURP_STATUS_C_STR_CASE(C_STR_LABEL, CODE)
        #define C_STR_DEFAULT BURP_STATUS_C_STR_DEFAULT(C_STR_LABEL)
        const char * Status::c_str() const {
          switch (getCode()) {
            C_STR_CASE(ok);
            C_STR_CASE(invalidHostname);
            C_STR_CASE(hostnameTooLong);
            C_STR_CASE(missingSsid);
            C_STR_CASE(invalidSsid);
            C_STR_CASE(ssidTooLong);
            C_STR_CASE(invalidPassphrase);
            C_STR_CASE(passphraseTooShort);
            C_STR_CASE(passphraseTooLong);
            C_STR_CASE(invalidChannel);
            C_STR_CASE(invalidBssid);
            C_STR_CASE(missingLocalIp);
            C_STR_CASE(invalidLocalIp);
            C_STR_CASE(missingGateway);
            C_STR_CASE(invalidGateway);
            C_STR_CASE(missingSubnet);
            C_STR_CASE(invalidSubnet);
            C_STR_CASE(invalidDns1);
            C_STR_CASE(invalidDns2);
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
