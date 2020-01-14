
#include "unionFind.h"


//merge 2 Server arrays for function unionGroups
void mergeArr(std::shared_ptr<Server>* server_array1, std::shared_ptr<Server>* server_array2,
        std::shared_ptr<Server>* server_array_combined, int combined_arr_size, int arr1_size, int arr2_size){
    int server_array1_index=0;
    int server_array2_index=0;
    int server_array_combined_index=0;
    while(server_array1_index<arr1_size && server_array2_index<arr2_size){
        Key key1(server_array1[server_array1_index]->getID(),server_array1[server_array1_index]->getTraffic());
        Key key2(server_array2[server_array2_index]->getID(),server_array2[server_array2_index]->getTraffic());
        //first insert the lower key
        if(key1 < key2){
            server_array_combined[server_array_combined_index]=server_array1[server_array1_index];
            server_array1_index++;
            server_array_combined_index++;
        }
        else{
            server_array_combined[server_array_combined_index]=server_array2[server_array2_index];
            server_array2_index++;
            server_array_combined_index++;
        }
    }
    //insert array1 cells if array2 allready finished
    while(server_array1_index<arr1_size){
        server_array_combined[server_array_combined_index]=server_array1[server_array1_index];
        server_array1_index++;
        server_array_combined_index++;
    }
    //insert array2 cells if array1 allready finished
    while(server_array2_index<arr2_size){
        server_array_combined[server_array_combined_index]=server_array2[server_array2_index];
        server_array2_index++;
        server_array_combined_index++;
    }
}

//set the ranks of the rank tree
void setRanks(const std::shared_ptr<Node<Key,Server>>& node){
    node->calcHeight();
    node->calcRank();
}

//merge two rank avl trees
void mergeTrees(std::shared_ptr<DataCenterGroup> group1, std::shared_ptr<DataCenterGroup> group2){
    assert(group1 != nullptr && group2 != nullptr);
    //copy first avl rank tree nodes to array
    std::shared_ptr<Server>* server_array1 = new std::shared_ptr<Server>[group1->getNumOfServers()];
    AddToArray pred1(server_array1);
    inorder<Key, Server, AddToArray>(group1->getTrafficRankTree()->getHead(), pred1);

    //copy first avl rank tree nodes to array
    std::shared_ptr<Server>* server_array2 = new std::shared_ptr<Server>[group2->getNumOfServers()];
    AddToArray pred2(server_array2);
    inorder<Key,Server,AddToArray>(group2->getTrafficRankTree()->getHead(),pred2);

    //create new array and merge array1 and array2
    int arr_size=group1->getNumOfServers()+group2->getNumOfServers();
    std::shared_ptr<Server>* server_array_combined = new std::shared_ptr<Server>[arr_size];
    mergeArr(server_array1,server_array2,server_array_combined,arr_size,group1->getNumOfServers(),group2->getNumOfServers());

    //create empty almost complete tree
    Avl<Key,Server>* new_tree = new Avl<Key,Server>(arr_size);
    //copy cells from new array to the empty almost complete tree
    AddToTree pred3(server_array_combined);
    inorder<Key, Server, AddToTree>(new_tree->getHead(), pred3);
    //set the ranks in the new tree
    postorder(new_tree->getHead(),setRanks);

    group1->setTrafficRankTree(new_tree);
    delete[] server_array1;
    delete[] server_array2;
    delete[] server_array_combined;
}

//find the DC_Group of DC_ID
std::shared_ptr<DataCenterGroup> UnionFind::findDCGroup(int DC_ID){
    return findDCRoot(DC_ID)->getGroup();
}

//union two DataCenterGroups
void unionGroups(DataCenter* root_big, DataCenter* root_small){
    std::shared_ptr<DataCenterGroup> group_big = root_big->getGroup();
    std::shared_ptr<DataCenterGroup> group_small = root_small->getGroup();
    root_small->setGroup(nullptr); // there is no pointer to DataCenterGroup so the group is deleted
    root_small->setNext(root_big);
    if(group_big->getNumOfServers()>0 || group_small->getNumOfServers()>0) mergeTrees(group_big, group_small);
    group_big->setNumOfDCs(group_big->getNumOfDCs()+group_small->getNumOfDCs());
    group_big->setNumOfServers(group_big->getNumOfServers()+group_small->getNumOfServers());
}


//union two Data Centers
void UnionFind::unionDCs(int DC_ID1, int DC_ID2){
    assert(DC_ID1>0 && DC_ID1<=n);
    assert(DC_ID2>0 && DC_ID2<=n);
    DataCenter* root1 = findDCRoot(DC_ID1);
    DataCenter* root2 = findDCRoot(DC_ID2);
    if(root1->getGroup()->getNumOfDCs()>=root2->getGroup()->getNumOfDCs()){
        unionGroups(root1,root2);
    }
    else unionGroups(root2,root1);
}

//find the DataCenter_root of DC_ID
DataCenter* UnionFind::findDCRoot(int DC_ID){
    assert(DC_ID>0 && DC_ID<=n);
    DataCenter* current_DC = this->DCs_arr[DC_ID];
    while (current_DC->getNext()!= nullptr){
        current_DC = current_DC->getNext();
    }
    DataCenter* root=current_DC;
    current_DC = this->DCs_arr[DC_ID];
    DataCenter* prev_DC = current_DC;
    //shrinking path to root
    while (current_DC->getNext()!= nullptr){
        current_DC = current_DC->getNext();
        prev_DC->setNext(root);
        prev_DC = current_DC;
    }
    return current_DC;
}

UnionFind::UnionFind(int n): DCs_arr(new DataCenter*[n+1]), n(n){
    this->DCs_arr[0] = nullptr;
    for(int i=1; i<=n; i++){
        this->DCs_arr[i] = new DataCenter(i);
    }
}


UnionFind::~UnionFind(){
    for(int i=1; i<=this->n; i++){
        delete this->DCs_arr[i];
    }
    delete[] DCs_arr;
    //std::cout << "~UnionFind()" << std::endl;
}

void UnionFind::removeServer(int DC_ID, int server_ID, int traffic){
    std::shared_ptr<DataCenterGroup> DC_group = findDCGroup(DC_ID);
    DC_group->removeServer(server_ID, traffic);
}

void UnionFind::addServer(int DC_ID, int server_ID, int traffic, const std::shared_ptr<Server>& server){
    std::shared_ptr<DataCenterGroup> DC_group = findDCGroup(DC_ID);
    DC_group->addServer(server_ID,traffic,server);
}


