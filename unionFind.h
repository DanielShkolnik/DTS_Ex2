
#ifndef DTS_EX2_UNIONFIND_H
#define DTS_EX2_UNIONFIND_H

#include "dataCenterGroup.h"
#include "dataCenter.h"

class UnionFind{
private:
    std::shared_ptr<DataCenterGroup>* groups_arr;
    DataCenter** DCs_arr;
    int n;

public:
    //std::shared_ptr<DataCenterGroup> getDataCenterGroup(int index);
    //std::shared_ptr<DataCenter> getDataCenter(int DC_ID);


    std::shared_ptr<DataCenterGroup> findDCGroup(int DC_ID);
    void unionDCs(int DC_ID1, int DC_ID2);
    explicit UnionFind(int n):groups_arr(new std::shared_ptr<DataCenterGroup>[n]), DCs_arr(new std::shared_ptr<DataCenter>[n]), n(n){};
    ~UnionFind() = default;
    UnionFind& operator=(const DataCenter& dc) = delete;
    UnionFind(const DataCenter& dc) = delete;

};


#endif //DTS_EX2_UNIONFIND_H
