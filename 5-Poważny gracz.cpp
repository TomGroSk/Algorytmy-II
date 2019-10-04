#include <iostream>

using namespace std;
struct Node{
    Node *father, *l_son, *r_son;
    int key;
    string text;
    Node(){
        father = nullptr;
        r_son = nullptr;
        l_son = nullptr;
    }
};
class BSTree{
public:
    Node *root;
    BSTree(){
        root = nullptr;
    }
    void insert(Node *temp){
        if(root == nullptr){
            root = temp;
            return;
        }
        Node *v = root;
        while(1){
            if(v->key < temp->key){
                if(v->r_son==nullptr){
                    v->r_son = temp;
                    temp->father=v;
                    return;
                }
                v = v->r_son;
            }
            else if(v->key >= temp->key){
                if(v->l_son==nullptr){
                    v->l_son = temp;
                    temp->father=v;
                    return;
                }
                v = v->l_son;
            }
        }
    }

    Node *nextnik(Node *temp){
        while(temp->l_son!=nullptr){
            temp = temp->l_son;
        }
        return temp;
    }

    Node *erase(Node *temp){
        if(temp->l_son==nullptr && temp->r_son==nullptr){ //if temp doesn't have sons
            if(temp==root){ //if temp is root
                root=nullptr;
                delete temp;
                return nullptr;
            }
            Node *father = temp->father;
            if(father->l_son == temp){ //if temp is left son
                father->l_son = nullptr;
            }
            else{                           //if temp is right son
                father->r_son = nullptr;
            }
            delete temp;
            return father;
        }
        else if(temp->l_son!=nullptr && temp->r_son!=nullptr){ //if temp have two sons
            Node *conseq = nextnik(temp->r_son);
            temp->key = conseq->key;
            temp->text = conseq->text;

            Node*father = temp->father;
            erase(conseq);
            return father;
        }
        else{ //if temp have one son
            if(temp==root){ //if temp is root
                if(temp->l_son!=nullptr && temp->r_son==nullptr){ //if temp have only left son
                    temp->l_son->father=nullptr;
                    root = temp->l_son;
                    delete temp;
                    return nullptr;
                }
                else if(temp->r_son!=nullptr && temp->l_son==nullptr){ //if temp have only right son
                    temp->r_son->father=nullptr;
                    root = temp->r_son;
                    delete temp;
                    return nullptr;
                }
            }
            Node *father = temp->father;
            if(temp->l_son!=nullptr && temp->r_son==nullptr){ //if temp have only left son
                Node *son = temp->l_son;
                if(father->l_son == temp){ //if temp is left son
                    son->father = father;
                    father->l_son = son;
                }
                else if(father->r_son == temp){ //if temp is right son
                    son->father = father;
                    father->r_son = son;
                }
            }
            else if(temp->l_son==nullptr && temp->r_son!=nullptr){ //if temp have only right son
                Node *son = temp->r_son;
                if(father->l_son == temp){ //if temp is left son
                    son->father = father;
                    father->l_son = son;
                }
                else if(father->r_son == temp){ //if temp is right son
                    son->father = father;
                    father->r_son = son;
                }
            }
            delete temp;
            return father;
        }
    }

    Node *search(int value){
        Node *temp = root;

        while (1) {
            if(temp==nullptr){
                return nullptr;
            }
            if(temp->key == value){
                return temp;
            }
            if(temp->key > value){
                temp = temp->l_son;
            }
            else{
                temp = temp->r_son;
            }
        }
    }
};



int main()
{
    ios_base::sync_with_stdio(false);

    int node, number_of_search, val, search_temp;
    string text;
    BSTree tree;
    Node *temp;

    cin >> node >> number_of_search;

    for(int i=0;i<node;i++){
        cin >> val >> text;
        temp = new Node;
        temp->text = text;
        temp->key = val;
        tree.insert(temp);
    }

    for (int i=0;i<number_of_search;i++) {
        cin >> search_temp;
        temp = tree.search(search_temp);

        if(temp==nullptr){
            cout<<"NIE"<<endl;
        }
        else{
            while (temp != nullptr) {
                cout << temp->text;
                temp = tree.erase(temp);
            }
            cout<<endl;
        }
    }
    return 0;
}
/*
9 4
10 kota
5 ma
15 Dana
3 Te
8 Ala
11 st
12 Ostatni
18 testowa
4 xyz
8 20 3 12
*/