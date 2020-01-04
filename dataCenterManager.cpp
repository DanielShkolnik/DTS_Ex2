

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
        this->num_of_servers++;
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
        int server_traffic = this->servers_hash_table.getTraffic(serverID);
        int server_DC_ID = this->servers_hash_table.getDCID(serverID);
        Key key(serverID,server_traffic);
        try{
            this->servers_traffic.delete_element(key);
            this->DCGroups.removeServer(server_DC_ID, serverID, server_traffic);
        }
        catch(Avl<Key,Server>::KeyNotFound& e){

        }
        this->servers_hash_table.remove(serverID);
        this->num_of_servers--;
        return SUCCESS;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(HashTable::ServerNotExsist& e){
        return FAILURE;
    }
}

StatusType DataCenterManager::SetTraffic(int serverID, int traffic){
    if(serverID<=0 || traffic<0) return INVALID_INPUT;
    try{
        int server_traffic_old = this->servers_hash_table.getTraffic(serverID);
        int server_DC_ID = this->servers_hash_table.getDCID(serverID);
        Key key(serverID,server_traffic_old);

        try{
            this->servers_traffic.delete_element(key);
            this->DCGroups.removeServer(server_DC_ID, serverID, server_traffic_old);
        }
        catch(Avl<Key,Server>::KeyNotFound& e){

        }
        this->servers_hash_table.setTraffic(serverID,traffic);
        Key new_key(serverID,traffic);
        this->servers_traffic.insert(new_key,this->servers_hash_table.getServer(serverID),traffic);
        this->DCGroups.addServer(server_DC_ID,serverID,traffic,this->servers_hash_table.getServer(serverID));
        return SUCCESS;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(HashTable::ServerNotExsist& e){
        return FAILURE;
    }
}

int sumTraffic(const std::shared_ptr<Node<Key,Server>>& root, int k, int sum_traffic){
    int right_count;
    if(root->getRight() == nullptr){
        right_count = 0;
    }
    else{
        right_count = root->getRight()->getNodeCount();
    }
    // then your k from right(max)
    if(right_count == k-1){
        if(root->getRight() != nullptr) return root->getRight()->getTraffic() + root->getSelfTraffic() + sum_traffic;
        else return root->getSelfTraffic() + sum_traffic;
    }
    // search right
    if(right_count > k-1){
        return sumTraffic(root->getRight(),k, sum_traffic);
    }
    // search left  and increase sum_traffic of bigger servers by traffic.
    //  if(right_count < k-1 && root->getLeft() != nullptr)
    else{
        if(root->getRight() != nullptr) sum_traffic += root->getRight()->getTraffic() + root->getSelfTraffic();
        else sum_traffic += root->getSelfTraffic();
        if(root->getLeft() == nullptr) return sum_traffic;
        else return sumTraffic(root->getLeft(),k  - right_count -1, sum_traffic);
    }
}

StatusType DataCenterManager::SumHighestTrafficServers(int dataCenterID, int k, int* traffic){
    if(k < 0 || dataCenterID > this->num_of_DCs || dataCenterID < 0 || traffic == nullptr) return INVALID_INPUT;
    try{
        if(dataCenterID !=0){
            std::shared_ptr<DataCenterGroup> DC_group = this->DCGroups.findDCGroup(dataCenterID);
            std::shared_ptr<Node<Key,Server>> root = DC_group->getTrafficRankTree()->getHead();
            *traffic = sumTraffic(root,k,0);
        }
        else{
           *traffic = sumTraffic(this->servers_traffic.getHead(),k,0);
        }
        return SUCCESS;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

