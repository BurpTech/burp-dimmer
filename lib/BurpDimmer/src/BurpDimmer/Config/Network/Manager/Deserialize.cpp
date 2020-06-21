#include "Actions.hpp"
#include "Deserialize.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        void deserialize(const JsonObject & object, f_onState onState) {
          deserialize(object, [&](const Error error, const Params * params) {
              onState(memory.create(params));
          });
        }

      }
    }
  }
}