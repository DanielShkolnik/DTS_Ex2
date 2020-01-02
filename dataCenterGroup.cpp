
#include "dataCenterGroup.h"

int DataCenterGroup::getNumOfDCs(){
    return this->num_of_DCs;
}

int DataCenterGroup::getNumOfServers(){
    return this->num_of_Servers;
}

DataCenter* DataCenterGroup::getRoot(){
    return this->root;
}

void DataCenterGroup::setNumOfDCs(int NumOfDCs){
    this->num_of_DCs=NumOfDCs;
}

void DataCenterGroup::setNumOfServers(int NumOfServers){
    this->num_of_Servers=NumOfServers;
}

Avl<Key,Server>* DataCenterGroup::getTrafficRankTree(){
    return this->traffic_rank_tree;
}

void DataCenterGroup::setTrafficRankTree(Avl<Key,Server>* tree){
    assert(tree!= nullptr);
    delete this->traffic_rank_tree;
    this->traffic_rank_tree=tree;
}