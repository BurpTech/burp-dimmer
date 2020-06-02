#pragma once

#include <functional>

#define COMPONENTS_LIGHT_MAX_BRIGHTNESS 25

namespace Components {

  class Light {

    public:

      using f_onUpdate = std::function<void(bool on, int brightness)>;

      Light(int pin, f_onUpdate onUpdate);
      void setup();
      void toggle();
      void setOn(bool on);
      void setBrightness(int brightness);
      void changeBrightness(int change);

    private:

      int _pin;
      bool _on;
      int _brightness;
      f_onUpdate _onUpdate;

      void _update();

  };

}
