//
// Created by omer on 30/12/2019.
//

#include "dynamicArr.h"

void DynamicArr::doubleSize(){
    size = size*2;
    ChainNode** newArr = new ChainNode*[size];
    for(int i=0; i<num_of_occupide_cells; i++){
        newArr[i] = this->arr[i];
    }

}