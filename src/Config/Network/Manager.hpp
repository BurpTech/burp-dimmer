#ifndef Config_Network_Manager_hpp
#define Config_Network_Manager_hpp

#include <ArduinoJson.h>

#include "../../Util/Debug.hpp"

#include "../../Json/Object.hpp"
#include "../../Redux/State.hpp"
#include "../../Redux/Reducer.hpp"
#include "../../Redux/Action.hpp"
#include "../ActionType.hpp"

namespace Config {
  namespace Network {

    using namespace Redux;
    using namespace Json;

    class Manager : public Object, public State {
      public:

        enum class Mode {
          NORMAL,
          ACCESS_POINT,
          WPS_CONFIG,
          OFF
        };

        static constexpr char MODE_FIELD[] = "mode";
        static constexpr Mode DEFAULT_MODE = Mode::NORMAL;

        Mode mode;

        Manager(const Mode mode = Manager::DEFAULT_MODE) :
          mode(mode) {
        }

        void serialize(JsonObject & object) {
          object[Manager::MODE_FIELD] = static_cast<int>(mode);
        }

        void deserialize(JsonObject & object) {
          mode = static_cast<Mode>(object[Manager::MODE_FIELD].as<int>());
        }

    };

    constexpr char Manager::MODE_FIELD[];
    constexpr Manager::Mode Manager::DEFAULT_MODE;

    class ManagerSetModeAction: public Action<ActionType> {

      public:

        Manager::Mode mode;

        ManagerSetModeAction(Manager::Mode mode) : 
          Action(ActionType::NETWORK_MANAGER_SET_MODE),
          mode(mode) {
        }

    };

    class ManagerReducer : public Reducer<ActionType> {

      public:

        const State * init() const override {
          return new Manager;
        }

        const State * reduce(const State *state, const Action<ActionType> &action) const override {
          switch (action.type) {
            case ActionType::NETWORK_MANAGER_SET_MODE: {
              Manager * manager = new Manager(action.as<ManagerSetModeAction>().mode);
              delete state;
              return manager;
            }
            default:
              return state;
          }
        }

    };

  }
}

#endif
