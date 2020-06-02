#include "./Reducer.hpp"
#include "./Actions.hpp"

namespace Config {
  namespace Network {
    namespace AccessPoint {

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
          case ActionType::NETWORK_ACCESS_POINT_DESERIALIZE: {
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
