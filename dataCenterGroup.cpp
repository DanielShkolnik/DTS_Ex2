
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