#pragma once

#include <BurpStatus/Status.hpp>
#include <BurpTree/State.hpp>
#include <BurpTree/Factory.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        class State : public BurpTree::State {

          public:

            const int test;

            State(const int test);
            State();
            void serialize(const JsonObject & object) const override;

        };

        class Status : public BurpStatus::Status {
          public:
            enum : BurpStatus::Status::Code {
              ok,
              noObject,
              noTest,
              invalidTest
            };
            const char * c_str() const override;
        };

        class Factory : public BurpTree::Factory<State, Status> {

          public:

            bool deserialize(const JsonObject & serialized) override ;
            bool createDefault() override;

        };

      }
    }
  }
}
