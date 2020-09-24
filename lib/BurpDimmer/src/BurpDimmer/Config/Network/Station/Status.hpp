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
              noObject,
              invalidObject,
              noTest,
              invalidTest
            };
            const char * c_str() const override;
        };

      }
    }
  }
}
