#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

typedef list<unsigned int> lista;

struct root{
    unsigned int wierzch, cel, koszt;
};



struct comparar{
    bool operator () (root &r1, root &r2) {
        if (r1.koszt > r2.koszt) return true;
        return false;
    }
};


void zmien_indeks(lista l1, unsigned int *wierzch, unsigned int gdzie){
    for(unsigned int i: l1){
        wierzch[i] = gdzie;
    }
}
void klusek(priority_queue <root, vector<root>, comparar> pq, unsigned int l_wierzcholkow){
    root pom;
    unsigned int wynik=0,gdzie;

    lista *kolory=new lista[l_wierzcholkow];
    unsigned int *wierzch = new unsigned int[l_wierzcholkow];

    for(unsigned int i=0;i<l_wierzcholkow;i++){
        kolory[i].push_back(i);
        wierzch[i]=i;
    }


    while (!pq.empty()) {
        pom = pq.top();
        pq.pop();

        if(wierzch[pom.wierzch] != wierzch[pom.cel]){

            gdzie = wierzch[pom.cel];

            zmien_indeks(kolory[gdzie], wierzch, wierzch[pom.wierzch]);
            kolory[wierzch[pom.wierzch]].merge(kolory[gdzie]);

            wynik+=pom.koszt;
        }
    }

    cout << wynik;
}



int main()
{
    ios_base::sync_with_stdio(false);


    unsigned int l_wierzch, l_krawedzi, a, b, koszt = 0, czy_wazne;
    priority_queue <root, vector<root>, comparar> pq;
    root pomo;


    cin >> l_wierzch >> l_krawedzi;
    bool *worth = new bool[l_wierzch];


    for(unsigned int i=0;i<l_wierzch;i++){
        cin >> czy_wazne;
        worth[i]=czy_wazne;
    }


    for(unsigned int i=0;i<l_krawedzi;i++){
        cin >> a >> b >> koszt;

        if(worth[b]==1 && worth[a]==1){

            pomo.cel=b;
            pomo.wierzch=a;
            pomo.koszt=koszt;

            pq.push(pomo);
        }
    }
    klusek(pq, l_wierzch);

    return 0;
}