#pragma once

#include <functional>
#include <BurpRedux/Subscriber.hpp>

namespace TestHelpers {

  template <class State>
  class TestSubscriber : public BurpRedux::Subscriber<State> {

    public:

      using f_cb = std::function<void()>;

      TestSubscriber() :
        _cb(nullptr)
      {}

      void onPublish(const State * _) override {
        if (_cb) {
          f_cb cb = _cb;
          _cb = nullptr;
          cb();
        }
      }

      void callbackOnce(f_cb cb) {
        _cb = cb;
      }

    private:

      f_cb _cb;

  };

}
