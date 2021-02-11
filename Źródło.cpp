#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>
#include "struktury.h"
#include "funkcje.h";


using namespace std;



int main(int argc, char **argv)
{
	ifstream plik; //tworzê obiekt do obs³ugi strumienia
	ofstream plik_wyjsciowy; //tworzê obiekt do obs³ugi strumienia
	int wynik;
	setlocale(LC_ALL, "polish");//ustawiam lokalizacje na polska
	lista_info moja_lista; // tworzê listê o nazwie moja lista 
	moja_lista.H = nullptr;//ustawiam wskaŸnik listy etykiet na nullptr
	moja_lista.T = nullptr;//ustawiam wskaŸnik listy etykiet na nullptr
	wynik = zaladowanie_pliku(argc, argv, plik, plik_wyjsciowy);//wywo³anie funkcji sprawdzaj¹cej poprawnoœæ plików wejscia, wyjœcia oraz argumentów. Liczba jak¹ zwróci ta funkcja zapisywana jest w zmiennej 
	if (wynik == 0) // je¿eli funkcja za³adowanie pliku zwróci wartoœæ 0 
	{
		cout <<endl<< "Nie udalo sie poprawnie zaladowac pliku" << endl;
		cout << "Program zostanie zamkniety" << endl;
		return 0;//Nastêpuje zamkniêcie programu 
	}
	if (wczytaj(moja_lista, plik) == true)	//sparwdzam czy uda³o siê poprawnie wczytaæ wszystkie linie z pliku wejœciowego
	{
		cout << "Udalo sie wczytac wszystkie ksiazki z pliku z ksiazkami " << endl;//Je¿eli tak, stosowny komunikat 
	}
	else if (wczytaj(moja_lista, plik) == false) // je¿eli nie uda³o by siê poprawnie wczytaæ to wyœwietlam nastêpuj¹ce kominukaty. 
	{
		cout << "Nie uda³o siê wczytaæ poprawnie ksi¹¿ki" << endl;
		cout << "Nastapi zakonczenie dzialania programu" << endl;
		return 0;//Nastêpuje zamkniêcie programu 
		
	}

	pokazList(moja_lista.H, plik_wyjsciowy); //funkcja zapisuj¹ca zawartoœæ listy i podlisty do pliku Ksiazki

	cout << "ilosc list : " << moja_lista.licznik << endl; // wypisujê iloœæ list etykiet powsta³ych w skutek pracy programu 

	zwolnij(moja_lista);//usuniêcie listy;

	system("pause");
}

