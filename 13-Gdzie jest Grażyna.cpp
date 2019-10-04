#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
using namespace std;


int changeToMinutes(string g){
    unsigned int i=0;
    int wynik=0;
    string godz, min;
    bool wasCiapek = false;
    while(g[i]!='\0'){
        if(g[i]==':'){
            wasCiapek=true;
        }
        if(wasCiapek && g[i]!=':'){
            min+=g[i];
        }
        else{
            godz+=g[i];
        }
        i++;
    }
    wynik += (stoi(godz)*60)+stoi(min);
    return wynik;
}

int main()
{
    int start, end, room, godz, min;
    string temp1, temp2;
    srand(time(NULL));
    int wylosowana_liczba =0;
    double counter=0;
    cin >> temp1;
    cin >> temp2;
    cin >> room;

    start = changeToMinutes(temp1);
    end = changeToMinutes(temp2);

    for(int i=0; i<1000000;i++){
        wylosowana_liczba = rand() % (end-start+1) + start;
        godz = wylosowana_liczba/60;
        min = wylosowana_liczba%60;
        if(room==Grazyna(godz,min)){
            counter++;
        }
    }
    cout << fixed << setprecision(2) <<counter/1000000;



    return 0;
}

/*
8:00
22:00
0
*/