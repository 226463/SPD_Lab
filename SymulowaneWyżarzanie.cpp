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

//= = = = = = = = = = = = = = =  D E K L A R A C J E   F U N K C J I = = = = = = = = = = = = = = =
void wysDane(int **Dane, int masz, int zad);													//1
int* TabSuma(int **Dane, int masz, int zad);													//2
int** NEH( int **Dane, int masz, int zad );														//3
int cMax( int **Dane, int masz, int zad );														//4
int **fnSwap(int **Dane, int zad, int masz );													//5
int **symWyz( int **Dane, int zad, int masz, float T0, float u, int nrIteracjiMax, int Tmax, int tMax, int ruch, int czyNeh );	//6
void czekaj( int iMilisekundy );                                                                //7
double obliczSekundy( clock_t czas );                                                           //8
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
				
//= = = = = = = = = = = = = = = = = = C I A Ł A   F U N K C J I = = = = = = = = = = = = = = = = = =
//-- Wyswietla dane z tablie z danymi -------------------------------------------------------------
void wysDane(int **Dane, int masz, int zad)												//FUNKCJA 1
{
    for ( int i = 0; i < masz; ++i, cout<<endl )
 		for ( int j = 0; j < zad; ++j)
 			cout<<Dane[i][j]<<'\t';
    getchar(); getchar();
    system("clear");

}
//--NEH--------------------------------------------------------------------------------------------
int* TabSuma(int **Dane, int masz, int zad) //Potrzebne funcji NEH 						//FUNKCJA 2
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
//---NEH-------------------------------------------------------------------------------------------
int** NEH( int **Dane, int masz, int zad )												//FUNKCJA 3
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
//---CMax------------------------------------------------------------------------------------------
int cMax( int **Dane, int masz, int zad )												//FUNKCJA 4
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
//--- Generowanie ruchu - swap - funkcja potrzebna do alg. Symulowanego Wyżarzania  --------------//FUNKCA_5
int **fnSwap(int **Dane, int zad, int masz )													
{
	srand( time( NULL ) );
	int a, b;
	a = (rand() %zad );
	if( a==zad ) b = a-1;
    else b = a+1;
	while( a == b ) b = (rand() %zad );

//	cout << a << "\t" << b << endl; getchar();
	for( int i = 0; i < masz; i++ )
		swap( Dane[a][i], Dane[b][i] );

	return Dane;
}
int **fnInsert(int **Dane, int zad, int masz )	
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
//--- algorytm Symulowanego Wyżarzania------------------------------------------------------------//FUNKCJA_6
int **symWyz( int **Dane, int zad, int masz, float T0, float u, int nrIteracjiMax, int Tmax, int tMax, int ruch, int czyNeh )	
{
    double czas1, czas2, czas;
    czas1 = obliczSekundy( clock() ); //Start czasu - pierwszy pomiar
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
    if( czyNeh == 1 ){
        cout << "\nTrwa Wyliczanie Cmax za pomocą algorytmu NEH..." << endl;
        PI0 = NEH(Dane, masz, zad); 
        int cmax = cMax(PI0,masz,zad);
        cout << "Cmax NEH = " << cmax << endl; getchar(); }
    else if( czyNeh ==0 ) PI = Dane;
    
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
	if( ruch == 1 ) PIprim = fnSwap(PIprim,zad,masz);
    else if( ruch == 2 ) PIprim = fnInsert(PIprim,zad,masz);
//= = =  K R Y T E R I U M   S T O P U = = = | | = = = P O C Z Ą T E K   P Ę T L I ===
//for( int nrIteracji = 0; i < nrIteracjiMax && T >= Tmax; nrIteracji ++ )	// Ograniczenie rozszerzone - ilość iteracji + maksymalna temperatura (minimalna)
//for( int nrIteracji = 0; i < nrIteracjiMax && T >= Tmax && /*czas<=czasmax*/; nrIteracji ++ )	// Ograniczenia maksymalne - jak wyzej + czas trwania symulacji - wymaga dopracowania
//for( int nrIteracji = 0; i < nrIteracjiMax; nrIteracji ++ )		// Ograniczenie podstawowe - tylko ilość iteracji
for( int nrIteracji = 0; nrIteracji < nrIteracjiMax && T >= Tmax && czas <= tMax; nrIteracji ++ ){
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
		//cout << "TAK" << endl;
	} 
//--- KROK - IV ---> SCHŁADZANIE ---
	//-- T <-- fc(T) --
//	cout << "T = " << T << "	u = " << u << endl;
	T = u * T;
//	cout << "T = " << T << endl;
	//T = T * ( k / kmax );	//alternatywna wersja - wymaga zdefiniowania k i kmax ( ograniczenia ze względu na ilość iteracji )
//--- KROK - V ---> KRYTERIUM STOPU ---
    czas2 = obliczSekundy( clock() ); //Stop czasu - drugi pomiar
    czas = czas2 - czas1;    // Obliczenie czasu trwania algorytmu
	}// zamknięcie cąłości powyżej w pętlę i sprawdzenie warunku bądź warunków - KONIEC PĘTLI

	//cout << "PI0\n"; wysDane(PI0,zad,masz);
	//cout << "PI\n"; wysDane(PI,zad,masz);
	//cout << "PIprim\n"; wysDane(PIprim,zad,masz);
	//int cMaxA = cMax(PI,masz,zad);
	//cout << "cMax Po Symulowanym Wyzarzaniu = " << cMaxA << endl;
	//cout << "póki co działa" << endl; getchar();
	return PI;
delete PI0;
delete PI;
delete PIprim;
}

void czekaj( int iMilisekundy )
{
    clock_t koniec = clock() + iMilisekundy * CLOCKS_PER_SEC / 1000.0;
    while( clock() < koniec ) continue;
    
}
double obliczSekundy( clock_t czas )
{
    return static_cast < double >( czas ) / CLOCKS_PER_SEC;
}
//-- F. main ---------------------------------------------------------------------------------------//FUNKCJA MAIN
int main()
{
  //  clock_t start, stop;
   // double czas;

  //  start = clock();

    double czas1, czas2, czas;
	int zad, masz, cmax, nrIteracjiMax, T0, Tmax, tMax, ruch, czyNeh;	
    string nazwaPliku;
    float u;
    getchar();
    system("clear");
    cout << "Podaj nazwę pliku z danymi ( nazwa.txt ) \n Dostępne pliki to:";
    cout << "dane000.txt \ndane10.txt \ndane20.txt \ndane30.txt \ndane38.txt \ndane40.txt";
    cout << "\ndane50.txt \ndane60.txt \ndane70.txt \ndane80.txt \ndne90.txt \ndane100.txt \ndane120.txt \n-->";
    cin >> nazwaPliku;
    system("clear");
    cout <<"Nazwa pliku: " << nazwaPliku << endl;
    cout << "Wybierz formę dokonywania ruchu: \nSwap wybierz 1 \nInsert wybierz 2 \n";
    cin >> ruch;
    system("clear");
    cout << "Czy wczytane dane poddać na początek algorytmowi NEH? \nTAK wybierz 1 \nNIE wybierz 2 \n";
    cin >> czyNeh;
    system("clear");
    cout << "Podaj wartości następujących parametrów: \nWspółczynnik wychładzania u: (np. 0.8 0.9 0.95) \n";
    cin >> u;
    cout << "Temperatura startowa T0: \n";
    cin >> T0;
    cout << "Temperatura maksymalna: \n";
    cin >> Tmax;
    cout << "Maksymalna ilość iteracji \n";
    cin >> nrIteracjiMax;
    cout << "Maksymalny czas trwania algorytmu tMax: \n";
    cin >> tMax;
    cout << "Wczytano dane: " << endl;
    cout << "Współcynnik wychłądzania u: " << u << "\nTemperatura startowa T0: " << T0 << "\nTempertura maksymalna Tmax: " << Tmax << "\nMaksymalna ilość iteracji: " << nrIteracjiMax << endl;
    cout << "Maksymalny czas trwania algorytmu tMax: " << tMax << endl; 
    if(ruch == 1) cout << "Forma Wyboru ruchu: Swap" << endl;
    else  if(ruch == 2) cout << "Forma Wyboru ruchu: Insert" << endl;
    cout << "\nAby rozpocząć naciśnij dowolny klawisz... \n"; getchar();
    //-- Wczytywanie Dnych -----------------------------
    //ifstream data("dane.txt");
    ifstream data(nazwaPliku);
     data >> zad >> masz;

	 cout << "masz="<<"  "<<masz<<" zad="<< zad <<endl;
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
    //wysDane(Dane,zad,masz);
	//-------------------------------------------------
	
	cmax = cMax( Dane, masz, zad );
	cout << "Cmax dla Wczytanych danych = " << cmax; getchar();

	
	u=0.8;			// określić współczynnik schładzania
	T0 = 100;		// określić wartość początkowej temperatury
	Tmax = 10;
	nrIteracjiMax = 100000;
    czas1 = obliczSekundy( clock() ); //Start czasu - pierwszy pomiar
	
    Dane = symWyz(Dane, zad, masz, T0, u, nrIteracjiMax, Tmax, tMax, ruch, czyNeh );
    
    czas2 = obliczSekundy( clock() ); //Stop czasu - drugi pomiar
    cmax = cMax( Dane, masz, zad );
    czas = czas2 - czas1;    // Obliczenie czasu trwania algorytmu
    system("clear");
    cout << "Badania wykonano dla pliku\n" << nazwaPliku << endl;
    if(ruch == 1) cout << "Forma Wyboru ruchu: Swap" << endl;
    else  if(ruch == 2) cout << "Forma Wyboru ruchu: Insert" << endl;
    cout << "Współcynnik wychłądzania u: " << u << "\nTemperatura startowa T0: " << T0 << "\nTempertura maksymalna Tmax: " << Tmax << "\nMaksymalna ilość iteracji: " << nrIteracjiMax << endl;
    cout << "Maksymalny czas trwania algorytmu tMax: " << tMax << endl;
	cout << "Cmax dla Symulowanego Wyżarzania = " << cmax << endl; getchar();
    cout << "Czas pracy algorytmu: " << czas << "[s]" << endl;
  
return 0;
}
