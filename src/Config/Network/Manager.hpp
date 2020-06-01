#ifndef Config_Network_Manager_hpp
#define Config_Network_Manager_hpp

#include <ArduinoJson.h>

#include "../../Util/Debug.hpp"

#include "../../Json/Serializer.hpp"
#include "../../Json/Deserializer.hpp"
#include "../../Redux/State.hpp"
#include "../../Redux/State.hpp"
#include "../../Redux/Reducer.hpp"
#include "../../Redux/Action.hpp"
#include "../ActionType.hpp"
#include "ArduinoJson.hpp"

namespace Config {
  namespace Network {

    using namespace Json;
    using namespace Redux;

    class Manager : public Serializer, public State {
      public:

        enum class PermMode {
          NORMAL,
          ACCESS_POINT,
          OFF
        };

        enum class TempMode {
          ACCESS_POINT,
          WPS_CONFIG
        };

        static constexpr char MODE_FIELD[] = "mode";
        static constexpr char ACCESS_POINT_TIMEOUT_FIELD[] = "accessPointTimeout";
        static constexpr PermMode DEFAULT_PERM_MODE = PermMode::NORMAL;
        static constexpr TempMode DEFAULT_TEMP_MODE = TempMode::ACCESS_POINT;
        static constexpr bool DEFAULT_TEMP_MODE_ACTIVE = false;
        static constexpr unsigned long DEFAULT_ACCESS_POINT_TIMEOUT = 0;

        static const Manager * deserialize(const Manager * previous, const JsonObject & object) {
          Manager * next = new Manager(object);
          return next;
        }

        static const Manager * createAccessPointTimeout(const Manager * previous, const unsigned long timeout) {
          Manager * next = new Manager(timeout);
          return next;
        }

        static const Manager * createPermMode(const Manager * previous, const PermMode mode) {
          Manager * next = new Manager(*previous, mode);
          return next;
        }

        static const Manager * createTempMode(const Manager * previous, const TempMode mode) {
          Manager * next = new Manager(*previous, mode);
          return next;
        }

        static const Manager * createNextPermMode(const Manager * previous) {
          switch (previous->permMode) {
            case PermMode::NORMAL:
              return createPermMode(previous, PermMode::ACCESS_POINT);
            case PermMode::ACCESS_POINT:
              return createPermMode(previous, PermMode::OFF);
            case PermMode::OFF:
              return createPermMode(previous, PermMode::NORMAL);
          }
        }

        const PermMode permMode;
        const TempMode tempMode;
        const bool tempModeActive;
        const unsigned long accessPointTimeout;

        Manager(const unsigned long timeout) :
          permMode(DEFAULT_PERM_MODE),
          tempMode(DEFAULT_TEMP_MODE),
          tempModeActive(DEFAULT_TEMP_MODE_ACTIVE),
          accessPointTimeout(timeout) {
        }

        Manager(const Manager & manager, PermMode mode) :
          permMode(mode),
          tempMode(DEFAULT_TEMP_MODE),
          tempModeActive(DEFAULT_TEMP_MODE_ACTIVE),
          accessPointTimeout(manager.accessPointTimeout) {
        }

        Manager(const Manager & manager, TempMode mode) :
          permMode(manager.permMode),
          tempMode(mode),
          tempModeActive(DEFAULT_TEMP_MODE_ACTIVE),
          accessPointTimeout(manager.accessPointTimeout) {
        }

        Manager(const JsonObject & object) :
          permMode(static_cast<PermMode>(object[Manager::MODE_FIELD].as<int>())),
          tempMode(DEFAULT_TEMP_MODE),
          tempModeActive(DEFAULT_TEMP_MODE_ACTIVE),
          accessPointTimeout(object[Manager::ACCESS_POINT_TIMEOUT_FIELD].as<unsigned long>()) {
        }

        void serialize(JsonObject & object) const override {
          // don't serialize the tempMode as it should not be restored
          object[Manager::MODE_FIELD] = static_cast<int>(permMode);
          object[Manager::ACCESS_POINT_TIMEOUT_FIELD] = static_cast<unsigned long>(accessPointTimeout);
        }

    };

    constexpr char Manager::MODE_FIELD[];
    constexpr char Manager::ACCESS_POINT_TIMEOUT_FIELD[];
    constexpr Manager::PermMode Manager::DEFAULT_PERM_MODE;
    constexpr Manager::TempMode Manager::DEFAULT_TEMP_MODE;
    constexpr bool Manager::DEFAULT_TEMP_MODE_ACTIVE;
    constexpr unsigned long Manager::DEFAULT_ACCESS_POINT_TIMEOUT;

    class ManagerDeserializeAction: public Action<ActionType> {
      public:
        const JsonObject & object;
        ManagerDeserializeAction(const JsonObject & object) : 
          Action(ActionType::NETWORK_MANAGER_DESERIALIZE),
          object(object) {
        }
    };

    class ManagerSetAccessPointTimeoutAction: public Action<ActionType> {
      public:
        const unsigned long timeout;
        ManagerSetAccessPointTimeoutAction(const unsigned long timeout) : 
          Action(ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT),
          timeout(timeout) {
        }
    };

    class ManagerNextModeAction: public Action<ActionType> {
      public:
        ManagerNextModeAction(const JsonObject & object) : 
          Action(ActionType::NETWORK_MANAGER_NEXT_PERM_MODE) {
        }
    };

    class ManagerSetPermModeAction: public Action<ActionType> {
      public:
        Manager::PermMode mode;
        ManagerSetPermModeAction(Manager::PermMode mode) : 
          Action(ActionType::NETWORK_MANAGER_SET_PERM_MODE),
          mode(mode) {
        }
    };

    class ManagerSetTempModeAction: public Action<ActionType> {
      public:
        Manager::TempMode mode;
        ManagerSetTempModeAction(Manager::TempMode mode) : 
          Action(ActionType::NETWORK_MANAGER_SET_TEMP_MODE),
          mode(mode) {
        }
    };

    class ManagerReducer : public Deserializer, public Reducer<ActionType> {

      public:

        const Manager * initialManager;

        void deserialize(const JsonObject & object) override {
          initialManager = new Manager(object);
        }

        const State * init() const override {
          return initialManager;
        }

        const State * reduce(const State *state, const Action<ActionType> &action) const override {
          switch (action.type) {
            case ActionType::NETWORK_MANAGER_DESERIALIZE: {
              return State::replace(state, Manager::deserialize(
                state->as<Manager>(),
                action.as<ManagerDeserializeAction>().object
              ));
            }
            case ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT: {
              return State::replace(state, Manager::createAccessPointTimeout(
                state->as<Manager>(),
                action.as<ManagerSetAccessPointTimeoutAction>().timeout
              ));
            }
            case ActionType::NETWORK_MANAGER_NEXT_PERM_MODE: {
              return State::replace(state, Manager::createNextPermMode(state->as<Manager>()));
            }
            case ActionType::NETWORK_MANAGER_SET_PERM_MODE: {
              return State::replace(state, Manager::createPermMode(
                state->as<Manager>(),
                action.as<ManagerSetPermModeAction>().mode
              ));
            }
            case ActionType::NETWORK_MANAGER_SET_TEMP_MODE: {
              return State::replace(state, Manager::createTempMode(
                state->as<Manager>(),
                action.as<ManagerSetTempModeAction>().mode
              ));
            }
            default:
              return state;
          }
        }

    };

  }
}

#endif
