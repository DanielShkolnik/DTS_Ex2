
#ifndef DTS_EX2_UNIONFIND_H
#define DTS_EX2_UNIONFIND_H

#include "dataCenterGroup.h"
#include "dataCenter.h"
#include "assert.h"
#include "avl.h"
#include <memory>

class UnionFind{
private:
    DataCenter** DCs_arr;
    int n; // number of DCs

public:
    std::shared_ptr<DataCenterGroup> findDCGroup(int DC_ID);
    DataCenter* findDCRoot(int DC_ID);
    void unionDCs(int DC_ID1, int DC_ID2);
    explicit UnionFind(int n);
    ~UnionFind();
    UnionFind& operator=(const DataCenter& dc) = delete;
    UnionFind(const DataCenter& dc) = delete;
    void removeServer(int DC_ID, int server_ID, int traffic);
    void addServer(int DC_ID, int server_ID, int traffic, const std::shared_ptr<Server>& server);
};

// function object to call for preorder do something.
// adds nodes inorder to array
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

// function object to call for preorder do something.
// coppies nodes inorder to the empty tree from the sorted array
class AddToTree{
private:
    int i;
    std::shared_ptr<Server>* server_array;
public:
    void operator()(const std::shared_ptr<Node<Key,Server>>& node){
        node->setData((this->server_array)[i]);
        node->setSelfTraffic((this->server_array)[i]->getTraffic());
        Key key((this->server_array)[i]->getID(), (this->server_array)[i]->getTraffic());
        node->setKey(key);
        i++;
    }
    explicit AddToTree(std::shared_ptr<Server>* server_array):i(0),server_array(server_array){};
    AddToTree(const AddToTree& a) = delete;
};




#endif //DTS_EX2_UNIONFIND_H



