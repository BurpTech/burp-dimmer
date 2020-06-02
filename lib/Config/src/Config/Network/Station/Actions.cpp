#include "./Actions.hpp"

namespace Config {
  namespace Network {
    namespace Station {
      namespace Actions {

        Deserialize::Deserialize(const JsonObject & object) : 
          Redux::Action<ActionType>(ActionType::NETWORK_STATION_DESERIALIZE),
          object(object) {
        }

      }
    }
  }
}
