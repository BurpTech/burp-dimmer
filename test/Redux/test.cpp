#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>

#include "../src/Util/List.hpp"
#include "../src/Redux/Action.hpp"
#include "../src/Redux/State.hpp"
#include "../src/Redux/ReducerMap.hpp"
#include "../src/Redux/SubscriberList.hpp"
#include "../src/Redux/Store.hpp"

using namespace Redux;

//
// Store
//

Store store;

//
// Actions
//

enum {
  INCREMENT_ALL,
  INCREMENT_FOO,
  INCREMENT_BAR
};

const Action incrementAll(INCREMENT_ALL);
const Action incrementFoo(INCREMENT_FOO);
const Action incrementBar(INCREMENT_BAR);

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

class FooReducer : public Reducer {
  public:
    const State * init() const {
      return new Foo(0);
    }
    const State * reduce(const State * state, const Action & action) const {
      switch (action.type) {
        case INCREMENT_ALL:
        case INCREMENT_FOO:
          const Foo * foo = new Foo(state->as<Foo>()->value + 1);
          delete state;
          state = foo;
          break;
      }
      return state;
    }
};
FooReducer fooReducer;

class BarReducer : public Reducer {
  public:
    const State * init() const {
      return new Bar(0);
    }
    const State * reduce(const State * state, const Action & action) const {
      switch (action.type) {
        case INCREMENT_ALL:
        case INCREMENT_BAR:
          Bar * bar = new Bar(state->as<Bar>()->value + 1);
          delete state;
          state = bar;
          break;
      }
      return state;
    }
};
BarReducer barReducer;

REDUX_REDUCERMAP_STATE_2(
  Top,
  Foo, foo, fooReducer,
  Bar, bar, barReducer
);
ReducerMap<Top> reducer;

//
// Subscribers
//

int foo = 1000;
int bar = 1000;

class FooSubscriber : public Subscriber {
  public:
    void notify() const {
      const Top * top = store.getState<Top>();
      foo = top->foo->value;
    }
};
const FooSubscriber fooSubscriber;

class BarSubscriber : public Subscriber {
  public:
    void notify() const {
      const Top * top = store.getState<Top>();
      bar = top->bar->value;
    }
};
const BarSubscriber barSubscriber;

const Subscriber * subscribers[] = {
  &fooSubscriber,
  &barSubscriber,
  NULL
};
SubscriberList subscriber(subscribers);

void test() {
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

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test);
  UNITY_END();
}

void loop() {
}

int main() {
  setup();
}
