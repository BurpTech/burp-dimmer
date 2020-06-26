#include "RotaryEncoder.hpp"

#include <Arduino.h>

namespace BurpDimmer {
  namespace Components {

    RotaryEncoder::RotaryEncoder(int pinA, int pinB, f_interruptDispatch interruptDispatch) :
      _pinA(pinA),
      _pinB(pinB),
      _interruptDispatch(interruptDispatch),
      _onChange(nullptr) {
    }

    void RotaryEncoder::setup(f_onChange onChange) {
      _onChange = onChange;
      pinMode(_pinA, INPUT);
      pinMode(_pinB, INPUT);
      _pinAState = digitalRead(_pinA);
      _pinBState = digitalRead(_pinB);
      attachInterrupt(digitalPinToInterrupt(_pinA), _interruptDispatch, CHANGE);
      attachInterrupt(digitalPinToInterrupt(_pinB), _interruptDispatch, CHANGE);
    }

    void RotaryEncoder::loop() {
      if (_writePos != _readPos) {
        State state = _buffer[_readPos];
        _readPos = (_readPos + 1) % BURP_DIMMER_ROTARY_ENCODER_BUFFER_SIZE;
        if (
          (_state == State::A_FALLING && state == State::B_FALLING) ||
          (_state == State::A_RISING && state == State::B_RISING)
        ) {
          _onChange(BURP_DIMMER_ROTARY_ENCODER_RIGHT);
        }
        if (
          (_state == State::B_FALLING && state == State::A_FALLING) ||
          (_state == State::B_RISING && state == State::A_RISING)
        ) {
          _onChange(BURP_DIMMER_ROTARY_ENCODER_LEFT);
        }
        _state = state;
      }
    }

    ICACHE_RAM_ATTR void RotaryEncoder::interrupt() {
      int pinAState = digitalRead(_pinA);
      int pinBState = digitalRead(_pinB);
      State state = State::UNCHANGED;
      if (pinAState != _pinAState) {
        if (pinAState == HIGH) {
          state = State::A_RISING;
        } else {
          state = State::A_FALLING;
        }
        _pinAState = pinAState;
      } else if (pinBState != _pinBState) {
        if (pinBState == HIGH) {
          state = State::B_RISING;
        } else {
          state = State::B_FALLING;
        }
        _pinBState = pinBState;
      }
      if (state != State::UNCHANGED) {
        _buffer[_writePos] = state;
        _writePos = (_writePos + 1) % BURP_DIMMER_ROTARY_ENCODER_BUFFER_SIZE;
      }
    }

  }
}
