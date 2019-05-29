#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct qelement
 {
   int n;  ///numer zadania
   int r; ///termin dostepnosci
   int p; ///czas obslugi
   int q; ///czas dostarczenia
 };

class Calier_algorytm
{
    /*FUNKTORY DO POROWNANIA (DO KOLEJKI) */
struct sortowanie_malejace 
	{
    bool operator()(const qelement &dana1, const qelement &dana2)
		{
        if(dana1.q<dana2.q)
            return true;
        else
            return false;
   		}
 	};

struct sortowanie_rosnace 
	{
    bool operator()(const qelement &dana1, const qelement &dana2)
		{
        if(dana1.r>dana2.r)
            return true;
        else
            return false;
    	}
	};

 /*DEKLARACJE WEKTOROW I ZMIENNYCH*/
 vector<qelement> zad;
 vector<int> pi;
 vector<int> cz_zad;
 int a=0;
 int b=0;
 int c=-5;

 /*DEKLARACJE FUNKCJI*/
public:
    void Wczytaj(string nazwaPliku);
    void Kopiuj_dane(vector<qelement> kopiuj);
    int Schrage();
    int Schrage_z_podzialem();
    int blok_AB(int cmax);
    int min_r();
    int min_q();
    int suma_p();
    int Calier(int UB);
};

void Calier_algorytm::Wczytaj(string nazwaPliku)
 {
     ifstream plik(nazwaPliku.c_str(), ios::in);
     int n;
     qelement element;  ///element do wrzucania
     plik>>n;
     for(int i=0; i<n; i++)
	{
		plik>>element.r;
		plik>>element.p;
		plik>>element.q;
        element.n=i;
        zad.push_back(element);
	}
	cout<<"Liczba zadan: "<<n<<endl;
	plik.close();
 }

void Calier_algorytm::Kopiuj_dane(vector<qelement> kopiuj)
{   ///ABY KOLEJNY CARLIER DOSTAL JUZ ZADANIA PRZEROBIONE TJ. PRZESUNITE R LUB Q
    zad=kopiuj;
}

int Calier_algorytm::Schrage()
{
    priority_queue<qelement, vector<qelement>, sortowanie_rosnace> N; ///nieuszeregowane
    priority_queue<qelement, vector<qelement>,sortowanie_malejace> G; ///zadania gotowe
    int t=0;		///chwila czasowa
	int cmax=0;	///maksymalny z terminow dostarczenia zadan
	qelement e;
	///ZALADOWANIE DO N
	for(int i=0; i<zad.size(); i++)
        N.push(zad[i]);
    ///ALGORYTM SCHRAGE
    while((G.empty()!=true) || (N.empty()!=true)){
            while((N.empty()!=true) && (N.top().r<=t)){
                e=N.top();
                G.push(e);
                N.pop();
            }
            if(G.empty()==true)     ///jezeli zbior zadan gotowych do realizacji jest pusty, to chwila t przesuwana jest do momentu dostepnosci najwczesnijeszego zadania ze zboiru N
                t=N.top().r;
            else{                   ///jezeli zbior zadan gotowych do realizacji nie jest pusty, to ze zbioru wyznaczane jest zadanie o najwiekszym czasie dostarczenia
            e=G.top();
            G.pop();
            pi.push_back(e.n);
            t=t+e.p;                ///chwila czasowa jest przesuwane o czas wykonania tego zadania
            cz_zad.push_back(t);
            cmax=max(cmax,t+e.q);   ///czas dostarczenia do klienta

            }
    }
    return cmax;
}

int Calier_algorytm::Schrage_z_podzialem()
{
    priority_queue<qelement, vector<qelement>, sortowanie_rosnace> N; ///nieuszeregowane
    priority_queue<qelement, vector<qelement>,sortowanie_malejace> G; ///zadania gotowe
    int n;        ///liczba zadan
    int t=0;		///chwila czasowa
	int cmax=0;	///maksymalny z terminow dostarczenia zadan
	qelement e;
	qelement l;  ///aktalnie wykonywane zadanie
	///ZALADOWANIE DO N
	for(int i=0; i<zad.size(); i++)
        N.push(zad[i]);
    ///ALGORYTM SCHRAGE Z PODZIALEM
    ///R to moment przerwania; t moment zakonczenia zadania
    while((G.empty()!=true) || (N.empty()!=true)){
            while((N.empty()!=true) && (N.top().r<=t)){
                e=N.top();
                G.push(e);
                N.pop();
                if(e.q>l.q){      ///jesli znajdziemy zadanie, ktore ma mniejszy czas dostarczenia niz zadanie, ktore jest na maszynie to zdejmujemy
                    l.p=t-e.r;    ///i zmieniamy jej czas wykonania
                    t=e.r;       ///      zeby doladowac wszystkie zadania, ktore sa dosptene w momencie przerwania
                if(l.p>0)         ///jesli czas wykonania zadania zdjetego z maszyny jest wiekszy od zera, to jest spowrotem wrzucane do kolejki zadan gotowych do realziacji
                    G.push(l);
                }
            }
            if(G.empty()==true)     ///jezeli zbior zadan gotowych do realizacji jest pusty, to chwila t przesuwana jest do momentu dostepnosci najwczesnijeszego zadania ze zboiru N
                t=N.top().r;
            else{                   ///jezeli zbior zadan gotowych do realizacji nie jest pusty, to ze zbioru wyznaczane jest zadanie o najwiekszym czasie dostarczenia
            e=G.top();
            G.pop();
            l=e;                 /// wrzucenie zadania na maszyne
            t=t+e.p;                ///chwila czasowa jest przesuwane o czas wykonania tego zadania
            cmax=max(cmax,t+e.q);
            }
    }
    return cmax;
}

int Calier_algorytm::blok_AB(int cmax)
{
    int sigma;
    ///WYZNACZANIE B
    for(int j=0; j<=zad.size()-1; j++)
	{
        if(cmax==cz_zad[j]+zad[pi[j]].q)
            b=j;
    }
    ///WYZNACZANIE A
    for(int j=0; j<=zad.size()-1; j++)
	{
        sigma=0;
        for(int s=j; s<=b; s++){
            sigma=sigma+zad[pi[s]].p;
        }
        if(cmax==zad[pi[j]].r+sigma+zad[pi[b]].q)
		{
            a=j;
            break;
        }
    }
    ///WYZNACZANIE C
    for(int j=a; j<=b; j++)
	{
        if(zad[pi[j]].q<zad[pi[b]].q)
            c=j;
    }
}

int Calier_algorytm::suma_p()
{
    int sigma=0;
    for(int j=c+1; j<=b; j++){
        sigma=sigma+zad[pi[j]].p;
    }
    return sigma;
}

int Calier_algorytm::min_q()
{
    int mini_q=9999;
    for(int j=c+1; j<=b; j++){
        if(zad[pi[j]].q<mini_q)
            mini_q=zad[pi[j]].q;
    }
    return mini_q;
}

int Calier_algorytm::min_r()
{
    int mini_r=9999;
    for(int j=c+1; j<=b; j++){
        if(zad[pi[j]].r<mini_r)
            mini_r=zad[pi[j]].r;
    }
    return mini_r;
}

int Calier_algorytm::Calier(int UB)
{
    int cmax=0;
    int U;
    int LB;
    int rPR, qPR, pPR;
    int r_odtw, q_odtw;
    U=Schrage();
    if(U<UB)
        UB=U;

    blok_AB(U);

    if(c==-5)
	{
        cout << "Cmax = "<< UB << endl;
    
	int UB=9999999;
    string dane;
    cout << "podaj nazwê pliku" << endl;
    cin >> dane;
   	if(dane == "0") exit(0); 
	Calier_algorytm calier;
	calier.Wczytaj(dane);
	cout << "Cmax = " << calier.Calier(UB) << endl;
	//exit(0);
	return UB; 
	}

    rPR=min_r();
    qPR=min_q();
    pPR=suma_p();
    r_odtw=zad[pi[c]].r;
    zad[pi[c]].r=max(zad[pi[c]].r, rPR+pPR);

    LB=Schrage_z_podzialem();
    if(LB<UB)
	{
        Calier_algorytm Calier2;
        Calier2.Kopiuj_dane(zad);
        cmax=Calier2.Calier(UB);
    }

    zad[pi[c]].r=r_odtw;
    q_odtw=zad[pi[c]].q;
    zad[pi[c]].q=max(zad[pi[c]].q, qPR+pPR);
    LB=Schrage_z_podzialem();

    if(LB<UB)
	{
        Calier_algorytm Calier2;
        Calier2.Kopiuj_dane(zad);
        cmax=Calier2.Calier(UB);
    }
    zad[pi[c]].q=q_odtw;
    return cmax;
}

int main() 
{
    int UB=9999999;
    string dane;
    cout << "podaj nazwê pliku" << endl;
    cin >> dane;
   	if(dane == "0") exit(0); 
	Calier_algorytm calier;
	calier.Wczytaj(dane);
	cout << "Cmax = " << calier.Calier(UB) << endl;
	cout << "cos"; getchar();getchar();
	return 0;
}
