#ifndef SHIFT_REGISTER_H  // Include Guard (prevents errors if header is double included)
#define SHIFT_REGISTER_H

#include "Arduino.h" // Uncomment if using Arduino-specific functionality

class ShiftRegister {
  public:
    ShiftRegister(int state_pin, int push_pin, int output_pin, int clear_pin, int enable_pin, int num_outputs);
    void highState();
    void lowState();
    void pushState();
    void pushMemory();
    void disableOutputs();

  private:
    int _state_pin;
    int _push_pin;
    int _output_pin;
    int _enable_pin;
    int _num_outputs;
};

#endif
