
#ifndef DTS_EX2_UNIONFIND_H
#define DTS_EX2_UNIONFIND_H

#include "dataCenterGroup.h"
#include "dataCenter.h"

class UnionFind{
private:
    std::shared_ptr<DataCenterGroup>* groups_arr;
    std::shared_ptr<DataCenter>* DCs_arr;

public:
    DataCenterGroup* getDataCenterGroup(int index);
    DataCenter* getDataCenter(int index);
    UnionFind() = default;
    ~UnionFind() = default;
    UnionFind& operator=(const DataCenter& dc) = delete;
    UnionFind(const DataCenter& dc) = delete;


};


#endif //DTS_EX2_UNIONFIND_H
