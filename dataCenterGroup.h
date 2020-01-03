
#ifndef DTS_EX2_DATACENTERGROUP_H
#define DTS_EX2_DATACENTERGROUP_H

#include "server.h"
#include "key.h"
#include "avl.h"
#include "assert.h"
#include "memory"

class DataCenterGroup{
private:
    Avl<Key,Server>* traffic_rank_tree;
    int num_of_DCs;
    int num_of_Servers;

public:
    int getNumOfDCs();
    int getNumOfServers();
    void setNumOfDCs(int NumOfDCs);
    void setNumOfServers(int NumOfServers);
    Avl<Key,Server>* getTrafficRankTree();
    void setTrafficRankTree(Avl<Key,Server>* tree);

    explicit DataCenterGroup(): traffic_rank_tree(nullptr), num_of_DCs(0),num_of_Servers(0){};
    ~DataCenterGroup() = default;
    DataCenterGroup& operator=(const DataCenterGroup& dc) = delete;
    DataCenterGroup(const DataCenterGroup& dc) = delete;
    void removeServer(int server_ID, int traffic);
    void addServer(int serverID, int traffic, const std::shared_ptr<Server>& server);
};


#endif //DTS_EX2_DATACENTERGROUP_H
