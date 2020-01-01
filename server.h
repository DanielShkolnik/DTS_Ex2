//
// Created by omer on 30/12/2019.
//

#ifndef DTS_EX2_SERVER_H
#define DTS_EX2_SERVER_H
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
};
#endif //DTS_EX2_SERVER_H
