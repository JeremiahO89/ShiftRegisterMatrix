#ifndef BLUETOOTHTYPECONVERTER_H // Include Guard (prevents errors if header is double included)
#define BLUETOOTHTYPECONVERTER_H


#include "Arduino.h" //Needed for the string libary
#include <stdint.h> //Used for unit8_t

uint8_t* decodeBluetoothStr(String dataString, int dataStringLen);
bool* decodeHEX(uint8_t* bluetoothData, int bluetoothDataSize, int* action, int* num_Rows, int* num_columns);
void freeDecodedArray(bool* array);

#endif
