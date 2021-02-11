#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>


using namespace std; 

struct podlista {	//struktura podlisty danego elementu listy (etykiet)
	string autor;	//zmienna przechowuj¹ca nazwisko autora danej ksi¹¿ki która znajduje siê w podliœcie
	string tytul;  //zmienna przechowuj¹ca tytu³ danej ksi¹¿ki która znajduje siê w podliœcie
	podlista*podlista_nast;  //wskaŸnik na nastêpny element podlisty
	podlista*podlista_poprzedni; //wskaŸnik na poprzedni element podlisty

};
struct lista //struktura typu lista zawieraj¹ca etykiety
{
	string etykieta;	//zmienna przechowuj¹ca nazwê konkretnej etykiety	
	lista*lista_nast;  //wskaŸnik na nastêpny element listy etykiet
	lista*lista_poprzedni; //wskaŸnik na poprzedni element listy etykiet
	podlista *Head = nullptr; // wskaŸnik na g³owê podlisty 
	podlista *Tail = nullptr; //wskaŸnik na ogon podlisty 
};
struct lista_info //pomocnicza struktura 
{
	int licznik = 0; //licznik który posiada informacjê o tym czy istnieje ju¿ jakiœ element funkcji etykiet, jeœli nie to wartoœæ wynosi zero, jeœli istnieje to wartoœæ wiêksza od zera
	lista *H; // wskaŸnik na g³owê listy etykiet
	lista *T; //wskaŸnik na ogon listy etykiet

};
