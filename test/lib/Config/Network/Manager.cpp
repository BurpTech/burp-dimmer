#include <unity.h>
#include <ArduinoJson.h>
#include <Redux/Subscriber.hpp>
#include <Config/Network.hpp>
#include <Config/Network/Manager.hpp>
#include "../../helpers/util.hpp"
#include "../../Config.hpp"
#include "../Network.hpp"
#include "./Manager.hpp"
#include "ActionType.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      using namespace Actions;

      const State * state() {
        return Network::state()->manager;
      }

      void Config_Network_Manager_State_should_have_correct_defaults() {
        TEST_ASSERT_EQUAL_INT(PermMode::NORMAL, State::DEFAULT_PERM_MODE);
        TEST_ASSERT_EQUAL_INT(TempMode::ACCESS_POINT, State::DEFAULT_TEMP_MODE);
        TEST_ASSERT_EQUAL_INT(false, State::DEFAULT_TEMP_MODE_ACTIVE);
        TEST_ASSERT_EQUAL_UINT32(0, State::DEFAULT_ACCESS_POINT_TIMEOUT);
      }

      void Config_Network_Manager_State_should_have_correct_field_names_for_serialization() {
        TEST_ASSERT_EQUAL_STRING("mode", State::MODE_FIELD);
        TEST_ASSERT_EQUAL_STRING("accessPointTimeout", State::ACCESS_POINT_TIMEOUT_FIELD);
      }

      void Config_Network_Manager_should_initialize_with_the_default_state() {
        initializeDefaults();
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_PERM_MODE, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(State::DEFAULT_ACCESS_POINT_TIMEOUT, state()->accessPointTimeout);
      }

      void Config_Network_Manager_should_initialize_with_the_serialized_state() {
        initialize();
        TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
      }

      void Config_Network_Manager_should_apply_the_deserialization_action() {
        initialize();
        withObj([&](JsonObject & object) {
          object[State::MODE_FIELD] = static_cast<int>(PermMode::OFF);
          object[State::ACCESS_POINT_TIMEOUT_FIELD] = 30000;
          store.dispatch(Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_DESERIALIZE, &object));
          TEST_ASSERT_EQUAL_INT(PermMode::OFF, state()->permMode);
          TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
          TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state()->tempModeActive);
          TEST_ASSERT_EQUAL_UINT32(30000, state()->accessPointTimeout);
        });
      }

      void Config_Network_Manager_should_apply_the_set_access_point_timeout_action() {
        initialize();
        unsigned long timeout = 100000;
        store.dispatch(Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT, &timeout));
        TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(timeout, state()->accessPointTimeout);
      }

      void Config_Network_Manager_should_apply_the_next_mode_action() {
        initialize();

        // set a temp mode to verify that setting a perm mode
        // turns it off
        store.dispatch(setTempModeWpsConfig);

        store.dispatch(nextPermMode);
        TEST_ASSERT_EQUAL_INT(PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(nextPermMode);
        TEST_ASSERT_EQUAL_INT(PermMode::NORMAL, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(nextPermMode);
        TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(nextPermMode);
        TEST_ASSERT_EQUAL_INT(PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
      }

      void Config_Network_Manager_should_apply_the_set_perm_mode_action() {
        initialize();

        // set a temp mode to verify that setting a perm mode
        // turns it off
        store.dispatch(setTempModeWpsConfig);

        store.dispatch(setPermModeOff);
        TEST_ASSERT_EQUAL_INT(PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(setPermModeNormal);
        TEST_ASSERT_EQUAL_INT(PermMode::NORMAL, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(setPermModeAccessPoint);
        TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
      }

      void Config_Network_Manager_should_apply_the_set_temp_mode_action() {
        initialize();

        // set a perm mode to verify that setting a temp mode
        // switches the temp mode on
        store.dispatch(setPermModeOff);

        store.dispatch(setTempModeWpsConfig);
        TEST_ASSERT_EQUAL_INT(PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(TempMode::WPS_CONFIG, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(true, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(setTempModeAccessPoint);
        TEST_ASSERT_EQUAL_INT(PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(TempMode::ACCESS_POINT, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(true, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
      }

      void test() {
        RUN_TEST(Config_Network_Manager_State_should_have_correct_defaults);
        RUN_TEST(Config_Network_Manager_State_should_have_correct_field_names_for_serialization);
        RUN_TEST(Config_Network_Manager_should_initialize_with_the_default_state);
        RUN_TEST(Config_Network_Manager_should_initialize_with_the_serialized_state);
        RUN_TEST(Config_Network_Manager_should_apply_the_deserialization_action);
        RUN_TEST(Config_Network_Manager_should_apply_the_set_access_point_timeout_action);
        RUN_TEST(Config_Network_Manager_should_apply_the_next_mode_action);
        RUN_TEST(Config_Network_Manager_should_apply_the_set_perm_mode_action);
        RUN_TEST(Config_Network_Manager_should_apply_the_set_temp_mode_action);
      }

    }
  }
}
