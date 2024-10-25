#include <SoftwareSerial.h> // 
#include <BluetoothTypeConverter.h>
#include <ShiftRegister.h> //Shift Register Functinality and setup

//Define the bluetooth chip
const int RX_PIN = 1; 
const int TX_PIN = 2;
SoftwareSerial bluetooth(RX_PIN, TX_PIN); 


const int numRows = 8;
const int numColumns = 8;
// Use 4 different pins which will result in 8 outputs
ShiftRegister HighRegister(3,4,5,6,7,numRows);
ShiftRegister LowRegister(8,9,10,11,12,numColumns);


void setup() {
  bluetooth.begin(9600); // set bluetooth pulling rate


}

void loop() {
  // put your main code here, to run repeatedly:

}
