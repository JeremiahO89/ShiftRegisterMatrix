#ifndef BLUETOOTHTYPECONVERTER_H // Include Guard (prevents errors if header is double included)
#define BLUETOOTHTYPECONVERTER_H


#include <Arduino.h> //Needed for the string libary
#include <stdint.h> //Used for unit8_t
// #include <cstdlib> // for malloc and free

uint8_t* decodeBluetoothStr(String dataString, int dataStringLen);
bool* hexToBool(uint8_t* bluetoothData, int bluetoothDataSize, int* action, int* num_Rows, int* num_columns);

void freeBoolArray(bool* array);
void freeUnit8Array(uint8_t* array);

#endif
