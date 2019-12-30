//
// Created by omer on 30/12/2019.
//

#include <assert.h>
#include "chainNode.h"

ChainNode::ChainNode(int server_id, int DC_id):server(new Server(server_id,DC_id)),next(nullptr){}

void ChainNode::setNext(ChainNode* next){
    assert(this->next!= nullptr);
    this->next = next;
}

ChainNode::~ChainNode() {
    delete this->server;
}