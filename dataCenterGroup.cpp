
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

void DataCenterGroup::removeServer(int server_ID, int traffic){
    Key key(server_ID,traffic);
    this->traffic_rank_tree->delete_element(key);
}

void DataCenterGroup::addServer(int serverID, int traffic, const std::shared_ptr<Server>& server){
    Key key(serverID,traffic);
    this->traffic_rank_tree->insert(key,server);
}