#include "Multiplexer.h"
#include "ShiftRegister.h"


# define CYCLE_TIME_ON 1000  //1.5 millisecond 

Multiplexer::Multiplexer(ShiftRegister& highRegister, ShiftRegister& lowRegister): _highRegister(highRegister), _lowRegister(lowRegister){

}

void Multiplexer::displayBoolArray(bool* highArray, int arrayLen, int action, int num_rows, int num_columns){

    if (arrayLen < (num_rows * num_columns)){
        // make array for lowRegister outputs
        bool* lowArray = (bool*)malloc(num_rows * sizeof(bool));

        if (lowArray != NULL){
            for (int counter = 0; counter < arrayLen; counter+= num_columns){
                _highRegister.setArray_toMemory(&highArray[counter], num_columns);
                
                // Set the correct row pins low
                for(int pos = 0; pos < num_rows; pos++){
                    if (counter / num_columns == pos){ // this is the current row we are on (this row needs to turn on)
                        lowArray[pos] = 0;
                    }
                    else{ // turn all of the other rows off
                        lowArray[pos] = 1;
                    }
                }
                _lowRegister.setArray_toMemory(lowArray, num_rows);

                // Display the memory on the outputs
                _highRegister.pushMemory();
                _lowRegister.pushMemory();
                delay(CYCLE_TIME_ON); // leave the LED's on for a short time
            }
            
            // done with loop free array
            free(lowArray);
            lowArray = nullptr;
        }
    }

}

