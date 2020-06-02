#include "./Actions.hpp"

namespace Config {
  namespace Network {
    namespace AccessPoint {
      namespace Actions {

        Deserialize::Deserialize(const JsonObject & object) : 
          Redux::Action<ActionType>(ActionType::NETWORK_ACCESS_POINT_DESERIALIZE),
          object(object) {
        }

      }
    }
  }
}
