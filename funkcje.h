#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>




using namespace std; 

bool wczytaj(lista_info&dane_z_lista_info, ifstream & plik);//funkcja wczytuj¹ca plik tekstowy, zapisuj¹ca autorów i tytu³y oraz etykiety 

void sprawdz(lista_info&dane_z_lista_info, string etykieta, string autor, string tytul);//funkcja która sprawdza czy dana etykieta ju¿ znjaduje siê na liœcie etykiet

void pokazList(lista *listainfo, ofstream & plik_wyjsciowy);//funkcja zapisuj¹ca zawartoœæ listy i podlisty do pliku Ksiazki

void zwolnij(lista_info & listainfo);//funkcja która usuwa elementy list

void dodaj(string dane_do_dodania, lista_info &dane_z_lista_info, string autor, string tytul);//funkcja która dodaje kolejny element listy etykiet

void dodajpodliste(string autor, string tytul, lista *glowa);//funkcja która dodaje kolejny element podlisty

int zaladowanie_pliku(int argc, char **argv, ifstream & plik, ofstream & plik_wyjsciowy);

int porownaj(string etykieta, string etykieta2);

void help();
