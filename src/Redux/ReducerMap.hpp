#ifndef Redux_ReducerMap_hpp
#define Redux_ReducerMap_hpp

#include <functional>

#include "./Reducer.hpp"

namespace Redux {
  using f_init = std::function<const State *()>;
  using f_reduce = std::function<const State *(const State * substate)>;

  template <class T>
  class ReducerMap : public Reducer {

    public:

      ReducerMap(const Reducer ** reducers) :
        _reducers(reducers) {
      }

      const State * init() const {
        const Reducer ** reducer = _reducers;
        const T * t = new T([&]() {
          return (*(reducer++))->init();
        });
        return t;
      }

      const State * reduce(const State * state, const Action & action) const {
        const T * oldT = static_cast<const T *>(state);
        const Reducer ** reducer = _reducers;
        const T * t = new T(oldT, [&](const State * substate) {
          return (*(reducer++))->reduce(substate, action);
        });
        delete oldT;
        return t;
      }

    private:
      const Reducer ** _reducers;

  };

}

#endif
