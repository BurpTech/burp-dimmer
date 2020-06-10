#pragma once

#include <Redux/Subscriber.hpp>
#include <functional>

template <class State>
class TestSubscriber : public Redux::Subscriber<State> {

  public:

    using f_cb = std::function<void()>;

    TestSubscriber() :
      _cb(nullptr),
      _callback(false)
    {}

    void notify(const State * state) override {
      _callback = true;
    }

    void loop() {
      if (_callback) {
        _callback = false;
        if (_cb) {
          f_cb cb = _cb;
          _cb = nullptr;
          cb();
        }
      }
    }

    void callbackOnce(f_cb cb) {
      _cb = cb;
    }

  private:

    f_cb _cb;
    bool _callback;

};
