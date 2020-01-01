
#include "unionFind.h"


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




void mergeTrees(Avl<Key,Server>* tree1, Avl<Key,Server>* tree2){

}

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
    std::shared_ptr<DataCenterGroup> group1 = findDCGroup(DC_ID1);
    std::shared_ptr<DataCenterGroup> group2 = findDCGroup(DC_ID2);
    if(group1->getNumOfDCs()>=group2->getNumOfDCs()){
        group2->getRoot()->setNext(group1->getRoot());
        mergeTrees(group1->getTrafficRankTree(), group2->getTrafficRankTree());
        group1->setNumOfDCs(group1->getNumOfDCs()+group2->getNumOfDCs());
        group1->setNumOfServers(group1->getNumOfServers()+group2->getNumOfServers());
    }
    else {
        group1->getRoot()->setNext(group2->getRoot());
        mergeTrees(group2->getTrafficRankTree(), group1->getTrafficRankTree());
        group2->setNumOfDCs(group2->getNumOfDCs()+group1->getNumOfDCs());
        group2->setNumOfServers(group2->getNumOfServers()+group1->getNumOfServers());
    }
}




