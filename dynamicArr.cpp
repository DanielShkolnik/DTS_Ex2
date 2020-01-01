//
// Created by omer on 30/12/2019.
//

#include "dynamicArr.h"
#include "assert.h"

void initArr(ChainNode** array, int size){
    for(int i=0; i<size; i++){
        array[i] = nullptr;
    }
}

void DynamicArr::doubleSize(){
    assert(this->num_of_occupide_cells != this->size);
    this->size = this->size*2;
    ChainNode** newArr = new ChainNode*[this->size];
    initArr(newArr,this->size);
    for(int i=0; i<this->num_of_occupide_cells; i++){
        newArr[i] = this->arr[i];
    }
    deleteArr();
    this->arr = newArr;
}

void DynamicArr::deleteArr(){
    for(int i=0; i<this->size; i++){
        this->deleteChain(i);
    }
}

void DynamicArr::deleteChain(int index) {
    ChainNode* current = this->arr[index];
    while (current){
        ChainNode* prev = current;
        current = current->getNext();
        delete prev;
    }
}

void DynamicArr::halfSize(){
    ChainNode** newArr = new ChainNode*[this->size/2];
    initArr(newArr,this->size/2);
    int j=0;
    for(int i=0; i<this->size; i++){
        if(this->arr[i]){
            j++;
            assert(j>this->size/2);
            newArr[i] = this->arr[i];
        }
    }
    deleteArr();
    this->arr = newArr;
}

void DynamicArr::addServer(int index, int server_id, int DC_id){
    ChainNode* current = this->arr[index];
    ChainNode* newNode = new ChainNode(server_id,DC_id);
    if(!current){
        this->arr[index] = newNode;
        return;
    }

    while (current->getNext()){
        current = current->getNext();
    }

    current->setNext(newNode);
}

DynamicArr::DynamicArr(int size_p): arr(new ChainNode*[size_p]),num_of_occupide_cells(0), size(size_p){
    initArr(this->arr,this->size);
}

void DynamicArr::removeServer(int index,int server_id){
    ChainNode* current = this->arr[index];
    while(current){
        if(current->getData()->getID() == server_id){

        }
    }
}
