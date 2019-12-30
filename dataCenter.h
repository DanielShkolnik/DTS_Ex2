#ifndef DTS_EX2_DATACENTER_H
#define DTS_EX2_DATACENTER_H

#include "dataCenterGroup.h"

class DataCenter{
private:
    int DC_ID;
    DataCenter* next;
    std::shared_ptr<DataCenterGroup> group;

public:
    int getID();
    DataCenter* getNext();
    void setNext(DataCenter* next);
    std::shared_ptr<DataCenterGroup> getGroup();
    explicit DataCenter(int ID):DC_ID(ID),next(nullptr),group(nullptr){};
    ~DataCenter() = default;
    DataCenter& operator=(const DataCenter& dc) = delete;
    DataCenter(const DataCenter& dc) = delete;
};





#endif //DTS_EX2_DATACENTER_H
