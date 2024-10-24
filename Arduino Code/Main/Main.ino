#include <ShiftRegister.h>


const int numRows = 8;
const int numColumns = 8;
// Use 4 different pins which will result in 8 outputs
ShiftRegister HighRegister(3,4,5,6,7,numRows);
ShiftRegister LowRegister(8,9,10,11,12,numColumns);


void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

}
