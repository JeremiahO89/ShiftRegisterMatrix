#ifndef SHIFT_REGISTER_H  // Include Guard (prevents errors if header is double included)
#define SHIFT_REGISTER_H

#include "Arduino.h" // Uncomment if using Arduino-specific functionality

class ShiftRegister {
  public:
    ShiftRegister(int state_pin, int latch_pin, int clear_pin, int unused_pin, int num_outputs);
    int pushState();
  private:
    int _state_pin;
    int _latch_pin;
    int _clear_pin;
    int _unused_pin;
    int _num_outputs;
};

#endif
