#pragma once

#include <ArduinoJson.h>
#include "../../../Util/Debug.hpp"
#include "../../../Json/Deserializer.hpp"
#include "../../../Redux/Reducer.hpp"
#include "../../../Redux/State.hpp"
#include "../../../Redux/Action.hpp"
#include "../../ActionType.hpp"
#include "./Actions.hpp"
#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {

      class Reducer : public Json::Deserializer, public Redux::Reducer<ActionType> {

        public:

          void deserialize(const JsonObject & object) override {
            _initialState = new State(object);
          }

          const Redux::State * init() const override {
            return _initialState;
          }

          const Redux::State * reduce(const Redux::State *state, const Redux::Action<ActionType> &action) const override {
            switch (action.type) {
              case ActionType::NETWORK_MANAGER_DESERIALIZE: {
                return Redux::State::replace(state, new State(
                  action.as<Actions::Deserialize>().object
                ));
              }
              case ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT: {
                return Redux::State::replace(state, new State(
                  *(state->as<State>()),
                  action.as<Actions::SetAccessPointTimeout>().timeout
                ));
              }
              case ActionType::NETWORK_MANAGER_NEXT_PERM_MODE: {
                return Redux::State::replace(state, _createNextPermMode(
                  *(state->as<State>())
                ));
              }
              case ActionType::NETWORK_MANAGER_SET_PERM_MODE: {
                return Redux::State::replace(state, new State(
                  *(state->as<State>()),
                  action.as<Actions::SetPermMode>().mode
                ));
              }
              case ActionType::NETWORK_MANAGER_SET_TEMP_MODE: {
                return Redux::State::replace(state, new State(
                  *(state->as<State>()),
                  action.as<Actions::SetTempMode>().mode
                ));
              }
              default:
                return state;
            }
          }

        private:

          const State * _initialState = nullptr;

          static const State * _createNextPermMode(const State & previous) {
            switch (previous.permMode) {
              case State::PermMode::NORMAL:
                return new State(previous, State::PermMode::ACCESS_POINT);
              case State::PermMode::ACCESS_POINT:
                return new State(previous, State::PermMode::OFF);
              case State::PermMode::OFF:
                return new State(previous, State::PermMode::NORMAL);
            }
          }

      };

    }
  }
}
