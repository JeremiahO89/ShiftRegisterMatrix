#ifndef MULTIPLEXER_H // Include Guard (prevents errors if header is double included)
#define MULTIPLEXER_H

#include <Arduino.h> // Needed for the string libary
#include <stdint.h> // Used for unit8_t
#include "ShiftRegister.h"

class Multiplexer {
    public:
        Multiplexer(ShiftRegister& highRegister, ShiftRegister& lowRegister);
        void displayBoolArray(bool* highArray, int arrayLen, int action, int num_rows, int num_columns);

    private:
        ShiftRegister& _highRegister;
        ShiftRegister& _lowRegister;


};

#endif
