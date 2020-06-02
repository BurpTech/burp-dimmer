#include "./Reducer.hpp"
#include "./Actions.hpp"
#include "Redux/State.hpp"

namespace Config {
  namespace Network {
    namespace Station {

      void Reducer::deserialize(const JsonObject & object) {
        _initialState = new State(object);
      }

      const Redux::State * Reducer::init(const Redux::State * state) const {
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
