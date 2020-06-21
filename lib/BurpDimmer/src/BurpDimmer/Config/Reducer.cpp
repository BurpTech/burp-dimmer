#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {

    Reducer reducer(State::memory, Network::reducer, Light::reducer);

    Reducer::Reducer(
        State::Memory & memory,
        Network::Reducer & networkReducer,
        Light::Reducer & lightReducer
    ) :
      _memory(memory),
      _networkReducer(networkReducer),
      _lightReducer(lightReducer)
    {}

    const State::Instance * Reducer::reduce(const State::Instance * previous, const Action & action) {
      const Light::State::Instance * light = _lightReducer.reduce(previous->light, action);
      const Network::State::Instance * network = _networkReducer.reduce(previous->network, action);
      if (light != previous->light || network != previous->network) {
        const State::Params params = {
          light,
          network
        };
        return _memory.create(&params);
      }
      return previous;
    }

  }
}
