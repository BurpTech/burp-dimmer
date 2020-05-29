#ifndef Network_Config_Manager_hpp
#define Network_Config_Manager_hpp

#include <Arduino.h>
#include <ArduinoJson.h>

#include "../../Debug.hpp"

#include "../../Json/Object.hpp"

namespace Network {
  namespace Config {
    class Manager : public Json::Object {
      public:
        static constexpr size_t MODE_BUFFER_SIZE = 20;
        char mode[Manager::MODE_BUFFER_SIZE];

        Manager(const char * name) :
          Json::Object(name) {
        }

        void serialize(JsonObject & object) {
        }

        void deserialize(JsonObject & object) {
        }

        setConfig(char * newMode) {

        }

      private:
    };
  }
}

#endif
