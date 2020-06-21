#include "Selector.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      Selector * selector;

      const State::Instance * select(const Config::State::Instance * state) {
        return state->light;
      }

      void init(const Config::State::Instance * state) {
        selector = new Selector(select, state);
      }

      void deinit() {
        delete selector;
      }

    }
  }
}
