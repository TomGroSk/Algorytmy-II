#include <iostream>
#include <math.h>
using namespace std;



double calk(double b){
    double objet = 0;
    for(double i=0.01;i<b;i+=0.01){
        objet += 2*butelka(i-0.01)*butelka(i);
    }
    return objet*0.5*0.01*M_PI;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int x,y,z;
    double j,objet_akw,p,n;
    cin >> x >> y >> z;
    cin >> p;
    objet_akw = (x*y*z)*(1-p);
    cin >> n;

    for(int i=0;i<n;i++){
        cin >> j;
        if((objet_akw-=calk(j))<=0){
            cout<<i+1;
            return 0;
        }
    }
    cout <<"NIE";
    return 0;
}