#pragma once

#include <Redux/Action.hpp>

namespace BurpDimmer {
  namespace Light {

    enum class ActionType {
      SET_STATE
    };

    using Action = Redux::Action<ActionType>;

    template <class Error>
    using f_onAction = std::function<void(const Error error, const Action * state)>;
    template <class Error, class State>
    using f_onState = std::function<void(const Error error, const State * state)>;
    template <class Error, class State>
    using f_getState = std::function<void(f_onState<Error, State> onState)>;

    template <class Error, class State, ActionType ACTION>
    void action(f_getState<Error, State> getState, f_onAction<Error> onAction) {
      return getState([](const Error error, const State * state) {
        if (error == Error::noError) {
          Action action(ACTION, &state);
          return onAction(error, &action);
        }
        return onAction(error, nullptr);
      });
    }

  }
}
