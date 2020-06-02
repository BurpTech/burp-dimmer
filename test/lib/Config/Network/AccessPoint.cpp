#include <unity.h>
#include <ArduinoJson.h>
#include <Redux/Subscriber.hpp>
#include <Config/Network.hpp>
#include <Config/Network/AccessPoint.hpp>
#include "../../helpers/util.hpp"
#include "../../Config.hpp"
#include "../Network.hpp"
#include "./AccessPoint.hpp"

namespace Config {
  namespace Network {
    namespace AccessPoint {
      using namespace Actions;

      const State * state() {
        return Network::state()->accessPoint;
      }

      void Config_Network_AccessPoint_State_should_have_correct_defaults() {
      }

      void Config_Network_AccessPoint_State_should_have_correct_field_names_for_serialization() {
      }

      void Config_Network_AccessPoint_should_initialize_with_the_correct_state() {
        initialize();
      }

      void Config_Network_AccessPoint_should_apply_the_deserialization_action() {
        initialize();
        withObj([&](JsonObject & object) {
        });
      }

      void test() {
        RUN_TEST(Config_Network_AccessPoint_State_should_have_correct_defaults);
        RUN_TEST(Config_Network_AccessPoint_State_should_have_correct_field_names_for_serialization);
        RUN_TEST(Config_Network_AccessPoint_should_initialize_with_the_correct_state);
        RUN_TEST(Config_Network_AccessPoint_should_apply_the_deserialization_action);
      }

    }
  }
}
