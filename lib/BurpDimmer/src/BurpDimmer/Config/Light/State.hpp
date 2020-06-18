#pragma once

#include <array>
#include <Json/Serializer.hpp>
#include <Memory/Pair.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      constexpr char levelsField[] = "levels";
      constexpr unsigned char maxLevels = 50;
      using Levels = std::array<unsigned char, maxLevels>;
      using Params = Levels;

      class State : public Json::Serializer {

        public:
          
          const Levels levels;

          State(const Levels * levels);
          void serialize(JsonObject & object) const override;

      };

      extern Memory::Pair<State, Levels> memory;

    }
  }
}
