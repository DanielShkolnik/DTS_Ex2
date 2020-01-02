

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
        int server_traffic = this->servers_hash_table.getTraffic(serverID);
        int server_DC_ID = this->servers_hash_table.getDCID(serverID);
        Key key(serverID,server_traffic);
        this->servers_traffic.delete_element(key);
        this->DCGroups.removeServer(server_DC_ID, serverID, server_traffic);
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
        this->servers_traffic.insert(new_key,this->servers_hash_table.getServer(serverID));
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

int sumTraffic(std::shared_ptr<Node<Key,Server>> root, int k, int sum_traffic){
    // then your k from right(max)
    if(root->getRight()->getNodeCount() == k-1){
        return root->getLeft()->getTraffic() + root->getSelfTraffic();
    }
    // search right
    if(root->getRight()->getNodeCount() > k-1){
        return sumTraffic(root->getRight(),k, sum_traffic);
    }
    // search left  and increase sum_traffic of bigger servers by traffic.
    if(root->getRight()->getNodeCount() < k-1){
        sum_traffic += root->getRight()->getTraffic();
        return sumTraffic(root->getLeft(),k  - root->getRight()->getNodeCount() -1, sum_traffic);
    }

}

StatusType DataCenterManager::SumHighestTrafficServers(int dataCenterID, int k, int* traffic){
    std::shared_ptr<DataCenterGroup> DC_group = this->DCGroups.findDCGroup(dataCenterID);
    std::shared_ptr<Node<Key,Server>> root = DC_group->getTrafficRankTree()->getHead();

}

