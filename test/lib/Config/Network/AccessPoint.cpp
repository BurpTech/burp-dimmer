#include "AccessPoint.hpp"
#include <unity.h>
#include <Config.hpp>
#include <TestHelpers/TestSubscriber.hpp>

namespace Config {
  namespace Network {
    namespace AccessPoint {
      using namespace Actions;

      TestHelpers::TestSubscriber<Config::State> subscriber;

      Module tests("AccessPoint", [](Describe & describe) {

        describe.setup([]() {
          store.setSubscriber(&subscriber);
        });

        describe.loop([]() {
          store.loop();
        });

      });

      // const State * state() {
        // return Network::state()->accessPoint;
      // }

      // void Config_Network_AccessPoint_State_should_have_correct_defaults() {
      // }

      // void Config_Network_AccessPoint_State_should_have_correct_field_names_for_serialization() {
      // }

      // void Config_Network_AccessPoint_should_initialize_with_the_default_state() {
        // initializeDefaults();
      // }

      // void Config_Network_AccessPoint_should_initialize_with_the_serialized_state() {
        // initialize();
      // }

      // void Config_Network_AccessPoint_should_apply_the_deserialization_action() {
        // initialize();
        // withObj([&](JsonObject & object) {
          // store.dispatch(Redux::Action<ActionType>(ActionType::NETWORK_ACCESS_POINT_DESERIALIZE, &object));
        // });
      // }

      // void test() {
        // RUN_TEST(Config_Network_AccessPoint_State_should_have_correct_defaults);
        // RUN_TEST(Config_Network_AccessPoint_State_should_have_correct_field_names_for_serialization);
        // RUN_TEST(Config_Network_AccessPoint_should_initialize_with_the_default_state);
        // RUN_TEST(Config_Network_AccessPoint_should_initialize_with_the_serialized_state);
        // RUN_TEST(Config_Network_AccessPoint_should_apply_the_deserialization_action);
      // }

    }
  }
}
