#include "./Redux.hpp"
#include <functional>
#include <unity.h>

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

  Store<Top, TestActionType, InitialValues> store;

  //
  // Subscribers
  //

  int foo = 1000;
  int bar = 1000;

  class FooSubscriber : public Subscriber<Top> {
    public:
      void notify(const Top * state) override {
        foo = state->foo->value;
      }
  };
  FooSubscriber fooSubscriber;

  class BarSubscriber : public Subscriber<Top> {
    public:
      void notify(const Top * state) override {
        bar = state->bar->value;
      }
  };
  BarSubscriber barSubscriber;

  class TestSubscriber : public Subscriber<Top> {
    public:
      using f_cb = std::function<void(const Top * state)>;

      TestSubscriber() :
        _cb(nullptr)
      {}

      void notify(const Top * state) override {
        if (_cb) {
          _cb(state);
          _cb = nullptr;
        }
      }

      void callback(f_cb cb) {
        _cb = cb;
      }

    private:
      f_cb _cb;
  };
  TestSubscriber testSubscriber;

  Subscriber<Top> * subscribers[] = {
    &fooSubscriber,
    &barSubscriber,
    &testSubscriber,
    nullptr
  };
  SubscriberList<Top> subscriber(subscribers);

  Module tests("Redux", [](Describe & describe) {

    describe.loop([]() {
      store.loop();
    });

    describe.before([]() {
      store.setup(&reducer, &subscriber);
    });

    describe.it("should have the correct start values", []() {
      TEST_ASSERT_EQUAL_INT(1000, foo);
      TEST_ASSERT_EQUAL_INT(1000, bar);
    });

    describe.async("after init", [](Async & async, f_done & done) {
      InitialValues initialValues = {
        5, 24
      };
      store.init(initialValues);
      testSubscriber.callback([&](const Top * state) {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(5, state->foo->value);
          TEST_ASSERT_EQUAL_INT(24, state->bar->value);
        });
        async.it("should have notified the subscribers in order", [&]() {
          TEST_ASSERT_EQUAL_INT(5, foo);
          TEST_ASSERT_EQUAL_INT(24, bar);
        });
        done();
      });
    });

    describe.async("after increment all", [](Async & async, f_done & done) {
      store.dispatch(incrementAll);
      testSubscriber.callback([&](const Top * state) {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(6, state->foo->value);
          TEST_ASSERT_EQUAL_INT(25, state->bar->value);
        });
        async.it("should have notified the subscribers in order", [&]() {
          TEST_ASSERT_EQUAL_INT(6, foo);
          TEST_ASSERT_EQUAL_INT(25, bar);
        });
        done();
      });
    });

    describe.async("after increment foo", [](Async & async, f_done & done) {
      store.dispatch(incrementFoo);
      testSubscriber.callback([&](const Top * state) {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(7, state->foo->value);
          TEST_ASSERT_EQUAL_INT(25, state->bar->value);
        });
        async.it("should have notified the subscribers in order", [&]() {
          TEST_ASSERT_EQUAL_INT(7, foo);
          TEST_ASSERT_EQUAL_INT(25, bar);
        });
        done();
      });
    });

    describe.async("after increment bar", [](Async & async, f_done & done) {
      store.dispatch(incrementBar);
      testSubscriber.callback([&](const Top * state) {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(7, state->foo->value);
          TEST_ASSERT_EQUAL_INT(26, state->bar->value);
        });
        async.it("should have notified the subscribers in order", [&]() {
          TEST_ASSERT_EQUAL_INT(7, foo);
          TEST_ASSERT_EQUAL_INT(26, bar);
        });
        done();
      });
    });

    describe.async("after increase all", [](Async & async, f_done & done) {
      int increase = 5;
      store.dispatch(Action<TestActionType>(TestActionType::INCREASE_ALL, &increase));
      testSubscriber.callback([&](const Top * state) {
        async.it("should notify the correct state", [&]() {
          TEST_ASSERT_EQUAL_INT(12, state->foo->value);
          TEST_ASSERT_EQUAL_INT(31, state->bar->value);
        });
        async.it("should have notified the subscribers in order", [&]() {
          TEST_ASSERT_EQUAL_INT(12, foo);
          TEST_ASSERT_EQUAL_INT(31, bar);
        });
        done();
      });
    });

  });

}
