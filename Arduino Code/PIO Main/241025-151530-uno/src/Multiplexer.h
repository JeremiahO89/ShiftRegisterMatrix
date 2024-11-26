#ifndef MULTIPLEXER_H // Include Guard (prevents errors if header is double included)
#define MULTIPLEXER_H

#include <Arduino.h> // Needed for the string libary
#include <stdint.h> // Used for unit8_t
#include "ShiftRegister.h"

class Multiplexer {
    public:
    
        Multiplexer(ShiftRegister& highRegister, ShiftRegister& lowRegister);
        void sendData(bool* highArray, int arrayLen, int num_rows, int action);
private:
        ShiftRegister& _highRegister;
        ShiftRegister& _lowRegister;
        int _displaySize;
        bool* _displayArray;
        int _startColumn;
        void checkColumnState(int arrayLen, int num_rows);
        void displayBoolArray(bool* array, int arrayLen, int num_rows);
};

#endif
