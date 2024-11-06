#include "ShiftRegister.h" //Shift Register Functinality and setup
//#include <Arduino.h>



// These are FIXED for now
const int numRows = 8;
const int numColumns = 8;
// Use 4 different pins which will result in 8 outputs
ShiftRegister highRegister = ShiftRegister(12,9,10,4,11,numRows);
ShiftRegister lowRegister = ShiftRegister(8,5,6,3,7,numColumns);


void setup() {
  lowRegister.enableOutputs();
  lowRegister.clearMemory();
  lowRegister.pushMemory();

  highRegister.enableOutputs();
  highRegister.clearMemory();
  highRegister.pushMemory();

  highRegister.highState();
  highRegister.highState();
  highRegister.highState();
  highRegister.highState();
  highRegister.highState();
  highRegister.highState();
  highRegister.highState();
  highRegister.highState();
  
  highRegister.pushState();
  highRegister.pushMemory();
}



void loop() {

}