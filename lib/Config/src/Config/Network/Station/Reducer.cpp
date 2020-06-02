#include "./Reducer.hpp"
#include "./Actions.hpp"
#include "ActionType.hpp"
#include "ArduinoJson.hpp"
#include "Config/Network/Station/State.hpp"
#include "Redux/State.hpp"

namespace Config {
  namespace Network {
    namespace Station {

      const Redux::State * Reducer::init(const Redux::State * state, const Redux::Reducer<State, ActionType, JsonObject>::f_withInit withInit) const {
        return withInit([&](const JsonObject * pObject) {
          return Redux::Reducer<State, ActionType, JsonObject>::_alloc(
            state->as<State>(),
            [&](void * address) {
              return new(address) State(*pObject);
            }
          );
        });
      }

      const Redux::State * Reducer::reduce(const Redux::State *state, const Redux::Action<ActionType> &action) const {
        switch (action.type) {
          case ActionType::NETWORK_STATION_DESERIALIZE: {
            return Redux::Reducer<State, ActionType, JsonObject>::_alloc(
              state->as<State>(),
              [&](void * address) {
                return new(address) State(
                  action.as<Actions::Deserialize>().object
                );
              }
            );
          }
          default:
            return state;
        }
      }

    }
  }
}
