#ifndef Network_Config_Manager_hpp
#define Network_Config_Manager_hpp

#include <ArduinoJson.h>

#include "../../Util/Debug.hpp"

#include "../../Json/Object.hpp"
#include "../../Redux/State.hpp"

namespace Network {
  namespace Config {
    class Manager : public Json::Object, public Redux::State {
      public:

        static constexpr char MODE_FIELD[] = "mode";

        enum class Mode {
          NORMAL,
          ACCESS_POINT,
          WPS_CONFIG,
          OFF
        };

        Mode mode = Mode::NORMAL;

        void serialize(JsonObject & object) {
          object[Manager::MODE_FIELD] = static_cast<int>(mode);
        }

        void deserialize(JsonObject & object) {
          mode = static_cast<Mode>(object[Manager::MODE_FIELD].as<int>());
        }

    };

    constexpr char Manager::MODE_FIELD[];
  }
}

#endif
