#pragma once

#include <functional>

namespace TestHelpers {

  class TestAsync {

    public:

      using f_cb = std::function<void()>;

      TestAsync() :
        _cb(nullptr)
      {}

      void loop() {
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
