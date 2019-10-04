#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Node{
    string key, value;
};
struct HashNode{
    vector <Node> nod;
};


class HashTabe{
public:
    
    HashNode *tab;
    int size, currentSize;
    
    HashTabe(){
        size = 10000;
        currentSize = 0;
        tab = new HashNode[size];
    }
    int hashCode(string key){
        int temp = 0;
        for(char c: key){
            temp += c%size;
        }
        return temp%size;
    }

    void insert(string key, string value){
        Node temp;
        
        int index = hashCode(key);
        
        temp.key = key;
        temp.value = value;

        tab[index].nod.push_back(temp);

        currentSize++;
    }

    void search(string key){
        if(currentSize == 0){
            cout << "-" << endl;
            return;
        }

        int index = hashCode(key);
        if(!tab[index].nod.empty()){
            for(unsigned int i=0;i<tab[index].nod.size();i++){
                if(tab[index].nod[i].key == key){
                    cout << tab[index].nod[i].value << endl;
                }
            }
            return;
        }

        cout << "-" << endl;
        return;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    string temp_name, temp_key;
    HashTabe hTable;
    int n;
    char operation;

    cin >> n;
    for(int i=0;i<n;i++){
        cin >> operation;
        if(operation == 'A'){
            cin >> temp_key >> temp_name;
            hTable.insert(temp_key, temp_name);
        }
        else{
            cin >> temp_key;
            hTable.search(temp_key);
        }
    }
    return 0;
}