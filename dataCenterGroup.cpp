
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
