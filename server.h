//
// Created by omer on 30/12/2019.
//

#ifndef DTS_EX2_SERVER_H
#define DTS_EX2_SERVER_H
#include <iostream>

class Server{
private:
    int server_id;
    int traffic;
    int DC_id;
public:
    Server(int server_id, int DC_id):server_id(server_id), traffic(0), DC_id(DC_id){};
    void setTraffic(int traffic);
    int getTraffic();
    int getID();
    int getDCID();
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    ~Server(){
        //std::cout << "~Server()" << server_id << std::endl;
    }
};
#endif //DTS_EX2_SERVER_H
