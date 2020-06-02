#include "./Redux.hpp"
#include <unity.h>

#include <Redux/Action.hpp>
#include <Redux/Reducer.hpp>
#include <Redux/ReducerMap.hpp>
#include <Redux/SubscriberList.hpp>
#include <Redux/Store.hpp>

namespace Redux {

  //
  // Action types
  //

  enum class TestActionType {
    INCREMENT_ALL,
    INCREMENT_FOO,
    INCREMENT_BAR
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
      const Foo * init(const Foo * previous, const f_withInit withInit) const {
        return withInit([&](const int * pValue) {
          return alloc(
            previous,
            [&](void * address) {
              return new(address) Foo(*pValue);
            }
          );
        });
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
          default:
            return previous;
        }
      }
  };
  FooReducer fooReducer;

  class BarReducer : public Reducer<Bar, TestActionType, int> {
    public:
      const Bar * init(const Bar * previous, const f_withInit withInit) const {
        return withInit([&](const int * pValue) {
          return alloc(
            previous,
            [&](void * address) {
              return new(address) Bar(*pValue);
            }
          );
        });
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
          default:
            return previous;
        }
      }
  };
  BarReducer barReducer;

  using InitialValues = struct {
    int foo;
    int bar;
  };

  class Top {
    public:
      const Foo * foo;
      const Bar * bar;

      Top(const Top * previous, const InitialValues * values) :
        foo(fooReducer.init(
          previous ? previous->foo : nullptr,
          [&](Reducer<Foo, TestActionType, int>::f_doInit doInit) {
            return doInit(&(values->foo));
          }
        )),
        bar(barReducer.init(
          previous ? previous->bar : nullptr,
          [&](Reducer<Bar, TestActionType, int>::f_doInit doInit) {
            return doInit(&(values->bar));
          }
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

  class FooSubscriber : public Subscriber {
    public:
      void notify() override {
        foo = store.state->foo->value;
      }
  };
  FooSubscriber fooSubscriber;

  class BarSubscriber : public Subscriber {
    public:
      void notify() override {
        bar = store.state->bar->value;
      }
  };
  BarSubscriber barSubscriber;

  Subscriber * subscribers[] = {
    &fooSubscriber,
    &barSubscriber,
    nullptr
  };
  SubscriberList subscriber(subscribers);

  void Redux_should_notify_subscribers_with_new_state_after_dispatching_actions_to_reducers() {
    TEST_ASSERT_EQUAL_INT(1000, foo);
    TEST_ASSERT_EQUAL_INT(1000, bar);
    store.setup(&reducer, &subscriber);
    InitialValues initialValues = {
      5, 24
    };
    store.init(
      [&](Reducer<Top, TestActionType, InitialValues>::f_doInit doInit) {
        return doInit(&initialValues);
      }
    );
    TEST_ASSERT_EQUAL_INT(5, foo);
    TEST_ASSERT_EQUAL_INT(24, bar);
    store.dispatch(incrementAll);
    TEST_ASSERT_EQUAL_INT(6, foo);
    TEST_ASSERT_EQUAL_INT(25, bar);
    store.dispatch(incrementFoo);
    TEST_ASSERT_EQUAL_INT(7, foo);
    TEST_ASSERT_EQUAL_INT(25, bar);
    store.dispatch(incrementBar);
    TEST_ASSERT_EQUAL_INT(7, foo);
    TEST_ASSERT_EQUAL_INT(26, bar);
  }

  void test() {
    RUN_TEST(Redux_should_notify_subscribers_with_new_state_after_dispatching_actions_to_reducers);
  }
}
