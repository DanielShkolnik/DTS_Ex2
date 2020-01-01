//
// Created by omer on 30/12/2019.
//

#ifndef DTS_EX2_DYNAMICARR_H
#define DTS_EX2_DYNAMICARR_H

#include "chainNode.h"

class DynamicArr{
private:
    ChainNode** arr;
    int num_of_occupide_cells;
    int size;
    void doubleSize();
    void halfSize();
    void deleteChain(int index);
    void deleteArr();
public:
    class ServerExsist{};
    class ServerNotExsist{};
    explicit DynamicArr(int size_p);
    void addServer(int index, int server_id, int DC_id);
    void removeServer(int index,int server_id); // TO DO
    ~DynamicArr();
    DynamicArr(const DynamicArr&) = delete;
    DynamicArr& operator=(const DynamicArr&) = delete;

};
#endif //DTS_EX2_DYNAMICARR_H
