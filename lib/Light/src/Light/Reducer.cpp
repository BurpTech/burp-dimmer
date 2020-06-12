#include "Reducer.hpp"

namespace Light {

  const State * Reducer::init(const State * previous, const JsonObject & object) const {
    return alloc(
      previous,
      [&](void * address) {
        return new(address) State(previous, object);
      }
    );
  }

  const State * Reducer::reduce(const State * previous, const Action & action) const {
    switch (action.type) {
      case ActionType::DESERIALIZE: {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(
              previous,
              *(action.payload<JsonObject>())
            );
          }
        );
      }
      case ActionType::TOGGLE: {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(
              *previous,
              !(previous->on)
            );
          }
        );
      }
      case ActionType::TURN_ON: {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(
              *previous,
              true
            );
          }
        );
      }
      case ActionType::TURN_OFF: {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(
              *previous,
              false
            );
          }
        );
      }
      case ActionType::SET_BRIGHTNESS: {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(
              *previous,
              *(action.payload<unsigned char>())
            );
          }
        );
      }
      case ActionType::INCREASE_BRIGHTNESS: {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(
              *previous,
              Change::increase
            );
          }
        );
      }
      case ActionType::DECREASE_BRIGHTNESS: {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(
              *previous,
              Change::decrease
            );
          }
        );
      }
      case ActionType::APPLY_CONFIG: {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(
              *previous
            );
          }
        );
      }
      default:
        return previous;
    }
  }

}
