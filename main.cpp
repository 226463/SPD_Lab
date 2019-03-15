#include <iostream>
//#include <time.h>
#include <unistd.h>
#include <cstdlib>	// potrzebne do system("clear");
#include <fstream>
#include <algorithm>
using namespace std;

//-- Wyświetla dane z tablic m1 m2 i mLicz -------------------------------------
void wysDane(int *m1, int *m2, int cmax, int n)
{   
    getchar();getchar();
    system("clear");
    cout << "m1= ";
    for(int i=0; i<n; i++) cout << m1[i] << " ";
    cout << endl;
    cout << "m2= ";
    for(int i=0; i<n; i++) cout << m2[i] << " ";
    cout << endl;
    cout << "cmax = " << cmax << endl;
    getchar();getchar();
    system("clear");
}
//--F. Cmax -------------------------------------------------------------------
int cMax(int *bulion1, int *bulion2, int n)
{
    int cmax=0;
    int zapas=0;
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
    return cmax;    
}


//-- F. main -------------------------------------------------------------------
int main()
{   char menu;
    int n = 6;          //rozmiar pozycji w pliku
    int *m1, *m2, *m3, *wirtualm1, *wirtualm2, *mLicz; 
    int cmax=999;
    int licznik =0;
    int bulion1[6];      // tablica pomocnicza
    int bulion2[6];     // tablica pomocnicza
    int bulion3[6];      // tablica pomocnicza
    int bulion4[6];     // tablica pomocnicza
    int bulion5[6];
    int bulion6[6];
    int cmaxBest=0;
    int bestczas=0;       // do Alg. Joahnsona
    int suma=0;
    m1 = new int[n];
    m2 = new int[n];
    m3 = new int[n];
    wirtualm1 = new int[n];
    wirtualm2 = new int [n];
    mLicz = new int[n];  //mLicz pomocniczy wektor o elementach {0,1,2,3,4,5}
    for(int i=0; i<n; i++) mLicz[i]=i; //przypisanie wartości do mwektora mLicz

    //-- Wczytywanie danych z pliku ---------------------------------------------
    ifstream data("dane.txt"); 
    for(int i=0; i<=n-1;i++) data >> m1[i] >> m2[i] >> m3[i];
    data.close();
    //---------------------------------------------------------------------------
 while(1)
 {
    system("clear");
    cout << "Przegląd Zupełny......p"<<endl;
    cout << "Alg. Joahnsona........j"<<endl;
    cout << "koniec................k"<<endl;
    cin >> menu;
 switch(menu)
   {
 case 'p':
    system("clear");
    cout << "Prezentacja wczytanych danych,";
    cout << "cmax jeszcze nie było szukane,";
    cout << "wiec został ustawiony na liczbę  999" << endl;

    wysDane(m1, m2, cmax, n);
    
    //-- Sortowanie - Przegląd Zupełny ------------------------------------------
    do
    {
        for(int i=0;i<n;i++)
        {
            bulion1[i]=m1[mLicz[i]];
            bulion2[i]=m2[mLicz[i]];
        }
        cmax = cMax(bulion1, bulion2, n);
        if(licznik == 0 || cmax < cmaxBest)
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
    while ( next_permutation(mLicz,mLicz+6) );   
  //-------------------------------------------------------------------------------
    cout << "Prezentacja wyników końcowych:" << endl;
    cout << "Najlepsza wartośc cmax, oraz wektory m1 i m2, dla których dany cmax wystąpił" << endl;
    //cout << "licznik=" << licznik << endl;
    wysDane(bulion3, bulion4, cmaxBest, n);

 break;

 case 'j':
//------------------algorytm Johnsona----------------------------------------------
   system("clear");
   
    getchar();getchar();
    system("clear");
    cout << "m1= ";
    for(int i=0; i<n; i++) cout << m1[i] << " ";
    cout << endl;
    cout << "m2= ";
    for(int i=0; i<n; i++) cout << m2[i] << " ";
    cout << endl;
    cout << "m3= ";
    for(int i=0; i<n; i++) cout << m3[i] << " ";
    cout << endl;
   
    getchar();getchar();
    system("clear");

    for(int l=0;l<n;l++)
    {
	wirtualm1[l] = m1[l] + m2[l];        //oblixczanie wirtualnych maszyn
        wirtualm2[l] = m3[l] + m2[l];
	cout << " wirtualna maszyna 1 [" << l <<"] = "<< wirtualm1[l]<< endl;
		cout << "wirtualna maszyna 2 [" << l <<"] = "<< wirtualm2[l]<< endl;
	
    }
    
      for(int k=0;k<6;k++)
      {
	 for(int i=0;i<n;i++)
        {
	  if(k!=5)
	    {
	  if(i==0)
	    {
	    bestczas=wirtualm1[0];      //wybieranie operacji z nakrotszym czasem wyk.
	    }
            if(bestczas>wirtualm2[i]) bestczas=wirtualm2[i];
	    else if(bestczas>wirtualm1[i+1])
	      {
		bestczas=wirtualm1[i+1];
		//sprawdzenie czy suma z itego wm1 i wm2 jest wieksza niz i+1
	      }
	    }
	    
	     cout <<"najlepszy czas dla i = "<< i << "wynosi: "<< bestczas << endl;
            //  cout << "najkrótszy czas wykonania =" << bestczas << endl;    
        
	    if(i==5){
	      for(int j=0;j<n;j++){//pętla do eliminowania już wybranych operacji i przypisania to tab pom
		if(bestczas==wirtualm1[j]||bestczas==wirtualm2[j]||bestczas==wirtualm1[j+1])
	      {
		
		for(int m=0;m<n;m++)
		  {
		if(m==0 && k==0){
		  cout<<j<<" = ";
		     bulion6[5]= wirtualm2[j];
		     bulion5[5]=wirtualm1[j];
		     wirtualm2[j]=999;
	             wirtualm1[j]=999;
		     }
		else if(m==1 && k==1){
		  bulion6[0]= wirtualm2[j];
		     bulion5[0]=wirtualm1[j];
		     wirtualm2[j]=999;
	             wirtualm1[j]=999;
		     }
		else if(m==2 && k==2){
		  //cout<<m;
		  //cout<<k;
		     bulion6[4]= wirtualm2[j];
		     bulion5[4]=wirtualm1[j];
		     wirtualm2[j]=999;
	             wirtualm1[j]=999;
		     }
		else if(m==3 && k==3){
		  // cout<<m;
		  //cout<<wirtualm1[j]<<endl;
		  //cout<<wirtualm2[j]<<endl;
	  	     bulion6[1]= wirtualm2[j];
		     bulion5[1]= wirtualm1[j];
		     wirtualm2[j]=999;
	             wirtualm1[j]=999;
		     }
 	else if(m==4 && k==4){
	  //cout<<m<<endl;
		   cout<<k<<endl;
		   /* cout<<wirtualm1[j]<<endl;
		   cout<<wirtualm2[j]<<endl;*/
    		     bulion6[3]= wirtualm2[j];
		     bulion5[3]=wirtualm1[j];
		     //wirtualm2[j]=999;
	             //wirtualm1[j]=999;
	}
		/*	else if(m==5 && k==5){
		  cout<<"k= "<<k;

		  }*/
		 if(m==5 && k==5&&wirtualm1[j]>bestczas)
		  {
		     bulion6[2]= wirtualm2[j];
		     bulion5[2]=wirtualm1[j];
		}
		  } //koniec petli m
		}
	      
	      }
		
	    }//koniec fora m
		 /*   cout<<k<<endl;
			   cout<<i<<endl;
			   cout<<j<<endl;*/
	      //koniec fora j
	 }//koniec ifa i==5

     //koniec fora i
	 	 for(int y=0;y<6;y++)
		     {
	       cout << "\t wirtualna maszyna 1 [" << y <<"] = "<< wirtualm1[y]<< endl;
	       cout << "wirtualna maszyna 2 [" << y <<"] = "<< wirtualm2[y]<< endl;
		     }
		   cout << "bulion5 ";
	   for(int g=0; g<n; g++) cout << bulion5[g] << " ";
	      cout << endl;
	      
	      cout << "bulion6 ";
	   for(int h=0; h<n; h++) cout << bulion6[h] << " ";
	   cout << endl;
	   cout<<"Cmax = "<<cMax(bulion5, bulion6,n);
	   
      }

  
     

    getchar(); getchar();
//-- Wyjście z Programu ----------------------------------------------------------------------------
 break;
 case 'k':
    system("clear");
    return 0;
 break;
 }
}
}
