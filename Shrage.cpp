#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
 
class obiekt {
    public:
        int r;
        int p;
        int q;
        obiekt(int xr,int xp,int xq);
};
 
obiekt::obiekt( int xr,int xp,int xq )
    : r( xr )
    , p( xp )
    , q( xq ) {
}
 
vector < obiekt > N;
vector <obiekt> G;
vector <obiekt> PI;
 
 
int szukajmin() {
    int j=0;
    for(unsigned int i=0; i<N.size(); i++) {
        if(N[j].r<N[i].r) {
        } else {
            j=i;
        }
    }
    return j;
}
 
int szukajmx() {
    int j=0;
    for(unsigned int i=0; i<G.size(); i++) {
        if(G[j].q<G[i].q) {
            j=i;
        }
    }
    return j;
}
 
vector <obiekt> schrage(string data)
{
    int t=0;
    int k=0;
    int Cmax=0;
    ifstream plik;
   
   //----- Wczytywanie danych z pliku ------
    plik.open(data.c_str(), ios::out);
        int a,b,x,y,z;
    plik >>a >>b;
    //cout << "R\t P\t Q\t zad =" << a << endl;
    for (int i=0; i<a; i++) {
        plik>>x;
        plik>>y;
        plik>>z;
        N.push_back(obiekt(x,y,z));
        //cout << x << "\t" << y << "\t" << z << endl;
    }
    plik.close();
 
    while(N.size()!=0 || G.size()!=0) {
 
        while(N.size()!=0 && t>=N[szukajmin()].r) {
            G.push_back(N[szukajmin()]);
            N.erase(N.begin() +szukajmin());
        }
 
        if(G.size()==0) {
            t=N[szukajmin()].r;
            continue;
        }
 
        k=k+1;
        PI.push_back(G[szukajmx()]);
        t=t+G[szukajmx()].p;
        if(Cmax>(t+G[szukajmx()].q)){
            Cmax=Cmax;
        }else{
            Cmax=t+G[szukajmx()].q;
        }
        G.erase(G.begin() +szukajmx());

    }
 
      cout << "R\t P\t Q\t zad =" << a << endl;
    for(unsigned int i=0; i<PI.size(); i++) {
      cout<<PI[i].r<<"\t"<<PI[i].p<<"\t"<<PI[i].q<<"\t"<<endl;
    }
    cout<<data<<": "<<Cmax<<endl;
    return PI;
}

int shragePmtn(string xx)
{
        vector <obiekt> l;
    int t=0;
    int Cmax=0;
    ifstream plik;
    plik.open(xx.c_str(), ios::out);
    int a,b,x,y,z;
    plik>>a >>b;
    cout << "R\t P\t Q\t zad =" << a << endl;
    for (int i=0; i<a; i++) {
        plik>>x;
        plik>>y;
        plik>>z;
        N.push_back(obiekt(x,y,z));
        cout << x << "\t" << y << "\t" << z << endl;
    }
    plik.close();
 
    while(N.size()!=0 || G.size()!=0) {
 
        while(N.size()!=0 && t>=N[szukajmin()].r) {
 
            G.push_back(N[szukajmin()]);
 
            if(l.size()!=0) {
                if(N[szukajmin()].q>l[0].q) {
                    l[0].p=t-N[szukajmin()].r;
                    if(l[0].p>0) {
                        G.push_back(l[0]);
                        t=t-l[0].p;
                        l.erase(l.begin()+0);
                    }
                }
 
            }
            N.erase(N.begin() +szukajmin());
 
        }
 
        if(G.size()==0) {
            t=N[szukajmin()].r;
            continue;
        }
 
        PI.push_back(G[szukajmx()]);
        if(l.size()!=0) {
            l.erase(l.begin()+0);
        }
        l.push_back(G[szukajmx()]);
        t=t+G[szukajmx()].p;
        if(Cmax>(t+G[szukajmx()].q)) {
            Cmax=Cmax;
        } else {
            Cmax=t+G[szukajmx()].q;
        }
        G.erase(G.begin() +szukajmx());
    }
  
    cout<<xx<<": "<<Cmax<<endl;
    return Cmax;
}
 
int main() {
    cout<<"Czas pracy algorytmu Shrage dla"<<endl;
    schrage("in50.txt");
    getchar(); system("clear"); 
    schrage("in100.txt");
    getchar();  system("clear");  
    schrage("in200.txt");
    getchar();    system("clear");
	cout << endl;
    cout<<"Czas pracy algorytmu Shrage pmtn dla"<<endl;
    shragePmtn("in50.txt");
    getchar();  system("clear");  
    shragePmtn("in100.txt");
    getchar();   system("clear"); 
    shragePmtn("in200.txt");
    getchar();   system("clear"); 
    return 0;
}
