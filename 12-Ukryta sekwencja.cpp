#include <iostream>
#include <string>
#include <vector>

using namespace std;

int hasz(vector <int> toCalculate){
    long code=5381;
    for(int i: toCalculate){
           code = code*33+i;
    }
    return code;
}

bool check(vector <int> klucz, vector <int> to_check){
    unsigned int iter = 0;
    for(int i: klucz){
        if(i != to_check[iter]) return false;
        iter++;
    }
    return true;
}



int main()
{
    ios_base::sync_with_stdio(false);
    int l_lancucha, element, l_klucza, hash_klucza, counter=0;
    vector <int> lancuch;   vector <int> klucz;
    int *tab = new int[2];
    tab[0]=0;   tab[1]=0;
    //wczytanie
    cin>>l_lancucha;
    for(int i=0;i<l_lancucha;i++){
        cin >> element;
        lancuch.push_back(element);
    }
    cin>>l_klucza;
    for(int i=0;i<l_klucza;i++){
        cin >> element;
        klucz.push_back(element);
    }


    //hash
    hash_klucza = hasz(klucz);

    //szukanie hashy w lancuchu

    for(int i = 0; i<l_lancucha-1 ; i++){
        vector <int> temp;
        for(int j = 0; j<l_klucza;j++){
            temp.push_back(lancuch[i+j]);
        }

        int temp_hash = hasz(temp);
        if(temp_hash == hash_klucza){
            if(check(klucz, temp)){ //sprawdzam czy faktycznie sa takie same
                tab[counter] = i;
                counter++;
            }
        }
        if((tab[0] + tab[1]) > l_lancucha){
            cout << (tab[0] + tab[1])-l_lancucha;
            return 0;
        }
        if(counter==2)  break;

    }
    
    int t=tab[0]+tab[1];
    while(t<l_lancucha){
        tab[0]=tab[1];
        tab[1]=t;
        t=tab[0]+tab[1];
    }

    if(t >= l_lancucha){
        cout << t-l_lancucha;
        return 0;
    }
    else if(t-l_lancucha < 0){
        cout << 0;
    }
    else {
        cout << t;
    }


//    cout << t << endl;
//    cout << tab[0] << "   " << tab[1] << endl;


    return 0;
}
/*
10
1 1 1 2 3 88 99 24 1 2
2
1 2

10


4
1 2 1 2
2
1 2

0



9
1 2 1 1 2 2 3 1 1
1
2

9


16
1 1 1 2 3 88 99 24 1 2 3 1 2 3 99 39
2
2 3

5




 */