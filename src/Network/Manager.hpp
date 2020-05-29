#ifndef Network_Manager_hpp
#define Network_Manager_hpp

#include <Arduino.h>
#include <functional>

#include "../Debug.hpp"

#include "../Error.hpp"
#include "Mode/Mode.hpp"

namespace Network {
  class Manager {
    public:
      using f_callback = std::function<void(Error * error)>;

      Manager(Mode::Mode ** modes) :
        _modes(modes) {
      }

      void setup() {
        Mode::Mode ** mode = _modes;
        while (*mode) {
          DEBUG_PRINT("mode: [%s]: [%s]", (*mode)->name, (*mode)->displayName);
          (*mode)->setup();
          mode++;
        }
      }

      void loop() {
        Mode::Mode ** mode = _modes;
        while (*mode) {
          (*mode)->loop();
          mode++;
        }
      }

      void select(f_callback cb, int index) {
      }

    private:
      Mode::Mode ** _modes;
  };
};

#endif
