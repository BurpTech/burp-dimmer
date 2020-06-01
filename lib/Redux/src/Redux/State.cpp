#include "./State.hpp"

namespace Redux {

  const State * State::replace(const State * previous, const State * next) {
    delete previous;
    return next;
  }

}
