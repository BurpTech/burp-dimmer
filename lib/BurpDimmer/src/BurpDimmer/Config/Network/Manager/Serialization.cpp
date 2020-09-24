#include "Status.hpp"
#include "Serialization.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        constexpr char modeField[] = "mode";
        constexpr char accessPointTimeoutField[] = "accessPointTimeout";
        constexpr char modeNormalString[] = "normal";
        constexpr char modeAccessPointString[] = "accessPoint";
        constexpr char modeOffString[] = "off";

        Serialization::Serialization() :
          BurpSerialization::Serialization(_root),
          _mode({
            ModeMap::Choice({modeNormalString, PermMode::NORMAL}),
            ModeMap::Choice({modeAccessPointString, PermMode::ACCESS_POINT}),
            ModeMap::Choice({modeOffString, PermMode::OFF})
          }, {
            Status::ok,
            Status::noMode,
            Status::invalidMode,
            Status::unknownMode
          }, root.mode),
          _accessPointTimeout({
            Status::ok,
            Status::noAccessPointTimeout,
            Status::invalidAccessPointTimeout
          }, root.accessPointTimeout),
          _root({
            Object::Entry({modeField, &_mode}),
            Object::Entry({accessPointTimeoutField, &_accessPointTimeout}),
          }, {
            Status::ok,
            Status::noObject,
            Status::invalidObject
          }, root.isNull)
        {}

      }
    }
  }
}
