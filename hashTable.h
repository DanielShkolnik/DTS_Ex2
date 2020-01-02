//
// Created by omer on 30/12/2019.
//

#ifndef DTS_EX2_HashTable_H
#define DTS_EX2_HashTable_H

#include "chainNode.h"

class HashTable{
private:
    ChainNode** arr;
    int num_of_occupied_cells;
    int size;
    void doubleSize();
    void halfSize();
    void deleteChain(int index);
    void deleteArr();
    void addServer(int index, int server_id, int DC_id);
    void removeServer(int index,int server_id);
    int hash(int server_id);
public:
    class ServerExsist{};
    class ServerNotExsist{};
    explicit HashTable(int size_p);
    ~HashTable();
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    void add(int server_id, int DC_id);
    void remove(int server_id);
};
#endif //DTS_EX2_HashTable_H
