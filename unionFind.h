
#ifndef DTS_EX2_UNIONFIND_H
#define DTS_EX2_UNIONFIND_H

#include "dataCenterGroup.h"
#include "dataCenter.h"
#include "assert.h"
#include "avl.h"
#include <memory>

class UnionFind{
private:
    std::shared_ptr<DataCenterGroup>* groups_arr;
    DataCenter** DCs_arr;
    int n;

public:
    std::shared_ptr<DataCenterGroup> findDCGroup(int DC_ID);
    void unionDCs(int DC_ID1, int DC_ID2);
    explicit UnionFind(int n):groups_arr(new std::shared_ptr<DataCenterGroup>[n]), DCs_arr(new DataCenter*[n]), n(n){};
    ~UnionFind();
    UnionFind& operator=(const DataCenter& dc) = delete;
    UnionFind(const DataCenter& dc) = delete;
    void removeServer(int DC_ID, int server_ID, int traffic);
    void addServer(int DC_ID, int server_ID, int traffic, const std::shared_ptr<Server>& server);
};


class AddToArray{
private:
    int i;
    std::shared_ptr<Server>* server_array;
public:
    void operator()(const std::shared_ptr<Node<Key,Server>>& node){
        (this->server_array)[i] = node->getData();
        i++;
    }
    explicit AddToArray(std::shared_ptr<Server>* server_array):i(0),server_array(server_array){};
    AddToArray(const AddToArray& a) = delete;
};

class AddToTree{
private:
    int i;
    std::shared_ptr<Server>* server_array;
public:
    void operator()(const std::shared_ptr<Node<Key,Server>>& node){
        node->setData((this->server_array)[i]);
        i++;
    }
    explicit AddToTree(std::shared_ptr<Server>* server_array):i(0),server_array(server_array){};
    AddToTree(const AddToTree& a) = delete;
};




#endif //DTS_EX2_UNIONFIND_H



