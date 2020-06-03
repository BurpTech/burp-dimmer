#include "./Reducer.hpp"
#include "./Actions.hpp"
#include "ActionType.hpp"
#include "ArduinoJson.hpp"
#include "Config/Network/Station/State.hpp"

namespace Config {
  namespace Network {
    namespace Station {

      const State * Reducer::init(const State * previous, const JsonObject & object) const {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(object);
          }
        );
      }

      const State * Reducer::reduce(const State *previous, const Redux::Action<ActionType> &action) const {
        switch (action.type) {
          case ActionType::NETWORK_STATION_DESERIALIZE: {
            return alloc(
              previous,
              [&](void * address) {
                return new(address) State(
                  action.as<Actions::Deserialize>().object
                );
              }
            );
          }
          default:
            return previous;
        }
      }

    }
  }
}
