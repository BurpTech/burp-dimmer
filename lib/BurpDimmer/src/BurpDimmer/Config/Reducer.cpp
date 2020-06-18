#include "Light/Reducer.hpp"
#include "Network/Reducer.hpp"
#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {

    const Reducer reducer;

    const State * Reducer::reduce(const State * previous, const Action & action) const {
      const Light::State * light = Light::reducer.reduce(previous->light, action);
      const Network::State * network = Network::reducer.reduce(previous->network, action);
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
