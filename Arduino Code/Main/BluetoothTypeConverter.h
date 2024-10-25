#ifndef BLUETOOTHTYPECONVERTER_H // Include Guard (prevents errors if header is double included)
#define BLUETOOTHTYPECONVERTER_H

#include <stdint.h>
bool* decodeBluetooth(uint8_t* bluetoothData, int bluetoothDataSize, int* action, int* num_Rows, int* num_columns);
void freeDecodedArray(bool* array);

#endif
