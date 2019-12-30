
#ifndef AVL_KEY_H
#define AVL_KEY_H

class Key{
private:
    int searver_ID;
    int traffic;
public:
    Key(int id, int traffic):searver_ID(id),traffic(traffic){};
    ~Key()= default;
    Key(const Key& key)= default;
    Key& operator=(const Key& key)= default;
    bool operator<(const Key& other) const ;
    bool operator>(const Key& other) const ;
    bool operator==(const Key& other) const ;
    bool operator!=(const Key& other) const ;
};

#endif //AVL_KEY_H
