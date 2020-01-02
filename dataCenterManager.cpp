

#include "dataCenterManager.h"

StatusType DataCenterManager::MergeDataCenters(int dataCenter1, int dataCenter2){
    if(dataCenter1>this->num_of_DCs || dataCenter1<=0 || dataCenter2>this->num_of_DCs || dataCenter2<=0) return INVALID_INPUT;
    try{
        this->DCGroups.unionDCs(dataCenter1,dataCenter2);
        return SUCCESS;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType DataCenterManager::AddServer(int dataCenterID, int serverID){
    if(dataCenterID>this->num_of_DCs || dataCenterID<=0 || serverID<=0) return INVALID_INPUT;
    try{
        this->servers_hash_table.add(serverID,dataCenterID);
        return SUCCESS;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(HashTable::ServerExsist& e){
        return FAILURE;
    }
    catch(HashTable::ServerNotExsist& e){
        return FAILURE;
    }
}


StatusType DataCenterManager::RemoveServer(int serverID){
    if(serverID<=0) return INVALID_INPUT;
    try{
        this->servers_hash_table.remove(serverID);

        Key key(serverID,);
        this->servers_traffic.delete_element()
        return SUCCESS;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(HashTable::ServerExsist& e){
        return FAILURE;
    }
    catch(HashTable::ServerNotExsist& e){
        return FAILURE;
    }
}

StatusType DataCenterManager::SetTraffic(int serverID, int traffic){

}

StatusType DataCenterManager::SumHighestTrafficServers(int dataCenterID, int k, int* traffic){

}

