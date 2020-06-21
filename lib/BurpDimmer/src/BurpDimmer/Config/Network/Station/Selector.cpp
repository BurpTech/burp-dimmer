#include "Selector.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        Selector * selector;

        const State::Instance * select(const Network::State::Instance * state) {
          return state->station;
        }

        void init(const Network::State::Instance * state) {
          selector = new Selector(select, state);
        }

        void deinit() {
          delete selector;
        }

      }
    }
  }
}
