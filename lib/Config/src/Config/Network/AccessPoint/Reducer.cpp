#include "./Reducer.hpp"
#include "./Actions.hpp"

namespace Config {
  namespace Network {
    namespace AccessPoint {

      const State * Reducer::init(const State * previous, const Redux::Reducer<State, ActionType, JsonObject>::f_withInit withInit) const {
        return withInit([&](const JsonObject * pObject) {
          return alloc(
            previous,
            [&](void * address) {
              return new(address) State(*pObject);
            }
          );
        });
      }

      const State * Reducer::reduce(const State *previous, const Redux::Action<ActionType> &action) const {
        switch (action.type) {
          case ActionType::NETWORK_ACCESS_POINT_DESERIALIZE: {
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
