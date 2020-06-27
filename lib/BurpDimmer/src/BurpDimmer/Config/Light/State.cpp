#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {
      namespace State {

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

        Instance::Instance(const Params & params, const unsigned long uid) :
          BurpRedux::State::Instance(uid),
          levels(params.error == Error::noError ? params.levels : defaultLevels),
          saveStateDelay(params.error == Error::noError ? params.saveStateDelay : defaultSaveStateDelay),
          offLevel(params.error == Error::noError ? params.offLevel : defaultOffLevel)
        {}

        void Instance::serialize(const JsonObject & object) const {
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

      }
    }
  }
}
