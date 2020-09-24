#pragma once

#include <BurpSerialization/Serialization.hpp>
#include <BurpSerialization/CStrMap.hpp>
#include <BurpSerialization/Scalar.hpp>
#include <BurpSerialization/Object.hpp>
#include "Types.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        class Serialization : public BurpSerialization::Serialization {

          private:

              using ModeMap = BurpSerialization::CStrMap<PermMode, PermMode::count>;
              using TimeoutScalar = BurpSerialization::Scalar<Timeout>;

          public:

              struct {
                  bool isNull = false;
                  ModeMap::Value mode;
                  TimeoutScalar::Value accessPointTimeout;
              } root;

              Serialization();

          private:

              using Object = BurpSerialization::Object<2>;

              const ModeMap _mode;
              const TimeoutScalar _accessPointTimeout;
              const Object _root;

        };

      }
    }
  }
}
