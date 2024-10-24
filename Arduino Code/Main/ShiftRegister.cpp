#include "Arduino.h"
#include "ShiftRegister.h"

# define DEBOUNCE 1   //1 millisecond 

// :: is the scope resolution operator 
ShiftRegister::ShiftRegister(int state_pin, int push_pin, int output_pin, int clear_pin, int enable_pin, int num_outputs) {
  pinMode(state_pin, OUTPUT);
  pinMode(push_pin, OUTPUT);
  pinMode(output_pin, OUTPUT);
  pinMode(clear_pin, OUTPUT);
  pinMode(enable_pin, OUTPUT);


  _state_pin = state_pin;
  _push_pin = push_pin;
  _output_pin = output_pin;
  _clear_pin = clear_pin;
  _enable_pin  = enable_pin ;
  _num_outputs = num_outputs; // this will change based on if its the colum or row register
}

//Set the state
void ShiftRegister::highState() {
  digitalWrite(_state_pin, HIGH);
  delay(DEBOUNCE);
  }
void ShiftRegister::lowState() {
  digitalWrite(_state_pin, LOW);
  delay(DEBOUNCE);
}
//Push the state into memory
void ShiftRegister::pushState() {
  digitalWrite(_push_pin, HIGH);
  delay(DEBOUNCE);
  digitalWrite(_push_pin, LOW);
  delay(DEBOUNCE);
}
//Push the memory to outputs
void ShiftRegister::pushMemory() {
  digitalWrite(_push_pin, HIGH);
  delay(DEBOUNCE);
  digitalWrite(_push_pin, LOW);
  delay(DEBOUNCE);
}
// Disable Outputs; Sets all output pins to LOW (0)
void ShiftRegister::disableOutputs(){
  digitalWrite(_enable_pin, HIGH);
  delay(DEBOUNCE);
}
//Enable Outputs; Sets all output pins to HIGH (1)
void ShiftRegister::enableOutputs(){
  digitalWrite(_enable_pin, LOW);
  delay(DEBOUNCE);
}
//Clear Memory; Sets all of the memory bits to LOW (0)
void ShiftRegister::clearMemory() {
  digitalWrite(_clear_pin, LOW);
  delay(DEBOUNCE);
  digitalWrite(_clear_pin, HIGH);
  delay(DEBOUNCE);
