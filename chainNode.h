//
// Created by omer on 30/12/2019.
//

#ifndef DTS_EX2_CHAINNODE_H
#define DTS_EX2_CHAINNODE_H

#include "server.h"

class ChainNode{
private:
    Server* server;
    ChainNode* next;
public:
    ChainNode();
    ChainNode(int server_id, int DC_id);
    void setNext(ChainNode* next);
    ChainNode* getNext();
    Server* getData();
    ChainNode(const ChainNode&) = delete;
    ChainNode& operator=(const ChainNode&) = delete;
    ~ChainNode();

};
#endif //DTS_EX2_CHAINNODE_H
