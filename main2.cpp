#include <iostream>
#include <time.h>
#include <unistd.h>
#include <cstdlib>	// potrzebne do system("clear");
#include <fstream>
#include <algorithm>
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
//algorytm NEH
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
			if (tmax >= cmax)
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

//----------------------------------------------------------------------------------------

//-- F. main -------------------------------------------------------------------
int main()
{
    clock_t start, stop;
    double czas;

    start = clock();

	int zad, masz, cmax;


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
    wysDane(Dane,zad,masz);

      	int **tab = kolejnosc(Dane, zad, masz);
	getchar();
	//wyswietlanie tablicy posortowanej
	cout << "===============TABLICA POSORTOWANA===============" << endl;
	for (int i = 0; i < zad; i++)
	{
		for (int j = 0; j < masz; j++)
		{
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}


	int ** ostateczna = Neh(tab, zad, masz);
	//wyswietlanie tablicy koncowej
	cout << "===============TABLICA OSTATECZNA===============" << endl;
	for (int i = 0; i < zad; i++)
	{
		for (int j = 0; j < masz; j++)
		{
			cout << ostateczna[i][j] << " ";
		}
		cout << endl;
	}

    cmax = cMax(ostateczna, masz, zad);
      cout << "cmax = " << cmax << endl;

stop = clock();
    czas = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Obliczanie zajmie: " << czas << endl;
}
