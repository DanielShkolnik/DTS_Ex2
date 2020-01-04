//
// Created by omer on 04/01/2020.
//

#include "library2.h"
#include <assert.h>
#include <iostream>
using std::cout;
int main() {
    void** DS=new (void*);
    *DS=Init(10);

    assert(*DS!= nullptr);
    StatusType s;
    s=AddServer(*DS,1,1);
    assert(s==SUCCESS);
    s=AddServer(*DS,1,2);
    assert(s==SUCCESS);
    s=AddServer(*DS,1,3);
    assert(s==SUCCESS);
    s=AddServer(*DS,2,4);
    assert(s==SUCCESS);
    s=AddServer(*DS,2,5);
    assert(s==SUCCESS);
    s=AddServer(*DS,2,6);
    assert(s==SUCCESS);
    s=AddServer(*DS,3,7);
    assert(s==SUCCESS);
    s=AddServer(*DS,3,8);
    assert(s==SUCCESS);
    s=AddServer(*DS,3,9);
    assert(s==SUCCESS);
    s=AddServer(*DS,3,10);
    assert(s==SUCCESS);

    s=SetTraffic(*DS,1,10);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,2,20);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,3,30);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,4,40);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,5,50);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,6,60);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,7,70);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,10,100);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,8,80);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,9,90);
    assert(s==SUCCESS);

    int sum=0;
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==100);
    s=SumHighestTrafficServers(*DS,0,2,&sum);
    assert(s==SUCCESS && sum==100+90);
    s=SumHighestTrafficServers(*DS,0,3,&sum);
    assert(s==SUCCESS && sum==100+90+80);
    s=SumHighestTrafficServers(*DS,0,4,&sum);
    assert(s==SUCCESS && sum==100+90+80+70);
    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==100+90+80+70+60);
    s=SumHighestTrafficServers(*DS,0,6,&sum);
    assert(s==SUCCESS && sum==100+90+80+70+60+50);
    s=SumHighestTrafficServers(*DS,0,7,&sum);
    assert(s==SUCCESS && sum==100+90+80+70+60+50+40);
    s=SumHighestTrafficServers(*DS,0,8,&sum);
    assert(s==SUCCESS && sum==100+90+80+70+60+50+40+30);
    s=SumHighestTrafficServers(*DS,0,9,&sum);
    assert(s==SUCCESS && sum==100+90+80+70+60+50+40+30+20);
    s=SumHighestTrafficServers(*DS,0,10,&sum);
    assert(s==SUCCESS && sum==100+90+80+70+60+50+40+30+20+10);


    s=SumHighestTrafficServers(*DS,1,10,&sum);
    assert(s==SUCCESS && sum==30+20+10);
    s=SumHighestTrafficServers(*DS,2,10,&sum);
    assert(s==SUCCESS && sum==60+50+40);
    s=SumHighestTrafficServers(*DS,3,10,&sum);
    assert(s==SUCCESS && sum==100+90+80+70);


    s=RemoveServer(*DS,8);
    assert(s==SUCCESS);

    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==100+90+70+60+50);
    s=SumHighestTrafficServers(*DS,0,10,&sum);
    assert(s==SUCCESS && sum==100+90+70+60+50+40+30+20+10);

    s=SumHighestTrafficServers(*DS,3,10,&sum);
    assert(s==SUCCESS && sum==100+90+70);

    s=RemoveServer(*DS,3);
    assert(s==SUCCESS);
    s=RemoveServer(*DS,4);
    assert(s==SUCCESS);

    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==100+90+70+60+50);
    s=SumHighestTrafficServers(*DS,0,10,&sum);
    assert(s==SUCCESS && sum==100+90+70+60+50+20+10);

    s=SumHighestTrafficServers(*DS,2,10,&sum);
    assert(s==SUCCESS && sum==60+50);
    s=SumHighestTrafficServers(*DS,1,10,&sum);
    assert(s==SUCCESS && sum==10+20);

    s=MergeDataCenters(*DS,1,2);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,2,10,&sum);
    assert(s==SUCCESS && sum==60+50+20+10);
    s=SumHighestTrafficServers(*DS,1,2,&sum);
    assert(s==SUCCESS && sum==60+50);
    s=SumHighestTrafficServers(*DS,1,3,&sum);
    assert(s==SUCCESS && sum==60+50+20);
    s=MergeDataCenters(*DS,1,3);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,3,10,&sum);
    assert(s==SUCCESS && sum==100+90+70+60+50+20+10);
    s=SumHighestTrafficServers(*DS,3,4,&sum);
    assert(s==SUCCESS && sum==100+90+70+60);

    s=AddServer(*DS,4,11);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,11,1);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,0,15,&sum);
    assert(s==SUCCESS && sum==100+90+70+60+50+20+10+1);
    s=SetTraffic(*DS,11,110);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,0,15,&sum);
    assert(s==SUCCESS && sum==110+100+90+70+60+50+20+10);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==110);
    s=MergeDataCenters(*DS,2,4);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,1,1,&sum);
    assert(s==SUCCESS && sum==110);

    s=SetTraffic(*DS,11,50);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,1,1,&sum);
    assert(s==SUCCESS && sum==100);
    s=SumHighestTrafficServers(*DS,1,6,&sum);
    assert(s==SUCCESS && sum==100+90+70+60+50+50);
    s=SumHighestTrafficServers(*DS,0,6,&sum);
    assert(s==SUCCESS && sum==100+90+70+60+50+50);

    cout<<"***************************QUIT*********************"<<"\n";
    Quit(DS);
    delete DS;
    cout<<"*******************************************************"<<"\n";
    cout<<"*******************************************************"<<"\n";
    cout<<"YOU HAVE PASSED THE TEST ^___^"<<"\n"<<"GOOD LUCK IN THE FINAL EXAM";
    cout<<"\n"<<"*******************************************************"<<"\n";
    cout<<"*******************************************************"<<"\n";
    return 0;
}