#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node{
    char c;
    bool isEndOfString;
    vector<Node*>child;
    Node(){
        isEndOfString = false;
    }
};

class Trie{
    Node *root;
    vector <string> toWrite;

public:
    Trie(){
        root = new Node;
        root->c=' ';
        
    }
    void insert(string temp_name){
        Node *temp = root;
        int index=0;
        bool isEnd = true;

        for(char i: temp_name){
            isEnd=true;
            for(Node *j: temp->child){
                if(j->c == i){
                    temp = j;
                    isEnd=false;
                    break;
                }
            }
            if(isEnd==true){
                break;
            }
            index++;
        }
        for(int i=index;i<temp_name.size();i++){
            Node *temp2 = new Node;
            temp2->c=temp_name[i];
            temp->child.push_back(temp2);
            temp = temp2;
        }
        temp->isEndOfString = true;
    }


    void search(string temp_name){
        Node *temp = root, temp2;
        toWrite.clear();
        bool isFound = false;
        string fatherString="";
        for(char i: temp_name){
            isFound = false;
            for(Node *j: temp->child){
                if(j->c == i){
                    fatherString+=j->c;
                    temp = j;
                    isFound = true;
                    break;
                }
            }
            if(isFound == false){
                break;
            }
        }

        if(isFound==true){
            if(temp->isEndOfString==true){
                toWrite.push_back(fatherString);
            }
            for(Node *node: temp->child){
                getLowerRoots(node, fatherString);
            }
            sort(toWrite.begin(), toWrite.end());
            for(string s: toWrite){
                cout<<s<<endl;
            }
        }


        if(toWrite.empty()){
            cout<<"-"<<endl;
            return;
        }
    }


    void getLowerRoots(Node *cos, string fatherString){
        if(cos->isEndOfString==true){
            toWrite.push_back(fatherString+cos->c);
        }
        for(Node *node: cos->child){
            getLowerRoots(node, fatherString+cos->c);
        }
    }

};



int main()
{
    ios_base::sync_with_stdio(false);
    string temp_name;
    int n;
    char operation;
    Trie treeTrie;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> operation >> temp_name;
        if(operation == 'A'){
            treeTrie.insert(temp_name);
        }
        else{
            treeTrie.search(temp_name);
        }
    }
    return 0;
}