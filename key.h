
#ifndef AVL_KEY_H
#define AVL_KEY_H

class Key{
private:
    int server_ID;
    int traffic;
public:
    Key():server_ID(0),traffic(0){};
    Key(int id, int traffic):server_ID(id),traffic(traffic){};
    ~Key()= default;
    Key(const Key& key)= default;
    Key& operator=(const Key& key)= default;
    bool operator<(const Key& other) const ;
    bool operator>(const Key& other) const ;
    bool operator==(const Key& other) const ;
    bool operator!=(const Key& other) const ;
};

#endif //AVL_KEY_H
