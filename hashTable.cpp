//
// Created by omer on 30/12/2019.
//

#include "hashTable.h"
#include "assert.h"
#define MAGICSIZE 17

void initArr(ChainNode** array, int size){
    for(int i=0; i<size; i++){
        array[i] = nullptr;
    }
}

void HashTable::doubleSize(){
    assert(this->num_of_occupied_cells == this->size);
    this->size = this->size*2;
    ChainNode** newArr = new ChainNode*[this->size];
    initArr(newArr,this->size);
    for(int i=0; i<this->num_of_occupied_cells; i++){
        ChainNode* current = this->arr[i];
        while (current){
            int index = this->hash(current->getData()->getID());
            newArr[index] = current;
            current = current->getNext();
        }
    }
    this->deleteArr();
    this->arr = newArr;
}

void HashTable::deleteArr(){
    for(int i=0; i<this->size; i++){
        this->deleteChain(i);
    }
    delete[] this->arr;
}

void HashTable::deleteChain(int index) {
    ChainNode* current = this->arr[index];
    while (current){
        ChainNode* prev = current;
        current = current->getNext();
        delete prev;
    }
    this->arr[index] = nullptr;
}

void HashTable::halfSize(){
    int prev_size = this->size;
    this->size = this->size/2;
    ChainNode** newArr = new ChainNode*[this->size];
    initArr(newArr,this->size);

    for(int i=0; i<prev_size; i++){
        ChainNode* current = this->arr[i];
        while (current){
            int index = this->hash(current->getData()->getID());
            newArr[index] = current;
            current = current->getNext();
        }
    }
    this->deleteArr();
    this->arr = newArr;
}

void HashTable::addServer(int index, int server_id, int DC_id){
    ChainNode* current = this->arr[index];
    if(!current){
        ChainNode* newNode = new ChainNode(server_id,DC_id);
        this->arr[index] = newNode;
        this->num_of_occupied_cells++;
        return;
    }

    while (current->getNext()){
        if(current->getData()->getID()== server_id){
            throw HashTable::ServerExsist();
        }
        current = current->getNext();
    }
    if(current->getData()->getID()== server_id){
        throw HashTable::ServerExsist();
    }
    ChainNode* newNode = new ChainNode(server_id,DC_id);
    current->setNext(newNode);
    this->num_of_occupied_cells++;
}

HashTable::HashTable(): arr(new ChainNode*[MAGICSIZE]),num_of_occupied_cells(0), size(MAGICSIZE){
    initArr(this->arr,this->size);
}

void HashTable::removeServer(int index,int server_id){
    ChainNode* current = this->arr[index];
    if(current == nullptr) throw HashTable::ServerNotExsist();
    if(current->getData()->getID() == server_id){
        this->arr[index] = current->getNext();
        delete current;
        this->num_of_occupied_cells--;
        return;
    }

    ChainNode* prev = current;
    current = current->getNext();
    while(current){
        if(current->getData()->getID() == server_id){
            prev->setNext(current->getNext());
            delete current;
            this->num_of_occupied_cells--;
            return;
        }
        prev = current;
        current = current->getNext();
    }

    throw HashTable::ServerNotExsist();
}

HashTable::~HashTable(){
    this->deleteArr();
}

int HashTable::hash(int server_id){
    return server_id%this->size;
}

void HashTable::add(int server_id, int DC_id){
    if(this->num_of_occupied_cells == this->size){
        this->doubleSize();
    }
    int index = this->hash(server_id);
    this->addServer(index,server_id,DC_id);
}

void HashTable::remove(int server_id){
    if(this->num_of_occupied_cells == this->size/4 && this->size > MAGICSIZE){
        this->halfSize();
    }
    int index = this->hash(server_id);
    this->removeServer(index,server_id);
}

std::shared_ptr<Server> HashTable::getServer(int server_id){
    int index = this->hash(server_id);
    ChainNode* current = this->arr[index];
    while (current){
        if(current->getData()->getID() == server_id){
            return current->getData();
        }
    }
    throw HashTable::ServerNotExsist();
}

int HashTable::getDCID(int server_id){
    std::shared_ptr<Server> server = this->getServer(server_id);
    return server->getDCID();
}
int HashTable::getTraffic(int server_id){
    std::shared_ptr<Server> server = this->getServer(server_id);
    return server->getTraffic();
}

void HashTable::setTraffic(int server_id, int traffic){
    std::shared_ptr<Server> server = this->getServer(server_id);
    server->setTraffic(traffic);
}