#include "./Redux.hpp"
#include <unity.h>

#include <Redux/Action.hpp>
#include <Redux/State.hpp>
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

  class Foo : public State {
    public:
      Foo(int value) :
        value(value) {
      }

      int value;
  };

  class Bar : public State {
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
      const State * init(const State * state, const f_withInit withInit) const {
        return withInit([&](const int * pValue) {
          return _alloc(
            state->as<Foo>(),
            [&](void * address) {
              return new(address) Foo(*pValue);
            }
          );
        });
      }
      const State * reduce(const State * state, const Action<TestActionType> & action) const {
        switch (action.type) {
          case TestActionType::INCREMENT_ALL:
          case TestActionType::INCREMENT_FOO: {
            const Foo * foo = state->as<Foo>();
            return _alloc(
              foo,
              [&](void * address) {
                return new(address) Foo(foo->value + 1);
              }
            );
          }
          default:
            return state;
        }
      }
  };
  FooReducer fooReducer;

  class BarReducer : public Reducer<Bar, TestActionType, int> {
    public:
      const State * init(const State * state, const f_withInit withInit) const {
        return withInit([&](const int * pValue) {
          return _alloc(
            state->as<Bar>(),
            [&](void * address) {
              return new(address) Bar(*pValue);
            }
          );
        });
      }
      const State * reduce(const State * state, const Action<TestActionType> & action) const {
        switch (action.type) {
          case TestActionType::INCREMENT_ALL:
          case TestActionType::INCREMENT_BAR: {
            const Bar * bar = state->as<Bar>();
            return _alloc(
              bar,
              [&](void * address) {
                return new(address) Bar(bar->value + 1);
              }
            );
          }
          default:
            return state;
        }
      }
  };
  BarReducer barReducer;

  using InitialValues = struct {
    int foo;
    int bar;
  };

  class Top : public Redux::State {
    public:
      const Foo * foo;
      const Bar * bar;

      Top(const Top * previous, const InitialValues * values) :
        foo(fooReducer.init(
          previous ? previous->foo : nullptr,
          [&](Redux::Reducer<Foo, TestActionType, int>::f_doInit doInit) {
            return doInit(&(values->foo));
          }
        )->as<Foo>()),
        bar(barReducer.init(
          previous ? previous->bar : nullptr,
          [&](Redux::Reducer<Bar, TestActionType, int>::f_doInit doInit) {
            return doInit(&(values->bar));
          }
        )->as<Bar>()) {
      }

      Top(const Top * previous, const Redux::Action<TestActionType> & action) :
        foo(fooReducer.reduce(previous->foo, action)->as<Foo>()),
        bar(barReducer.reduce(previous->bar, action)->as<Bar>()) {
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
        const Top * top = store.getState();
        foo = top->foo->value;
      }
  };
  FooSubscriber fooSubscriber;

  class BarSubscriber : public Subscriber {
    public:
      void notify() override {
        const Top * top = store.getState();
        bar = top->bar->value;
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
      [&](Redux::Reducer<Top, TestActionType, InitialValues>::f_doInit doInit) {
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
