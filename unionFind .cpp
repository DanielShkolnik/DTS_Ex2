
#include "unionFind .h"
#include "assert.h"

std::shared_ptr<DataCenterGroup> UnionFind::getDataCenterGroup(int index){
    assert(index<=0);
    return this->groups_arr[index];
}

std::shared_ptr<DataCenterGroup> UnionFind::getDataCenter(int index){
    assert(index<=0);
    return this->DCs_arr[index];
}
