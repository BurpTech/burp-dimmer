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
            C_STR_CASE(noObject);
            C_STR_CASE(invalidObject);
            C_STR_CASE(noTest);
            C_STR_CASE(invalidTest);
            C_STR_DEFAULT;
          }
        }

      }
    }
  }
}
