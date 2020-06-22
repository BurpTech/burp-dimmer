#include <stddef.h>
#include <string.h>
#include <unity.h>
#include <BurpDimmer/Memory/Pair.hpp>
#include "Pair.hpp"

namespace BurpDimmerTest {
  namespace Memory {
    namespace Pair {

      struct Params {
        const char * strData;
        int intData;
      };

      class State {

        public: 

          static constexpr size_t strSize = 10;

          char strData[strSize];
          int intData;
          unsigned long sequenceId;

          State(const Params * params, unsigned long sequenceId) :
            intData(params->intData),
            sequenceId(sequenceId)
          {
            strlcpy(strData, params->strData, strSize);
          }

      };

      BurpDimmer::Memory::Pair<State, Params> pair;
      const State * first = nullptr;
      const State * second = nullptr;
      const State * third = nullptr;

      Module tests("Pair", [](Describe & describe) {
          describe.describe("create", [](Describe & describe) {
              describe.before([]() {
                  Params params = {
                    "This is a test",
                    1234
                  };
                  first = pair.create(&params);
              });

              describe.it("should provide a pointer to a persistent state", []() {
                  TEST_ASSERT_EQUAL_STRING("This is a", first->strData);
                  TEST_ASSERT_EQUAL(1234, first->intData);
              });

              describe.it("should set the sequence ID", []() {
                  TEST_ASSERT_EQUAL(1, first->sequenceId);
              });

              describe.describe("then create again", [](Describe & describe) {
                  describe.before([]() {
                      Params params = {
                        "apple",
                        4321
                      };
                      second = pair.create(&params);
                  });

                  describe.it("should provide a new pointer to a persistent state", []() {
                      TEST_ASSERT_FALSE(second == first);
                      TEST_ASSERT_EQUAL_STRING("apple", second->strData);
                      TEST_ASSERT_EQUAL(4321, second->intData);
                  });

                  describe.it("should set the next sequence ID", []() {
                      TEST_ASSERT_EQUAL(2, second->sequenceId);
                  });

                  describe.describe("then create a 3rd time", [](Describe & describe) {
                      describe.before([]() {
                          Params params = {
                            "banana",
                            5555
                          };
                          third = pair.create(&params);
                      });

                      describe.it("should reuse the first pointer for the persistent state", []() {
                          TEST_ASSERT_FALSE(third == second);
                          TEST_ASSERT_TRUE(third == first);
                          TEST_ASSERT_EQUAL_STRING("banana", third->strData);
                          TEST_ASSERT_EQUAL(5555, third->intData);
                      });

                      describe.it("should set the next sequence ID", []() {
                          TEST_ASSERT_EQUAL(3, third->sequenceId);
                      });
                  });
              });
          });
      });

    }
  }
}
