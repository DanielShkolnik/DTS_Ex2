//
// Created by omer on 30/12/2019.
//

#include "server.h"

void Server::setTraffic(int traffic){
    this->traffic = traffic;
}

 int Server::getTraffic() {
     return this->traffic;
}

int Server::getID(){
    return this->server_id;
}

int Server::getDCID(){
    return this->DC_id;
}