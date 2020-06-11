#include "./Redux.hpp"
#include <functional>
#include <unity.h>
#include <TestHelpers/TestSubscriber.hpp>

#include <Redux/Action.hpp>
#include <Redux/Reducer.hpp>
#include <Redux/ReducerMap.hpp>
#include <Redux/SubscriberList.hpp>
#include <Redux/Store.hpp>

namespace Redux {

  struct InitialValues {
    int foo;
    int bar;
  };

  //
  // Action types
  //

  enum class TestActionType {
    INCREMENT_ALL,
    INCREMENT_FOO,
    INCREMENT_BAR,
    INCREASE_ALL
  };

  //
  // Actions
  //

  const Action<TestActionType> incrementAll(TestActionType::INCREMENT_ALL);
  const Action<TestActionType> incrementFoo(TestActionType::INCREMENT_FOO);
  const Action<TestActionType> incrementBar(TestActionType::INCREMENT_BAR);

  //
  // States
  //

  class Foo {
    public:
      Foo(int value) :
        value(value) {
      }

      int value;
  };

  class Bar {
    public:
      Bar(int value) :
        value(value) {
      }

      int value;
  };

  //
  // Reducers
  //

  class FooReducer : public Reducer<Foo, TestActionType, int> {
    public:
      const Foo * init(const Foo * previous, const int & value) const {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) Foo(value);
          }
        );
      }
      const Foo * reduce(const Foo * previous, const Action<TestActionType> & action) const {
        switch (action.type) {
          case TestActionType::INCREMENT_ALL:
          case TestActionType::INCREMENT_FOO: {
            return alloc(
              previous,
              [&](void * address) {
                return new(address) Foo(previous->value + 1);
              }
            );
          }
          case TestActionType::INCREASE_ALL:
            return alloc(
              previous,
              [&](void * address) {
                return new(address) Foo(previous->value + *(action.payload<int>()));
              }
            );
          default:
            return previous;
        }
      }
  };
  FooReducer fooReducer;

  class BarReducer : public Reducer<Bar, TestActionType, int> {
    public:
      const Bar * init(const Bar * previous, const int & value) const {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) Bar(value);
          }
        );
      }
      const Bar * reduce(const Bar * previous, const Action<TestActionType> & action) const {
        switch (action.type) {
          case TestActionType::INCREMENT_ALL:
          case TestActionType::INCREMENT_BAR: {
            return alloc(
              previous,
              [&](void * address) {
                return new(address) Bar(previous->value + 1);
              }
            );
          }
          case TestActionType::INCREASE_ALL:
            return alloc(
              previous,
              [&](void * address) {
                return new(address) Bar(previous->value + *(action.payload<int>()));
              }
            );
          default:
            return previous;
        }
      }
  };
  BarReducer barReducer;

  class Top {
    public:
      const Foo * foo;
      const Bar * bar;

      Top(const Top * previous, const InitialValues & values) :
        foo(fooReducer.init(
          previous ? previous->foo : nullptr,
          values.foo
        )),
        bar(barReducer.init(
          previous ? previous->bar : nullptr,
          values.bar
        )) {
      }

      Top(const Top * previous, const Action<TestActionType> & action) :
        foo(fooReducer.reduce(previous->foo, action)),
        bar(barReducer.reduce(previous->bar, action)) {
      }
  };
  ReducerMap<Top, TestActionType, InitialValues> reducer;

  //
  // Store
  //

  Store<Top, TestActionType, InitialValues> store(reducer);

  //
  // Subscribers
  //

  int foo = 1000;
  int bar = 1000;

  class FooSubscriber : public Subscriber {
    public:
      void notify() override {
        foo = store.getState()->foo->value;
      }
  };
  FooSubscriber fooSubscriber;

  class BarSubscriber : public Subscriber {
    public:
      void notify() override {
        bar = store.getState()->bar->value;
      }
  };
  BarSubscriber barSubscriber;

  TestHelpers::TestSubscriber testSubscriber;

  Subscriber * subscribers[] = {
    &fooSubscriber,
    &barSubscriber,
    &testSubscriber,
    nullptr
  };
  SubscriberList subscriber(subscribers);

  Module tests("Redux", [](Describe & describe) {

    describe.setup([]() {
      store.setSubscriber(&subscriber);
    });

    describe.loop([]() {
      store.loop();
      testSubscriber.loop();
    });

    describe.it("should have the correct start values", []() {
      TEST_ASSERT_EQUAL_INT(1000, foo);
      TEST_ASSERT_EQUAL_INT(1000, bar);
    });

    describe.describe("after init", [](Describe & describe) {
      describe.it("should have the correct initial state", []() {
        InitialValues initialValues = {
          5, 24
        };
        store.init(initialValues);
        TEST_ASSERT_EQUAL_INT(5, store.getState()->foo->value);
        TEST_ASSERT_EQUAL_INT(24, store.getState()->bar->value);
      });
    });

    describe.async("after increment all", [](Async & async, f_done & done) {
      store.dispatch(incrementAll);
      testSubscriber.callbackOnce([&]() {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(6, store.getState()->foo->value);
          TEST_ASSERT_EQUAL_INT(25, store.getState()->bar->value);
        });
        async.it("should have notified all the subscribers", [&]() {
          TEST_ASSERT_EQUAL_INT(6, foo);
          TEST_ASSERT_EQUAL_INT(25, bar);
        });
        done();
      });
    });

    describe.async("after increment foo", [](Async & async, f_done & done) {
      store.dispatch(incrementFoo);
      testSubscriber.callbackOnce([&]() {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(7, store.getState()->foo->value);
          TEST_ASSERT_EQUAL_INT(25, store.getState()->bar->value);
        });
        async.it("should have notified all the subscribers", [&]() {
          TEST_ASSERT_EQUAL_INT(7, foo);
          TEST_ASSERT_EQUAL_INT(25, bar);
        });
        done();
      });
    });

    describe.async("after increment bar", [](Async & async, f_done & done) {
      store.dispatch(incrementBar);
      testSubscriber.callbackOnce([&]() {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(7, store.getState()->foo->value);
          TEST_ASSERT_EQUAL_INT(26, store.getState()->bar->value);
        });
        async.it("should have notified all the subscribers", [&]() {
          TEST_ASSERT_EQUAL_INT(7, foo);
          TEST_ASSERT_EQUAL_INT(26, bar);
        });
        done();
      });
    });

    describe.async("after increase all", [](Async & async, f_done & done) {
      int increase = 5;
      store.dispatch(Action<TestActionType>(TestActionType::INCREASE_ALL, &increase));
      testSubscriber.callbackOnce([&]() {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(12, store.getState()->foo->value);
          TEST_ASSERT_EQUAL_INT(31, store.getState()->bar->value);
        });
        async.it("should have notified all the subscribers", [&]() {
          TEST_ASSERT_EQUAL_INT(12, foo);
          TEST_ASSERT_EQUAL_INT(31, bar);
        });
        done();
      });
    });

  });

}
