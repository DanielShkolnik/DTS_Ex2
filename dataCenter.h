#ifndef DTS_EX2_DATACENTER_H
#define DTS_EX2_DATACENTER_H



class DataCenter{
private:
    int DC_ID;
    DataCenter* next;
    std::shared_ptr<DataCenterGroup>* group;

public:
    int getID();
    DataCenter(int ID);
    ~DataCenter();
    DataCenter& operator=(const DataCenter& dc) = delete;
    DataCenter(const DataCenter& dc) = delete;
};





#endif //DTS_EX2_DATACENTER_H
