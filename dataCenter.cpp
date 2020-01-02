
#include "dataCenter.h"

int DataCenter::getID(){
    return this->DC_ID;
}

DataCenter* DataCenter::getNext(){
    return this->next;
}

void DataCenter::setNext(DataCenter* next){
    this->next = next;
}

std::shared_ptr<DataCenterGroup> DataCenter::getGroup(){
    return this->group;
}

void DataCenter::setGroup(const std::shared_ptr<DataCenterGroup>& group){
    this->group=group;
}

