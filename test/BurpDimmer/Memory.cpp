#include "Memory/Pair.hpp"
#include "Memory.hpp"

namespace BurpDimmerTest {
  namespace Memory {
    Module tests("Memory", [](Describe & describe) {

      describe.include(Pair::tests);

    });
  }
}
