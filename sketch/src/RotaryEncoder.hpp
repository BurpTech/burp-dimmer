#ifndef RotaryEncoder_hpp
#define RotaryEncoder_hpp

#include "Debug.hpp"

#define ROTARY_ENCODER_LEFT (-1)
#define ROTARY_ENCODER_RIGHT 1

#define _ROTARY_ENCODER_BUFFER_SIZE 8

class RotaryEncoder {
  using f_onChange = std::function<void(int direction)>;

  // can't use <functional> stuff with attachInterrupt
  using f_interruptDispatch = void(*)();

  enum class State {
    UNCHANGED,
    A_RISING,
    A_FALLING,
    B_RISING,
    B_FALLING
  };

  int _pinA;
  int _pinB;
  volatile unsigned int _pinAState;
  volatile unsigned int _pinBState;
  volatile State _buffer[_ROTARY_ENCODER_BUFFER_SIZE];
  volatile unsigned int _writePos;
  unsigned int _readPos;
  State _state;
  f_interruptDispatch _interruptDispatch;
  f_onChange _onChange;

  public:
    RotaryEncoder(int pinA, int pinB, f_interruptDispatch interruptDispatch, f_onChange onChange);
    void setup();
    void loop();
    ICACHE_RAM_ATTR void interrupt();
};

RotaryEncoder::RotaryEncoder(int pinA, int pinB, f_interruptDispatch interruptDispatch, f_onChange onChange) {
  _pinA = pinA;
  _pinB = pinB;
  _interruptDispatch = interruptDispatch;
  _onChange = onChange;
}

void RotaryEncoder::setup() {
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
    _readPos = (_readPos + 1) % _ROTARY_ENCODER_BUFFER_SIZE;
    if (
      (_state == State::A_FALLING && state == State::B_FALLING) ||
      (_state == State::A_RISING && state == State::B_RISING)
    ) {
      _onChange(ROTARY_ENCODER_RIGHT);
    }
    if (
      (_state == State::B_FALLING && state == State::A_FALLING) ||
      (_state == State::B_RISING && state == State::A_RISING)
    ) {
      _onChange(ROTARY_ENCODER_LEFT);
    }
    _state = state;
  }
}

void RotaryEncoder::interrupt() {
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
    _writePos = (_writePos + 1) % _ROTARY_ENCODER_BUFFER_SIZE;
  }
}

#endif
