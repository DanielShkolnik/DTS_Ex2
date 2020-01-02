
#include"library2.h"
#include "dataCenterManager.h"

void* Init(int n){
    DataCenterManager* DS = new DataCenterManager(n);
    return (void*)DS;
}

StatusType MergeDataCenters(void *DS, int dataCenter1, int dataCenter2){
    return ((DataCenterManager *)DS)-> MergeDataCenters(dataCenter1, dataCenter2);
}

StatusType AddServer(void *DS, int dataCenterID, int serverID){
    return ((DataCenterManager *)DS)-> AddServer(dataCenterID, serverID);
}

StatusType RemoveServer(void *DS, int serverID){
    return ((DataCenterManager *)DS)-> RemoveServer(serverID);
}

StatusType SetTraffic(void *DS, int serverID,  int traffic){
    return ((DataCenterManager *)DS)-> SetTraffic(serverID, traffic);
}

StatusType SumHighestTrafficServers(void *DS, int dataCenterID,  int k, int* traffic){
    return ((DataCenterManager *)DS)-> SumHighestTrafficServers(dataCenterID, k, traffic);
}

void Quit(void** DS){
    delete *(DataCenterManager **)DS;
    *DS = nullptr;
}



