#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {
      namespace State {

        Memory memory;

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
        constexpr unsigned long defaultSaveStateDelay = 5000;
        constexpr unsigned char defaultOffLevel = 24;

        Instance::Instance(const Params * params, unsigned long sequenceId) :
          levels(params ? params->levels : defaultLevels),
          saveStateDelay(params ? params->saveStateDelay : defaultSaveStateDelay),
          offLevel(params ? params->offLevel : defaultOffLevel),
          sequenceId(sequenceId)
        {}

        void Instance::serialize(JsonObject & object) const {
          JsonArray array = object[levelsField].as<JsonArray>();
          for (unsigned char i = 0; i < maxLevels; i++) {
            // break out at the first zero as this
            // will be the end of the levels
            if (levels[i] == 0) {
              return;
            }
            array.add(levels[i]);
          }
          object[saveStateDelayField] = saveStateDelay;
          object[offLevelField] = offLevel;
        }

        unsigned long Instance::getUid() const {
          return sequenceId;
        }

      }
    }
  }
}
