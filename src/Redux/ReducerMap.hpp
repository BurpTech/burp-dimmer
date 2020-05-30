#ifndef Redux_ReducerMap_hpp
#define Redux_ReducerMap_hpp

#include "./Reducer.hpp"
#include "./ReducerMapMacros.hpp"

namespace Redux {

  template <class T>
  class ReducerMap : public Reducer {

    public:

      const State * init() const {
        return new T;
      }

      const State * reduce(const State * state, const Action & action) const {
        return new T(state->as<T>(), action);
      }

  };

}

#endif
