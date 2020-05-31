#ifndef Redux_ReducerMap_hpp
#define Redux_ReducerMap_hpp

#include "./Reducer.hpp"
#include "./ReducerMapMacros.hpp"

namespace Redux {

  template <class ActionType, class DerivedState>
  class ReducerMap : public Reducer<ActionType> {

    public:

      const State * init() const override {
        return new DerivedState;
      }

      const State * reduce(const State * state, const Action<ActionType> & action) const override {
        return new DerivedState(state->as<DerivedState>(), action);
      }

  };

}

#endif
