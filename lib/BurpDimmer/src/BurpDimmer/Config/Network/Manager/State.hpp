#pragma once

#include <array>
#include <BurpTree/State.hpp>
#include <BurpTree/Factory.hpp>
#include <BurpTree/Status.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        class State : public BurpTree::State {

          public:

            enum PermMode : size_t {
              NORMAL = 0,
              ACCESS_POINT,
              OFF,
              count
            };

            enum class TempMode {
              ACCESS_POINT,
              WPS_CONFIG
            };

            using Timeout = unsigned long;

            const PermMode permMode;
            const TempMode tempMode;
            const bool tempModeActive;
            const Timeout accessPointTimeout;

            State(
                const PermMode permMode,
                const TempMode tempMode,
                const bool tempModeActive,
                const Timeout accessPointTimeout
            );
            State();
            void serialize(const JsonObject & object) const override;

        };

        class Status : public BurpTree::Status {
          public:
            enum : BurpTree::Status::Code {
              ok,
              noObject,
              noMode,
              noAccessPointTimeout,
              invalidMode,
              invalidAccessPointTimeout,
              unknownMode
            };
            const char * c_str() const override;
        };

        class Factory : public BurpTree::Factory<State, Status> {

          public:

            bool createDefault() override;
            bool deserialize(const JsonObject & serialized) override ;
            bool nextPermMode();
            bool startTempAccessPoint();
            bool startWpsConfig();
            bool stopTempMode();
            bool setNormalMode();

        };

      }
    }
  }
}
