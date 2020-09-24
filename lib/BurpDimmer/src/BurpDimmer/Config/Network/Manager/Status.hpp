#pragma once

#include <BurpStatus/Status.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        class Status : public BurpStatus::Status {
          public:
            enum : BurpStatus::Status::Code {
              ok,
              noObject,
              invalidObject,
              noMode,
              noAccessPointTimeout,
              invalidMode,
              invalidAccessPointTimeout,
              unknownMode
            };
            const char * c_str() const override;
        };

      }
    }
  }
}
