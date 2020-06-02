#include "./Reducer.hpp"
#include "./Actions.hpp"

namespace Config {
  namespace Network {
    namespace Station {

      void Reducer::deserialize(const JsonObject & object) {
        _initialState = new State(object);
      }

      const Redux::State * Reducer::init() const {
        return _initialState;
      }

      const Redux::State * Reducer::reduce(const Redux::State *state, const Redux::Action<ActionType> &action) const {
        switch (action.type) {
          case ActionType::NETWORK_STATION_DESERIALIZE: {
            return Redux::State::replace(state, new State(
              action.as<Actions::Deserialize>().object
            ));
          }
          default:
            return state;
        }
      }

    }
  }
}
