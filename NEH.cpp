#include <iostream>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <cstdlib>	// potrzebne do system("clear");
#include <fstream>
#include <algorithm>
using namespace std;

int cMax( int **Dane, int masz, int zad );
int* TabSuma(int **Dane, int masz, int zad);
void wysDane(int **Dane, int masz, int zad);
int** NEH( int **Dane, int masz, int zad );

//-- Wyswietla dane z tablie z danymi -------------------------------------
void wysDane(int **Dane, int masz, int zad)
{   
    for ( int i = 0; i < masz; ++i, cout<<endl )
 		for ( int j = 0; j < zad; ++j)
 			cout<<Dane[i][j]<<'\t'; 
    getchar(); getchar();         
    system("clear");

}
int* TabSuma(int **Dane, int masz, int zad)
{
    int *Tab = new int[zad];
    for( int i = 0; i < zad; i++ )
    {
        Tab[i] = 0;
        for( int j = 0; j < zad; j++ )
            Tab[i] += Dane[i][j];
    }
    
    return Tab;
}

//---NEH----
int** NEH( int **Dane, int masz, int zad )
{
    //-- tablica na ostateczną wersję macierzy - macierz wynikowa
   	int **tabNeh = new int *[zad];
    int **tab43 = new int *[zad];
    for( int i = 0; i < zad; i++ )
	{
		tabNeh[i] = new int [masz];
        tab43[i] = new int [masz];
		for( int j =0; j < masz; j++)
		{
			tabNeh[i][j] = 0;
            tab43[i][j] = 0;
		}			
	}
    //-------------------------------------------
    int* tabIndex = new int[zad];
    int* tab34 = new int[zad];
    for( int i = 0; i < zad; i++ ) 
    {
        tabIndex[i] = i; // indeksy
        tab34[i] = 0;
    }
    tab34 = TabSuma(Dane, masz, zad);   //wartości sum
 
  //  for( int i = 0; i < zad; i++ )  cout << "indeks1 = " << tabIndex[i] << "    " << tab34[i] << " " <<  endl; // wyświetlanie do testów
 
    //--sortowanie od największego do najmniejszego
    for( int i = 0 ; i < zad; i++ ) 
    {
        for( int j = 1; j < zad; j++ )
        {
            if( tab34[j-1] < tab34[j] )
            {
            swap(tab34[j-1], tab34[j]);
            swap(tabIndex[j-1], tabIndex[j]);
            }
        }
    }
    //-- Posortowane Malejaco


   // for( int i = 0; i < zad; i++ )  cout << "indeks = " << tabIndex[i] << " " << tab34[i] << " " <<  endl;  //wyśiwetlanie - do testów
    
    int cmax1, indeksCmax, cmaxControl; //  cmax2;
    tabNeh[0] = Dane[tabIndex[0]]; 
    //cmaxControl = 99999;
    indeksCmax = 0;    
    for( int i = 1; i < zad; i ++) 
    {
    // --- Pętla wykonujaca się tyle razy ile jest zadań  za każdym razem dokłada jedno zadanie  
        cmaxControl = 99999;
        for( int j = 0; j <= i; j++ )      // mieszanie w celu uzyskania najlepszego cmax
        {
            for( int k = 0; k < i+1; k++ )
            {
            if( k < j ) tab43[k] = tabNeh[k];
            else if( k == j) tab43[k] = Dane[tabIndex[i]];
            else if( k > j ) tab43[k] = tabNeh[k-1];
            }
//            wysDane(tab43,i+1,masz);
            cmax1 = cMax(tab43,masz,i+1);
//            cout << "Przed if: cmax1= " << cmax1 << endl; 
//            cout << "cmaxControl= " << cmaxControl << endl;
//            cout << "indeksCmax= " << indeksCmax << endl;  
            if(cmax1 < cmaxControl )
            {
                cmaxControl = cmax1; 
                indeksCmax = j;
            }
//            cout << "Po if: cmax1= " << cmax1 << endl; 
//            cout << "cmaxControl= " << cmaxControl << endl;
//            cout << "indeksCmax= " << indeksCmax << endl;          
        }
        for( int k = 0; k < i+1; k++ )
        {
            if( k < indeksCmax ) tabNeh[k] = tab43[k];
            else if( k == indeksCmax ) tabNeh[k] = Dane[tabIndex[i]];
            else if( k > indeksCmax ) tabNeh[k] = tab43[k-1];
        }
//         wysDane(tabNeh,i+1,masz);
//         cmax2=cMax(tabNeh,masz,i+1);
//         cout << "cmax2= " << cmax2 << endl;
    }
    
    return tabNeh; 
}

//-------------------------------------------------------------------------------------------
int cMax( int **Dane, int masz, int zad )
{
    int i =0, j = 0;
    int cmax = 0;
    cmax += Dane[i][j];
    int **czasZak = new int *[zad];
    for( int i = 0; i < zad; i++ )
	{
		czasZak[i] = new int [masz];
		for( int j =0; j < masz; j++)
		{
			czasZak[i][j] = 0;
		}			
	}
     
    for( int i = 0; i < zad; i++ ){ 
        czasZak[i][0] = Dane[i][0];
        if(i != 0){
            czasZak[i][0] += czasZak[i-1][0];
        }
    }

    for( int i = 0; i < masz; i++ ){
        czasZak[0][i] = Dane[0][i];
        if(i != 0){
            czasZak[0][i] += czasZak[0][i-1];
        }
    }
    
    for( int i = 1; i < zad; i++ )
    {
        for( int j = 1; j < masz; j++ )
        {
            czasZak[i][j] = Dane[i][j] + max(czasZak[i-1][j], czasZak[i][j-1]);
        }
    }
    return czasZak[zad-1][masz-1];
}     
//---------------------------------------------------------------------------------------- 
void czekaj( int iMilisekundy )
{
    clock_t koniec = clock() + iMilisekundy * CLOCKS_PER_SEC / 1000.0;
    while( clock() < koniec ) continue;
    
}
double obliczSekundy( clock_t czas )
{
    return static_cast < double >( czas ) / CLOCKS_PER_SEC;
}
//-- F. main -------------------------------------------------------------------
int main()
{  
	int zad, masz, cmax;  
    double czas1, czas2, czas;
    //-- Wczytywanie Dnych -----------------------------
	ifstream data("dane.txt");
     data >> zad >> masz;   
	 
	cout << "masz="<<"  "<<masz<<" zad="<<zad<<endl;   
   	int **Dane = new int *[zad];
    for( int i = 0; i < zad; i++ )
	{
		Dane[i] = new int [masz];
		for( int j =0; j < masz; j++)
		{
			data >> Dane[i][j];
		}			
	}
   data.close();
   cmax = cMax(Dane, masz, zad);
   cout << "Nieposortowane \n"<< "cmax = " << cmax << endl;
   wysDane(Dane,zad,masz);
   czas1 = obliczSekundy( clock() ); //Start czasu - pierwszy pomiar
   Dane = NEH( Dane, masz, zad );
  // czekaj( 5000 );
   czas2 = obliczSekundy( clock() ); //Stop czasu - drugi pomiar
   cmax = cMax(Dane, masz, zad);
   cout << "Posortowane \n" << "cmax = " << cmax << endl;  
   czas = czas2 - czas1;    // Obliczenie czasu trwania algorytmu
   cout << "mineło: " << czas << "[s]" << endl;
   wysDane(Dane,zad,masz);
   return 0;
}
