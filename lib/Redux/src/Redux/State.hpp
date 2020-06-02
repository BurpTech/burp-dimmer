#pragma once

namespace Redux {
  class State {
    public:

      template <class DerivedState>
      const DerivedState * as() const {
        return static_cast<const DerivedState *>(this);
      }

  };
}
