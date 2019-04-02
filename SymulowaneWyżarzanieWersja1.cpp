#include <iostream>
#include <time.h>
#include <unistd.h>
#include <cstdlib>		// potrzebne do system("clear");
#include <fstream>
#include <algorithm>
#include <ctime>
#include <math.h>
//#include <Windows.h> 
using namespace std;

int cMax( int **Dane, int masz, int zad );
void wysDane(int **Dane, int masz, int zad);

//-- Wyswietla dane z tablie z danymi -------------------------------------
void wysDane(int **Dane, int masz, int zad)
{
    for ( int i = 0; i < masz; ++i, cout<<endl )
 		for ( int j = 0; j < zad; ++j)
 			cout<<Dane[i][j]<<'\t';
    getchar(); getchar();
    system("clear");

}
//-------------------------------------------------------
int ** kolejnosc(int **Dane, int zad, int masz)
{
	for (int i = 0; i < zad - 1; i++)
	{
		for (int j = 1; j < zad; j++)
		{
			int suma1 = 0, suma2 = 0;
			for (int k = 0; k < masz; k++)
			{
				suma1 += Dane[j - 1][k];
				suma2 += Dane[j][k];
			}
			if (suma1 < suma2)
			{
				swap(Dane[j - 1], Dane[j]);
			}
		}
	}
	return Dane;
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
//----------------------------------------------
// algorytm NEH
int ** Neh(int ** Dane, int zad, int masz)
{
	int cmax=0;
	int index=0;
	for (int i = 0; i < zad; i++)
	{
		int tmax = 10000000;
		for (int j = i; j >= 0; j--)
		{
			cmax = cMax(Dane, i+1, masz);
			if (tmax > cmax)
			{
				tmax = cmax;
				index = j;
			}
			if (j != 0)
			{
				swap(Dane[j], Dane[j - 1]);
			}
		}
		for (int k = 0; k < index; k++)
		{
			swap(Dane[k], Dane[k + 1]);
		}

	}
	return Dane;
}
//------------------------------------------------------

// Generowanie ruchu - swap - funkcja potrzebna do alg. Symulowanego Wyżarzania
int **fnSwap(int **Dane, int zad, int masz )
{
	srand( time( NULL ) );
	int a, b;
	a = (rand() %zad );
	b = (rand() %zad );
	while( a == b ) b = (rand() %zad );

//	cout << a << "\t" << b << endl; getchar();
	for( int i = 0; i < masz; i++ )
		swap( Dane[a][i], Dane[b][i] );

	return Dane;
}
//---------------------------------------------
// algorytm Symulowanego Wyżarzania
//-------------------------------------

int **symWyz( int **Dane, int zad, int masz, float T0, float u, int nrIteracjiMax, int Tmax )
{
//	Dane -	Tablica tablic zawierajaca wczytane zadania
//	zad	 -	całkowita liczba zadań
// 	masz -	całkowita liczba maszyn
//	T0   -	Temperatura startowa ( może być podana przez użytkownika )
//	u	 -	współczynnik schładzania ( na wyższą ocenę dokonac porównania dla wartości u = 0,8 / 0,9 / 0,95 / 0,99 - może być podana przez użytkownika )

//--- K R O K - I	--->	INICJALIZACJA	---
//-- Generuj rozwiązanie początkowe PI0
//-- PI0 rozwiązanie początkowe 
	//PI0 = Neh(Dane,zad,masz);	//opcja kiedy fynkcja NEH będzie działac
	//PI0 = Dane;	// opcja która jako rozwiązanie początkowe bierze konfigurację bazową (1,2,3,4) - stosowane dopóki nie działa NEH
	int ** PI = new int *[zad];
	int ** PI0 = new int *[zad];
	int ** PIprim = new int *[zad];
    for( int i = 0; i < zad; i++ )
	{
		PI[i] = new int [masz];
		PI0[i] = new int [masz];
		PIprim[i] = new int [masz];
		for( int j =0; j < masz; j++)
		{
			PI0[i][j] = Dane[i][j];
			PI[i][j] = 0;
			PIprim[i][j] = 0;
		}
	}
	//-- PI Rozwiązanie aktualne - PI = PI0;
	for( int i = 0; i < zad; i++ )
	{
		for( int j = 0; j < masz; j++ ){
			PI[i][j] = PI0[i][j];
			PIprim[i][j] = PI[i][j];
			}
	}

	//-- Ustaw temperaturę startową T0
	float T = T0;	// T0 podany jako argument funkcji - może być zadany przez użytkownika
//--- K R O K - II	--->	GENEROWANIE RUCHU	---
	//--- NA PODSTAWIE PI, WYGENERUJ SĄSIADA PIprim - PIprim = fN(PI) - funkcja generująca sąsiada - użyć swap ( na wyższą ocenę porównać z Insert zamiast swap )	
	PIprim = fnSwap(PIprim,zad,masz);

//= = =  K R Y T E R I U M   S T O P U = = = | | = = = P O C Z Ą T E K   P Ę T L I ===
//for( int nrIteracji = 0; i < nrIteracjiMax && T >= Tmax; nrIteracji ++ )	// Ograniczenie rozszerzone - ilość iteracji + maksymalna temperatura (minimalna)
//for( int nrIteracji = 0; i < nrIteracjiMax && T >= Tmax && /*czas<=czasmax*/; nrIteracji ++ )	// Ograniczenia maksymalne - jak wyzej + czas trwania symulacji - wymaga dopracowania
//for( int nrIteracji = 0; i < nrIteracjiMax; nrIteracji ++ )		// Ograniczenie podstawowe - tylko ilość iteracji
for( int nrIteracji = 0; nrIteracji < nrIteracjiMax; nrIteracji ++ ){
//--- KROK - III ---> WYKONANIE LUB NIE WYKONANIE RUCHU ---
	//-- WYZNACZ PRAWDOPODOBIEŃSTWO PRZEJŚCIA DO PIprim - p <- P(Cmax(PI),Cmax(PIprim),T)
	float p = exp( ( cMax( PI, masz, zad ) - cMax( PIprim, masz, zad ) ) / T );
//	cout << "p = " << p << endl;
		
//-- p >= rand(0,1) IF !!!!!!!!!!!!!!! Dopracować RANDOM - if jest ok ale random może być źle 
	srand( time( NULL ) );
	float ran;
	for(int i=0;i<10;i++){
	ran = ( ( (rand() %1000 ) + 99 ) / 1000.000 );
//	cout << "random= " << ran << endl;
	}
	if( p >= ran )
	{
		for( int i = 0; i < zad; i++ )
		{
			for( int j = 0; j < masz; j++ )
				PI[i][j] = PIprim[i][j];		
		}
		cout << "TAK" << endl;
	} 
//--- KROK - IV ---> SCHŁADZANIE ---
	//-- T <-- fc(T) --
//	cout << "T = " << T << "	u = " << u << endl;
	T = u * T;
//	cout << "T = " << T << endl;
	//T = T * ( k / kmax );	//alternatywna wersja - wymaga zdefiniowania k i kmax ( ograniczenia ze względu na ilość iteracji )
//--- KROK - V ---> KRYTERIUM STOPU ---
	}// zamknięcie cąłości powyżej w pętlę i sprawdzenie warunku bądź warunków - KONIEC PĘTLI

	cout << "PI0\n"; wysDane(PI0,zad,masz);
	cout << "PI\n"; wysDane(PI,zad,masz);
	cout << "PIprim\n"; wysDane(PIprim,zad,masz);
	int cMaxA = cMax(PIprim,masz,zad);
	cout << "cMax= " << cMaxA << endl;
	cout << "póki co działa" << endl; getchar();
	
delete PI0;
delete PI;
delete PIprim;
}

//-- F. main -------------------------------------------------------------------
int main()
{
  //  clock_t start, stop;
   // double czas;

  //  start = clock();

	int zad, masz, cmax;


    //-- Wczytywanie Dnych -----------------------------
	ifstream data("dane20.txt");
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
    wysDane(Dane,zad,masz);
	//-------------------------------------------------
	
	cmax = cMax( Dane, masz, zad );
	cout << "Cmax = " << cmax << endl; getchar();

	float u, nrIteracjiMax, T0, Tmax;	
	u=0.8;			// określić współczynnik schładzania
	T0 = 100;		// określić wartość początkowej temperatury
	Tmax = 10;
	nrIteracjiMax = 100000;
	symWyz(Dane, zad, masz, T0, u, nrIteracjiMax, Tmax );

}
