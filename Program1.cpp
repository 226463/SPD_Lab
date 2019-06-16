#include <iostream>
//#include <time.h>
#include <unistd.h>
#include <cstdlib>	// potrzebne do system("clear");
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    getchar();
    system("clear");
    int n = 6; //rozmiar pozycji w pliku
    int *m1, *m2, *m3;
    int cmax=0;
    int zapas=0;
    int licznik =0;
    int bulion1[6];      // tablica pomocnicza
    int bulion2[6];     // tablica pomocnicza
    int bulion3[6];      // tablica pomocnicza
    int bulion4[6];     // tablica pomocnicza
    int cmaxBest=0;
    m1 = new int[n];
    m2 = new int[n];
    m3 = new int[n];

    ifstream data("dane.txt");
    for(int i=0; i<=n-1;i++) data >> m1[i] >> m2[i];
    data.close();
    for(int i=0; i<n; i++) m3[i]=i;



    cout << "m1=" << m1[0] << ' ' << m1[1] << ' ' << m1[2]<< " " << m1[3] << ' ' << m1[4] << ' ' << m1[5] << '\n';
    cout << "m2=" << m2[0] << ' ' << m2[1] << ' ' << m2[2]<< " " << m2[3] << ' ' << m2[4] << ' ' << m2[5] << '\n';
    cout << "m3=" << m3[0] << ' ' << m3[1] << ' ' << m3[2]<< " " << m3[3] << ' ' << m3[4] << ' ' << m3[5] << '\n';

    getchar();
    system("clear");
    licznik =0;
    //-----------------------------------------------------------------------------------
    do
    {
        for(int i=0;i<n;i++)
        {
            bulion1[i]=m1[m3[i]];
            bulion2[i]=m2[m3[i]];
        }
    //------------------------------------ f cmax -------------------
        cmax=0;
        zapas=0;
        for(int i=0;i<=n;i++) 
        {
            if(i==n)  bulion1[i]=0;
            if(i==0) cmax += bulion1[i];
            else if(i!=0)
            {
                if(bulion1[i] >= (bulion2[i-1]+zapas)) cmax += bulion1[i];
                else  
                {
                    cmax += bulion2[i-1];
                    zapas += bulion2[i-1]-bulion1[i];
                }
            }
        }
        //------------------------------------------------------------
        if(licznik==0 || cmax<cmaxBest)
        {
            cmaxBest = cmax;
            for(int j=0;j<=n;j++)
            {
                bulion3[j]=bulion1[j];
                bulion4[j]=bulion2[j];
            }
        }    
        licznik +=1;    
    } 
    while ( next_permutation(m3,m3+6) );   
  //-------------------------------------------------------------------------------------  
    cout << "licznik=" << licznik << endl;
    for(int i=0;i<n;i++)
    {
        cout << "bulion3[" << i <<"]= " << bulion3[i] << " ";
        cout << "bulion4[" << i <<"]= " << bulion4[i] << " ";
    }
    cout << endl;
    cout << "cmaxBest = "<< cmaxBest << endl;
}
