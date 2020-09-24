#include "Status.hpp"
#include "Serialization.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      constexpr char levelsField[] = "levels";
      constexpr char saveStateDelayField[] = "saveStateDelay";
      constexpr char offLevelField[] = "offLevelField";

      Serialization::Serialization() :
        BurpSerialization::Serialization(_root),
        _levels({
          Status::ok,
          Status::noLevels,
          Status::invalidLevels,
          Status::maxLevels,
          Status::minLevels,
          Status::levelZero,
          Status::levelNotIncreasing,
          Status::levelNotPresent,
          Status::levelWrongType
        }, root.levels),
        _saveStateDelay({
          Status::ok,
          Status::noSaveStateDelay,
          Status::invalidSaveStateDelay
        }, root.saveStateDelay),
        _offLevel({
          Status::ok,
          Status::noOffLevel,
          Status::invalidOffLevel
        }, root.offLevel),
        _root({
          Object::Entry({levelsField, &_levels}),
          Object::Entry({saveStateDelayField, &_saveStateDelay}),
          Object::Entry({offLevelField, &_offLevel})
        }, {
          Status::ok,
          Status::noObject,
          Status::invalidObject
        }, root.isNull)
      {}

    }
  }
}
