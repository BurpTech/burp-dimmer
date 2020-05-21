#ifndef Light_hpp
#define Light_hpp

#include "Debug.hpp"

#define LIGHT_MAX_BRIGHTNESS 25

#define _LIGHT_DEFAULT_BRIGHTNESS LIGHT_MAX_BRIGHTNESS
#define _LIGHT_DEFAULT_ON false

#define _LIGHT_LIMIT_BRIGHTNESS(BRIGHTNESS) ((BRIGHTNESS) < 0 ? 0 : ((BRIGHTNESS) > LIGHT_MAX_BRIGHTNESS ? LIGHT_MAX_BRIGHTNESS : (BRIGHTNESS))) 
#define _LIGHT_PWM_LEVEL(BRIGHTNESS) (int((float(BRIGHTNESS) / float(LIGHT_MAX_BRIGHTNESS)) * 255))

class Light {
  using f_onUpdate = std::function<void(bool on, int brightness)>;

  int _pin;
  bool _on;
  int _brightness;
  f_onUpdate _onUpdate;
  void _update();

  public:
    Light(int pin, f_onUpdate onUpdate);
    void setup();
    void toggle();
    void setOn(bool on);
    void setBrightness(int brightness);
    void changeBrightness(int change);
};

Light::Light(int pin, f_onUpdate onUpdate) {
  _pin = pin;
  _onUpdate = onUpdate;
  _brightness = _LIGHT_DEFAULT_BRIGHTNESS;
  _on = _LIGHT_DEFAULT_ON;
}

void Light::setup() {
  pinMode(_pin, OUTPUT);
  _update();
}

void Light::_update() {
  if (_brightness == 0) {
    _on = false;
    _brightness = LIGHT_MAX_BRIGHTNESS;
  }

  if (!_on) {
    digitalWrite(_pin, LOW);
  } else {
    int pwmLevel = _LIGHT_PWM_LEVEL(_brightness);
    DEBUG_VAL(F("setting output"), F("pwmLevel"), pwmLevel);
    analogWrite(_pin, pwmLevel);
  }

  _onUpdate(_on, _brightness);
}

void Light::toggle() {
  _on = !_on;
  _update();
}

void Light::setOn(bool on) {
  _on = on;
  _update();
}

void Light::setBrightness(int brightness) {
  _on = true;
  _brightness = _LIGHT_LIMIT_BRIGHTNESS(brightness);
  _update();
}

void Light::changeBrightness(int change) {
  if (_on) {
    _brightness = _LIGHT_LIMIT_BRIGHTNESS(_brightness + change);
    _update();
  } else if (change > 0) {
    _on = true;
    _brightness = _LIGHT_LIMIT_BRIGHTNESS(change);
    _update();
  }
}

#endif
