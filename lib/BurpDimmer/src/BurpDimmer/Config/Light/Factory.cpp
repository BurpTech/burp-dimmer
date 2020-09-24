#include "Serialization.hpp"
#include "Factory.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      constexpr Levels defaultLevels = {
        10,
        20,
        31,
        41,
        51,
        61,
        71,
        82,
        92,
        102,
        112,
        122,
        133,
        143,
        153,
        163,
        173,
        184,
        194,
        204,
        214,
        224,
        235,
        245,
        255
      };
      constexpr Delay defaultSaveStateDelay = 5000;
      constexpr LevelIndex defaultOffLevel = 24;

      bool Factory::deserialize(const JsonVariant & serialized) {
        return create([&]() -> const State * {
          Serialization serialization;
          auto code = serialization.deserialize(serialized);
          if (code == Status::ok) {
            if (serialization.root.offLevel.value >= serialization.root.levels.length) {
              return error(Status::offLevelOutOfRange);
            }
            return ok(new(getAddress()) State(
              serialization.root.levels.list,
              serialization.root.saveStateDelay.value,
              serialization.root.offLevel.value
            ));
          };
          return error(code);
        });
      }

      bool Factory::createDefault() {
        return create([&]() -> const State * {
            return ok(new(getAddress()) State(
              defaultLevels,
              defaultSaveStateDelay,
              defaultOffLevel
            ));
        });
      }

    }
  }
}
