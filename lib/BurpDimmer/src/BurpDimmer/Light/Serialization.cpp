#include "Status.hpp"
#include "Serialization.hpp"

namespace BurpDimmer {
  namespace Light {

    constexpr char onField[] = "on";
    constexpr char levelField[] = "level";
    constexpr char pwmField[] = "pwm";

    Serialization::Serialization() :
      BurpSerialization::Serialization(_root),
      _on({
        Status::ok,
        Status::noOn,
        Status::invalidOn
      }, root.on),
      _level({
        Status::ok,
        Status::noLevel,
        Status::invalidLevel
      }, root.level),
      _pwm({
        Status::ok,
        // pwm field can be skipped but if it's there
        // it should match the level field and the level
        // will be changed to the nearest level if it doesn't
        Status::ok,
        Status::invalidPwm
      }, root.pwm),
      _root({
        Object::Entry({onField, &_on}),
        Object::Entry({levelField, &_level}),
        Object::Entry({pwmField, &_pwm})
      }, {
        Status::ok,
        Status::noObject,
        Status::invalidObject
      }, root.isNull)
    {}

  }
}
