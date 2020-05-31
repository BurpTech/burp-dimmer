#ifndef Components_Light_hpp
#define Components_Light_hpp

#include <Arduino.h>
#include <functional>

#include "../Util/Debug.hpp"

#define COMPONENTS_LIGHT_MAX_BRIGHTNESS 25

#define _COMPONENTS_LIGHT_DEFAULT_BRIGHTNESS COMPONENTS_LIGHT_MAX_BRIGHTNESS
#define _COMPONENTS_LIGHT_DEFAULT_ON false

#define _COMPONENTS_LIGHT_LIMIT_BRIGHTNESS(BRIGHTNESS) ((BRIGHTNESS) < 0 ? 0 : ((BRIGHTNESS) > COMPONENTS_LIGHT_MAX_BRIGHTNESS ? COMPONENTS_LIGHT_MAX_BRIGHTNESS : (BRIGHTNESS))) 
#define _COMPONENTS_LIGHT_PWM_LEVEL(BRIGHTNESS) (int((float(BRIGHTNESS) / float(COMPONENTS_LIGHT_MAX_BRIGHTNESS)) * 255))

namespace Components {

  class Light {

    public:

      using f_onUpdate = std::function<void(bool on, int brightness)>;

      Light(int pin, f_onUpdate onUpdate) :
        _pin(pin),
        _on(_COMPONENTS_LIGHT_DEFAULT_ON),
        _brightness(_COMPONENTS_LIGHT_DEFAULT_BRIGHTNESS),
        _onUpdate(onUpdate) {
      }

      void setup() {
        pinMode(_pin, OUTPUT);
        _update();
      }

      void toggle() {
        _on = !_on;
        _update();
      }

      void setOn(bool on) {
        _on = on;
        _update();
      }

      void setBrightness(int brightness) {
        _on = true;
        _brightness = _COMPONENTS_LIGHT_LIMIT_BRIGHTNESS(brightness);
        _update();
      }

      void changeBrightness(int change) {
        if (_on) {
          _brightness = _COMPONENTS_LIGHT_LIMIT_BRIGHTNESS(_brightness + change);
          _update();
        } else if (change > 0) {
          _on = true;
          _brightness = _COMPONENTS_LIGHT_LIMIT_BRIGHTNESS(change);
          _update();
        }
      }

    private:

      int _pin;
      bool _on;
      int _brightness;
      f_onUpdate _onUpdate;

      void _update() {
        if (_brightness == 0) {
          _on = false;
          _brightness = COMPONENTS_LIGHT_MAX_BRIGHTNESS;
        }

        if (!_on) {
          digitalWrite(_pin, LOW);
        } else {
          int pwmLevel = _COMPONENTS_LIGHT_PWM_LEVEL(_brightness);
          DEBUG_PRINT("setting output: pwmLevel: [%d]", pwmLevel);
          analogWrite(_pin, pwmLevel);
        }

        _onUpdate(_on, _brightness);
      }

  };

}

#endif
