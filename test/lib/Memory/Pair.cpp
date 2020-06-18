#include "Pair.hpp"

namespace MemoryTest {
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

        State(const Params & params) :
          intData(params.intData)
        {
          strlcpy(strData, params.strData, strSize);
        }

    };

    Pair<State, Params> pair;
    State * first = nullptr;
    State * second = nullptr;
    State * third = nullptr;

    Module tests("Pair", [](Describe & describe) {
        describe.describe("persist", [](Describe & decsribe) {
            describe.before([]() {
                Params params = {
                  "This is a test",
                  1234
                };
                first = pair.persist(params);
            });

            describe.it("should provide a pointer to a persistent state", []() {
                TEST_ASSERT_EQUAL_STRING("This is a test", first->strData);
                TEST_ASSERT_EQUAL(1234, first->intData);
            });

            describe.describe("then persist again", [](Describe & decsribe) {
                describe.before([]() {
                    Params params = {
                      "apple",
                      4321
                    };
                    second = pair.persist(params);
                });

                describe.it("should provide a new pointer to a persistent state", []() {
                    TEST_ASSERT_FALSE(second == first);
                    TEST_ASSERT_EQUAL_STRING("apple", second->strData);
                    TEST_ASSERT_EQUAL(4321, second->intData);
                });

                describe.describe("then persist a 3rd time", [](Describe & decsribe) {
                    describe.before([]() {
                        Params params = {
                          "banana",
                          5555
                        };
                        third = pair.persist(params);
                    });

                    describe.it("should reuse the first pointer for the persistent state", []() {
                        TEST_ASSERT_FALSE(third == second);
                        TEST_ASSERT_TRUE(third == first);
                        TEST_ASSERT_EQUAL_STRING("apple", third->strData);
                        TEST_ASSERT_EQUAL(4321, third->intData);
                    });
                });
            });
        });
    });

  }
}
