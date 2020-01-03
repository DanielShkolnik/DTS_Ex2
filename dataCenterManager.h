
#ifndef DTS_EX2_DATACENTERMANAGER_H
#define DTS_EX2_DATACENTERMANAGER_H

#include "avl.h"
#include "unionFind.h"
#include "hashTable.h"
#include "dataCenterGroup.h"
#include "dataCenter.h"
#include "library2.h"

class DataCenterManager{
private:
    UnionFind DCGroups;
    HashTable servers_hash_table;
    Avl<Key,Server> servers_traffic;
    int num_of_DCs;
    int num_of_servers;

public:
    explicit DataCenterManager(int num_of_DCs):DCGroups(num_of_DCs),servers_hash_table(),servers_traffic(),num_of_DCs(num_of_DCs), num_of_servers(0){};
    ~DataCenterManager() = default;
    DataCenterManager& operator=(const DataCenterManager& dc) = delete;
    DataCenterManager(const DataCenterManager& dc) = delete;

    StatusType MergeDataCenters(int dataCenter1, int dataCenter2);
    StatusType AddServer(int dataCenterID, int serverID);
    StatusType RemoveServer(int serverID);
    StatusType SetTraffic(int serverID, int traffic);
    StatusType SumHighestTrafficServers(int dataCenterID, int k, int* traffic);
};



#endif //DTS_EX2_DATACENTERMANAGER_H
