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
      Foo(int value = 0) :
        value(value) {
      }

      int value;
  };

  class Bar : public State {
    public:
      Bar(int value = 0) :
        value(value) {
      }

      int value;
  };

  //
  // Reducers
  //

  class FooReducer : public Reducer<Foo, TestActionType> {
    public:
      const State * init(const State * state) const {
        return _alloc([&](void * address) {
            return new(address) Foo;
        }, state->as<Foo>());
      }
      const State * reduce(const State * state, const Action<TestActionType> & action) const {
        switch (action.type) {
          case TestActionType::INCREMENT_ALL:
          case TestActionType::INCREMENT_FOO: {
            const Foo * foo = state->as<Foo>();
            return _alloc([&](void * address) {
                return new(address) Foo(foo->value + 1);
            }, foo);
          }
          default:
            return state;
        }
      }
  };
  FooReducer fooReducer;

  class BarReducer : public Reducer<Bar, TestActionType> {
    public:
      const State * init(const State * state) const {
        return _alloc([&](void * address) {
            return new(address) Bar;
        }, state->as<Bar>());
      }
      const State * reduce(const State * state, const Action<TestActionType> & action) const {
        switch (action.type) {
          case TestActionType::INCREMENT_ALL:
          case TestActionType::INCREMENT_BAR: {
            const Bar * bar = state->as<Bar>();
            return _alloc([&](void * address) {
                return new(address) Bar(bar->value + 1);
            }, bar);
          }
          default:
            return state;
        }
      }
  };
  BarReducer barReducer;

  REDUX_REDUCERMAP_STATE_2(
    Top, TestActionType,
    Foo, foo, fooReducer,
    Bar, bar, barReducer
  );
  ReducerMap<Top, TestActionType> reducer;

  //
  // Store
  //

  Store<Top, TestActionType> store;

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
    TEST_ASSERT_EQUAL_INT(0, foo);
    TEST_ASSERT_EQUAL_INT(0, bar);
    store.dispatch(incrementAll);
    TEST_ASSERT_EQUAL_INT(1, foo);
    TEST_ASSERT_EQUAL_INT(1, bar);
    store.dispatch(incrementFoo);
    TEST_ASSERT_EQUAL_INT(2, foo);
    TEST_ASSERT_EQUAL_INT(1, bar);
    store.dispatch(incrementBar);
    TEST_ASSERT_EQUAL_INT(2, foo);
    TEST_ASSERT_EQUAL_INT(2, bar);
  }

  void test() {
    RUN_TEST(Redux_should_notify_subscribers_with_new_state_after_dispatching_actions_to_reducers);
  }
}
