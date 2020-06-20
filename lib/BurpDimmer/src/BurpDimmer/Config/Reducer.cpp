#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {

    const Reducer reducer(memory, Network::reducer, Light::reducer);

    Reducer::Reducer(
        Memory & memory,
        const Network::Reducer & networkReducer,
        const Light::Reducer & lightReducer
    ) :
      _memory(memory),
      _networkReducer(networkReducer),
      _lightReducer(lightReducer)
    {}

    const State * Reducer::reduce(const State * previous, const Action & action) const {
      const Light::State * light = _lightReducer.reduce(previous->light, action);
      const Network::State * network = _networkReducer.reduce(previous->network, action);
      if (light != previous->light || network != previous->network) {
        const Params params = {
          light,
          network
        };
        return memory.create(&params);
      }
      return previous;
    }

  }
}
