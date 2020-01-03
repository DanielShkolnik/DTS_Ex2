//
// Created by danie on 06/12/2019.
//

#include "key.h"

bool Key::operator<(const Key& other) const {
    if(this->traffic>other.traffic) return true;
    else if(this->traffic==other.traffic){
        return this->server_ID<other.server_ID;
    }
    return false;
}
bool Key::operator>(const Key& other) const {
    return !(this->operator<(other) || this->operator==(other));
}
bool Key::operator==(const Key& other) const{
    return (this->server_ID==other.server_ID && this->traffic==other.traffic);
}

bool Key::operator!=(const Key& other) const{
    return !(this->operator==(other));
}