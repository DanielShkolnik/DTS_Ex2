#ifndef AVL_H_
#define AVL_H_

#include "node.h"
#include <memory>
template <class K, class D>
class Avl{
private:
    std::shared_ptr<Node<K,D>> head;
    std::shared_ptr<Node<K,D>> find_nearest(K key);
    void fix_BFs(std::shared_ptr<Node<K,D>> leaf); //CHANGE TO SMART PTR
    void update_head(std::shared_ptr<Node<K,D>> node);
    void fix_relations(std::shared_ptr<Node<K,D>> A, std::shared_ptr<Node<K,D>> B);
public:
    Avl():head(nullptr){}
    explicit Avl(int size);
    ~Avl();
    Avl(const Avl& avl)= delete;
    Avl& operator=(const Avl& avl)= delete;
    void insert(const K& key, std::shared_ptr<D> data, int traffic); // Daniel
    void delete_element(const K& key); // Omer
    std::shared_ptr<D> find(const K& key); // Omer
    std::shared_ptr<Node<K,D>> getHead();
    int getBF(std::shared_ptr<Node<K,D>> node); // Dainel
    void rotateLL(std::shared_ptr<Node<K,D>> node); // Omer
    void rotateLR(std::shared_ptr<Node<K,D>> node); // Omer
    void rotateRL(std::shared_ptr<Node<K,D>> node); // Daniel
    void rotateRR(std::shared_ptr<Node<K,D>> node); // Daniel

    void treeClear();

    class Error{};
    class KeyExists{};
    class KeyNotFound{};
};

template <class K, class D>
void Avl<K,D>::insert(const K& key, std::shared_ptr<D> data, int traffic){
    std::shared_ptr<Node<K,D>> nearest_node=this->find_nearest(key);
    std::shared_ptr<Node<K,D>> new_node_ptr = std::shared_ptr<Node<K,D>>(new Node<K,D>(key,data,nearest_node,traffic));
    if(nearest_node == nullptr){
        this->head=new_node_ptr;
        return;
    }
    if (nearest_node->getKey()==key) throw Avl<K,D>::KeyExists();
    if (key>nearest_node->getKey()) nearest_node->setRight(new_node_ptr);
    if (key<nearest_node->getKey()) nearest_node->setLeft(new_node_ptr);
    this->fix_BFs(new_node_ptr);
    this->update_head(new_node_ptr);
}

// gets the key and returns element with the nearest existing key
template <class K, class D>
std::shared_ptr<Node<K,D>> Avl<K,D>::find_nearest(K key) {
    if(this->head == nullptr) return nullptr; // avl is empty->
    std::shared_ptr<Node<K,D>> current_node = this->head;
    std::shared_ptr<Node<K,D>> prev_node = this->head;
    while (current_node){
        prev_node = current_node;
        if(key > current_node->getKey()){
            current_node = current_node->getRight();
        } else if(key == current_node->getKey()){
            return current_node;
        } else{
            current_node = current_node->getLeft();
        }
    }
    return prev_node;
}
template <class K, class D>
void Avl<K,D>::rotateLL(std::shared_ptr<Node<K,D>> B){
    std::shared_ptr<Node<K,D>> B_papa=B->getPapa();
    std::shared_ptr<Node<K,D>> A = B->getLeft();
    std::shared_ptr<Node<K,D>> A_right = A->getRight();
    A->setRight(B);
    B->setLeft(A_right);
    if (B_papa!=nullptr)fix_relations(B_papa,A);
    else A->setPapa(nullptr);
    fix_relations(A,B);
    if (A_right!= nullptr) fix_relations(B,A_right);
    B->calcHeight();
    A->calcHeight();
    B->calcRank();
    A->calcRank();
}

template <class K, class D>
void Avl<K,D>::rotateLR(std::shared_ptr<Node<K,D>> C){
    std::shared_ptr<Node<K,D>> B = C->getLeft();
    std::shared_ptr<Node<K,D>> A = B->getRight();
    std::shared_ptr<Node<K,D>> A_left = A->getLeft();
    std::shared_ptr<Node<K,D>> A_right = A->getRight();
    std::shared_ptr<Node<K,D>> C_papa = C->getPapa();
    A->setLeft(B);
    B->setRight(A_left);
    A->setRight(C);
    C->setLeft(A_right);
    if(C_papa == nullptr) A->setPapa(nullptr);
    else fix_relations(C_papa,A);
    fix_relations(A,C);
    fix_relations(A,B);
    if(A_left != nullptr) fix_relations(B,A_left);
    if(A_right != nullptr) fix_relations(C,A_right);
    B->calcHeight();
    C->calcHeight();
    A->calcHeight();
    B->calcRank();
    C->calcRank();
    A->calcRank();
}
template <class K, class D>
std::shared_ptr<D> Avl<K,D>::find(const K& key){
    std::shared_ptr<Node<K,D>> nearest = this->find_nearest(key);
    if(nearest== nullptr || nearest->getKey() != key){
        throw Avl<K,D>::KeyNotFound(); //empty tree
    }
    else return nearest->getData();
}

template <class K, class D>
void remove_from_papa(const std::shared_ptr<Node<K,D>>& node){
    if(node->isRoot()) return;
    if(is_left_son(node)) node->getPapa()->setLeft(nullptr);
    else node->getPapa()->setRight(nullptr);
}

template <class K, class D>
void Avl<K,D>::delete_element(const K& key){
    // left->right->right....
    std::shared_ptr<Node<K,D>> nearest = this->find_nearest(key);
    if(nearest== nullptr || nearest->getKey()!=key) throw Avl<K,D>::KeyNotFound();

    // only one element
    if(nearest->isLeaf() && nearest->isRoot()){
        this->head = nullptr;
        return;
    }
    //leaf and not root => papa exists
    else if(nearest->isLeaf()){
        remove_from_papa(nearest);
        this->fix_BFs(nearest->getPapa()); // fix balance from leaf parent
        this->update_head(nearest->getPapa());
    }
    //no left son but not leaf => right son and papa exists
    else if(nearest->getLeft()== nullptr){
        if(nearest->getPapa() != nullptr) fix_relations(nearest->getPapa(),nearest->getRight());
        else nearest->getRight()->setPapa(nullptr);
        fix_BFs(nearest->getRight());
        this->update_head(nearest->getRight());
    }
    //find the left->right->right....son
    else{
        std::shared_ptr<Node<K,D>> current = nearest->getLeft();
        while (current->getRight()!= nullptr){
            current = current->getRight();
        }
        // path is only one to the left
        if(current == nearest->getLeft()){
            if (nearest->getPapa() != nullptr)fix_relations(nearest->getPapa(),current);
            else current->setPapa(nullptr); // if the nearest is the root.
            if(nearest->getRight() != nullptr) fix_relations(current,nearest->getRight());
            else current->setRight(nullptr);
            this->fix_BFs(current);
            this->update_head(current);
        }
        else{
            std::shared_ptr<Node<K,D>> changed_from = current->getPapa(); // save parent of leaf to fix balance from
            if(current->getLeft() != nullptr) fix_relations(current->getPapa(),current->getLeft());
            else current->getPapa()->setRight(nullptr);
            if(nearest->getPapa() != nullptr) fix_relations(nearest->getPapa(),current);
            else current->setPapa(nullptr); // if the nearest is the root
            if(nearest->getRight() != nullptr) fix_relations(current,nearest->getRight());
            else current->setRight(nullptr);
            fix_relations(current,nearest->getLeft());
            this->fix_BFs(changed_from);
            this->update_head(current);
        }

    }
}
template <class K, class D>
bool is_left_son(std::shared_ptr<Node<K,D>> node){
    if(node->getPapa()->getLeft()== nullptr) return false;
    return node->getPapa()->getLeft()->getKey()==node->getKey();
}
template <class K, class D>
void Avl<K,D>::rotateRR(std::shared_ptr<Node<K,D>> B){
    std::shared_ptr<Node<K,D>> B_papa=B->getPapa();
    std::shared_ptr<Node<K,D>> A=B->getRight();
    std::shared_ptr<Node<K,D>> A_left=A->getLeft();
    A->setLeft(B);
    B->setRight(A_left);
    if (B_papa!=nullptr)fix_relations(B_papa,A);
    else A->setPapa(nullptr);
    fix_relations(A,B);
    if (A_left!= nullptr) fix_relations(B,A_left);
    B->calcHeight();
    A->calcHeight();
    B->calcRank();
    A->calcRank();
}

template <class K, class D>
void Avl<K,D>::rotateRL(std::shared_ptr<Node<K,D>> C){
    std::shared_ptr<Node<K,D>> C_papa=C->getPapa();
    std::shared_ptr<Node<K,D>> B=C->getRight();
    std::shared_ptr<Node<K,D>> A=B->getLeft();
    std::shared_ptr<Node<K,D>> A_left=A->getLeft();
    std::shared_ptr<Node<K,D>> A_right=A->getRight();
    A->setLeft(C);
    C->setRight(A_left);
    A->setRight(B);
    B->setLeft(A_right);
    if(C_papa!= nullptr)fix_relations(C_papa,A);
    else A->setPapa(nullptr);
    if(A_left!= nullptr)fix_relations(C,A_left);
    fix_relations(A,B);
    fix_relations(A,C);
    if(A_right!= nullptr)fix_relations(B,A_right);
    C->calcHeight();
    B->calcHeight();
    A->calcHeight();
    C->calcRank();
    B->calcRank();
    A->calcRank();
}

template <class K, class D>
int Avl<K,D>::getBF(std::shared_ptr<Node<K,D>> node){
    if(node->getLeft()== nullptr && node->getRight()== nullptr) return 0; // leaf
    else if(node->getRight()==nullptr) return node->getLeft()->getHeight(); // no right son
    else if(node->getLeft()==nullptr) return -(node->getRight()->getHeight()); // // no left son
    return node->getLeft()->getHeight()-node->getRight()->getHeight();
}



template <class K, class D>
void Avl<K,D>::fix_BFs(std::shared_ptr<Node<K,D>> node){
    std::shared_ptr<Node<K,D>> current = node;
    if(node->isLeaf()){
        current->calcHeight();
        current->calcRank();
        current = current->getPapa();
    }
    if(current == nullptr) return;
    while (current){
        int prev_height = current->getHeight();
        current->calcHeight();
        current->calcRank();
        std::shared_ptr<Node<K,D>> prev = current;
        current = current->getPapa();
        int BF = this->getBF(prev);
        if(prev_height == prev->getHeight() && BF <2 && BF > -2){
            return;
        }

        //LL
        if(BF == 2 && this->getBF(prev->getLeft())>=0){
            this->rotateLL(prev);
        }
        //LR
        else if(BF == 2 && this->getBF(prev->getLeft())==-1){
            this->rotateLR(prev);
        }
        //RL
        else if(BF==-2 && this->getBF(prev->getRight())==1){
            this->rotateRL(prev);
        }
        //RR
        else if(BF==-2 && this->getBF(prev->getRight())<=0){
            this->rotateRR(prev);
        }

    }
}


template <class K, class D, class P>
void inorder(std::shared_ptr<Node<K,D>> node, P& predicate){
    if (node== nullptr) return;
    inorder(node->getLeft(),predicate);
    predicate(node);
    inorder(node->getRight(),predicate);
}

template <class K, class D, class P>
void preorder(std::shared_ptr<Node<K,D>> node, P predicate){
    if (node== nullptr) return;
    predicate(node);
    preorder(node->getLeft(),predicate);
    preorder(node->getRight(),predicate);
}

template <class K, class D, class P>
void postorder(std::shared_ptr<Node<K,D>> node, P predicate){
    if (node== nullptr) return;
    postorder(node->getLeft(),predicate);
    postorder(node->getRight(),predicate);
    predicate(node);
}
template <class K, class D>
std::shared_ptr<Node<K,D>> Avl<K,D>::getHead(){
    return this->head;
}
template <class K, class D>
void Avl<K,D>::update_head(std::shared_ptr<Node<K,D>> node){
    while(node->getPapa() != nullptr){
        node = node->getPapa();
    }
    this->head = node;
}

template <class K, class D>
void Avl<K,D>::fix_relations(std::shared_ptr<Node<K,D>> papa, std::shared_ptr<Node<K,D>> son){
    if (!papa || !son) throw Avl<K,D>::Error();
    if (papa->getKey()>son->getKey()) papa->setLeft(son);
    else papa->setRight(son);
    son->setPapa(papa);
}

template <class K, class D>
// inner destroy node without rolls (predicate for destructor)
void destroy(const std::shared_ptr<Node<K,D>>& node){
    node->setPapa(nullptr);
    node->setRight(nullptr);
    node->setLeft(nullptr);
}
template <class K, class D>
Avl<K,D>::~Avl(){
    postorder<K,D,void (const std::shared_ptr<Node<K,D>>& node)>(this->head,destroy);
}

template <class K, class D>
void Avl<K,D>::treeClear() {
    postorder<K,D,void (const std::shared_ptr<Node<K,D>>& node)>(this->head,destroy);
}

template <class K, class D>
Avl<K,D>::Avl(int size){
    std::shared_ptr<Node<K,D>> node_arr[size+1];
    // init array with offset 1 of pointers to empty nodes
    for(int i=1; i<=size; i++){
        node_arr[i] = std::shared_ptr<Node<K,D>>(new Node<K,D>());
    }
    // algorithm to build a tree from an array
    this->head = node_arr[1];
    for(int i=1; i<=size; i++){
        if(2*i<=size){
            node_arr[i]->setLeft(node_arr[2*i]);
            node_arr[2*i]->setPapa(node_arr[i]);
        }
        if(2*i+1<=size){
            node_arr[i]->setRight(node_arr[2*i+1]);
            node_arr[2*i+1]->setPapa(node_arr[i]);
        }
    }
}

#endif
