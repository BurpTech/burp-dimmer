#pragma once

#include <BurpTree/State.hpp>
#include <BurpTree/Factory.hpp>
#include <BurpTree/Status.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        class State : public BurpTree::State {

          public:

            const int test;

            State(
                const Uid uid,
                const int test
            );
            State(const Uid uid);
            void serialize(const JsonObject & object) const override;

        };

        class Status : public BurpTree::Status {
          public:
            enum : BurpTree::Status::Code {
              noError,
              noObject,
              noTest,
              invalidTest
            };
            const char * c_str() const override;
        };

        class Factory : public BurpTree::Factory<State, Status> {

          public:

            const BurpTree::State * deserialize(const JsonObject & serialized) override ;

          private:

            const State * _default() override;

        };

      }
    }
  }
}
