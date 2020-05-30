#ifndef Redux_State_State_hpp
#define Redux_State_State_hpp

namespace Redux {
  class State {
    public:

      template <class T>
      const T * as() const {
        return static_cast<const T *>(this);
      }

  };
}

#endif
