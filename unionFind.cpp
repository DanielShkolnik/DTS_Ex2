
#include "unionFind.h"
#include "assert.h"

/*
std::shared_ptr<DataCenterGroup> UnionFind::getDataCenterGroup(int index){
    assert(index<=0);
    return this->groups_arr[index];
}

std::shared_ptr<DataCenterGroup> UnionFind::getDataCenter(int index){
    assert(index<=0);
    return this->DCs_arr[index];
}
*/

std::shared_ptr<DataCenterGroup> UnionFind::findDCGroup(int DC_ID){
    assert(DC_ID<=0 || DC_ID>n);
    DataCenter* current_DC = this->DCs_arr[DC_ID];
    while (current_DC->getNext()!= nullptr){
        current_DC = current_DC->getNext();
    }
    DataCenter* root=current_DC;
    current_DC = this->DCs_arr[DC_ID];
    DataCenter* prev_DC = current_DC;
    while (current_DC->getNext()!= nullptr){
        current_DC = current_DC->getNext();
        prev_DC->setNext(root);
        prev_DC = current_DC;
    }
    return current_DC->getGroup();
}


void UnionFind::unionDCs(int DC_ID1, int DC_ID2){
    assert(DC_ID1<=0 || DC_ID1>n);
    assert(DC_ID2<=0 || DC_ID2>n);
    
}