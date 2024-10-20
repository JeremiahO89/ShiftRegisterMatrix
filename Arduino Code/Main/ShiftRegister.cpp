#include "Arduino.h"
#include "ShiftRegister.h"

# define DEBOUNCE 1 // 1 millisecond 

// :: is the scope resolution operator 
ShiftRegister::ShiftRegister(int state_pin, int latch_pin, int clear_pin, int unused_pin , int num_outputs) {
  pinMode(state_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(clear_pin, OUTPUT);
  pinMode(unused_pin, OUTPUT);


  _state_pin = state_pin;
  _latch_pin = latch_pin;
  _clear_pin = clear_pin;
  _unused_pin  = unused_pin ;
  _num_outputs = num_outputs;
}

int ShiftRegister::pushState() {
  digitalWrite(_latch_pin, HIGH);
  delay(DEBOUNCE);
  digitalWrite(_latch_pin, LOW);
  delay(DEBOUNCE);

}