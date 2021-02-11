#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>
#include "struktury.h"
#include "funkcje.h";


using namespace std;


int porownaj(string etykieta, string etykieta2)
{

	 // Funkcja, która porównuje napis bêd¹cy w liœcie z dopiero co wprowadzonym napisem

		int dlugosc = etykieta.length() + 1;// Sprawdzam d³ugoœæ napisu 
		char * tablica = new char[dlugosc]; // dynamicznie lokuje tyle pamiêci ile potrzeba do zapisania danego napisu (+1 poniewa¿ na koñcu string mamy zawsze NULL)
		//strcpy_s(tablica, dlugosc, etykieta.c_str()); // Funkcja, która przepisuje stringa (wprowadzone s³owo) do tablicy typu char o odpowiedniej d³ugoœci
		for (int i = 0; i < dlugosc; i++)
		{
			tablica[i] = etykieta[i];
			
		}

		int dlugosc1 = etykieta2.length() + 1; // Sprawdzam d³ugoœæ napisu 
		char * tablica1 = new char[dlugosc1]; //dynamicznie lokuje tyle pamiêci ile potrzeba do zapisania danego napisu (+1 poniewa¿ na koñcu string mamy zawsze NULL)
		//strcpy_s(tablica1, dlugosc1, etykieta2.c_str()); // Funkcja, która przepisuje stringa (aktualne s³owo) do tablicy typu char o odpowiedniej d³ugoœci
		for (int i = 0; i < dlugosc1; i++)
		{
			tablica1[i] = etykieta2[i];
			
		}

		// Funkcja, która porównuje wprowadzone s³owo z aktualnym s³owem w liscie, literka po literce, traktuje du¿e litery jako ma³e podczas porównywania
		if (_stricmp(tablica, tablica1) == 0) // Jeœli wprowadzone s³owo i aktualne s³owo w liscie s¹ identyczne
		{
			return 0;
		}
		else if (strcoll(tablica, tablica1) < 0) // Jeœli wprowadzone s³owo jest pierwsze w kolejnoœci alfabetycznej, a za nim aktualne s³owo w liscie
		{
			return 1;
		}
		else if (strcoll(tablica, tablica1) > 0) // Jeœli wprowadzone s³owo jest nastepne w kolejnoœci alfabetycznej, a pierwsze jest aktualne s³owo w liscie
		{
			return 2;
		}


		delete[] tablica; // Usuwam zalokowan¹ pamiêæ aby nie odprowadziæ do wycieku pamiêci 
		delete[] tablica1;
	
}

void dodaj(string etykieta, lista_info &dane_z_lista_info, string autor, string tytul)
{
	if (dane_z_lista_info.licznik == 0)//sprawdzam czy istnieje ju¿ jakiœ element w liœcie 
	{
		dane_z_lista_info.licznik++;//zwiêkszam licznik który mówi ile posiadam elementów listy 
		lista *pom = new lista;//tworzê nowy wskaŸnik pomocniczy i przypisujê mu nowy element listy (nowy obszar pamiêci)
		pom->etykieta = etykieta;//jako nazwa etykiety w tym elemnecie listy zapisujê string etykieta którego dostajê po wczytaniu danej linijki pliku txt 
		pom->lista_nast = nullptr;//ustawiam wartoœæ wskaŸnika na nastêpny element listy etykiet jako nullptr, poniewa¿ moja lista dodaje nowe elementy na koñcu 
		pom->lista_poprzedni = nullptr;//z racji tego ¿e jest to pierwszy element listy wartoœæ wskaŸnika na poprzedni ustawiam jako nullprt, w lisæie mam teraz tylko jeden element w³aœnie ten, który teraz jest tworzony
		dane_z_lista_info.H = pom;//wskaŸnik na g³owê listy etykiet ustawiam na adres jaki aktualnie przyjmuje pom czyli na mój nowy element listy 
		dane_z_lista_info.T = pom;//wskaŸnik na ogon listy etykiet równie¿ ustawiam na adres pom czyli na adres nowego elementu dlatego ¿e mam aktualnie listê z jednym elementem
		dodajpodliste(autor, tytul, pom); //wywo³ujê funkcje która dodaje podlistê zawieraj¹ca autora i tytu³ danej ksia¿ki do której nale¿y wczeœniej utworzona etykieta
	}
	else//je¿eli istnieje jakiœ element w liœcie czyli licznik jest wiêkszy od zera to tworzymy po prostu kolejny element listy etykiet
	{
		dane_z_lista_info.licznik++;//zwiêkszam licznik iloœci elementów w liœcie etykiet
		lista *pom = new lista;//tworzê nowy wskaŸnik pomocniczy u przypisujê mu nowy element listy (nowy obszar pamiêci)
		pom->etykieta = etykieta; // jako nazwa etykiety w tym elemnecie listy zapisujê stringa etykieta którego "dostajê" po wczytaniu danej linijki pliku txt
		pom->lista_nast = nullptr;;//ustawiam wartoœæ wskaŸnika na nastêpny element listy etykiet jako nullptr, poniewa¿ moja lista dodaje nowe elementy na koñcu 
		pom->lista_poprzedni = dane_z_lista_info.T;//ustawiam wskaŸnik na poprzedni elemnt na to co pokazuje aktualnie wska¿nik ogon listy 
		dane_z_lista_info.T->lista_nast = pom;//
		dane_z_lista_info.T = pom;//ustawiam wskaŸnik ogon listy na element który w³aœnie powsta³ o adresie takim jak pokazuje wskaŸnik pom
		dodajpodliste(autor, tytul, pom);
	}
}

void sprawdz(lista_info&dane_z_lista_info, string etykieta, string autor, string tytul)//funkcja która sprawdza czy dana etykieta ju¿ znjaduje siê na liœcie etykiet
{
	lista *pom = dane_z_lista_info.H;//tworze wskaŸnik pomocniczy 
	bool nie_ma;//tworzê flagê 
	nie_ma = true;//ustawiam flagê na wartoœæ true
	while (pom != nullptr)
	{
		if (porownaj(etykieta, pom->etykieta)==0/*pom->etykieta==etykieta*/)//jezeli etykieta któr¹ chce dodaæ do listy jest jaka sama jak ju¿ istniej¹cy element listy to dodaje tylko podliste z autorem i tytu³em
		{
			dodajpodliste(autor, tytul, pom);//wywyo³anie funkcji która dodaje do podlisty autora i tytu³ 
			nie_ma = false;//jeœli ta pêtla siê wykona czyli etykieta któr¹ chce dodaæ jest taka sama jak juz istniej¹ca to tylko dodaje el podlisty 
		}
		pom = pom->lista_nast;//ustawiam wskaŸnik na nastêpnym element w liœcie etykiet
	}
	if (nie_ma)//je¿eli wczeœniejszy "if" nie zadzia³a³ to znaczy ze flaga nie jest podniesiona czyli w aktulanej liscie etykiet nie ma takiej samej etykiety jak¹ chcê dodaæ
	{
		dodaj(etykieta, dane_z_lista_info, autor, tytul);//wywyo³anie funkcji, która dodaje nowy elemnt listy etykiet
	}

}
void dodajpodliste(string autor, string tytul, lista *glowa)//fukncja dodaj¹ca kolejny element podlisty
{
	if (glowa->Head == nullptr)//jezeli wskaznik na glowe podlisty elementu z listy etykiet jest nullptr to znaczy ze go nie ma to tworze zupelnie nowa podliste dal tego el.
	{
		glowa->Head = new podlista;//tworzê nowy element podlisty i przypisuje mu wskaŸnik g³owy poniewa¿ to pierwszy element
		glowa->Head->autor = autor;//w miejscu autora wpisujê pobranego autora 
		glowa->Head->tytul = tytul;//w miejscu tytu³u wpisujê pobrany tytu³
		glowa->Head->podlista_nast = nullptr;//wskaŸnik na nastepny element ustawiam jako nullprt, poniewa¿ w podliœcie mam tylko jeden element
		glowa->Head->podlista_poprzedni = nullptr;//wskaŸnik na poprzedni element usatwiam równie¿ na nullptr
		glowa->Tail = glowa->Head;//ustawiam wskaŸnik ogona podlisty na to samo co g³owa poniewa¿ mam tylko jeden element 
	}
	else//je¿eli podlista posiada jeden element lub wiêcej
	{
		podlista *pom; //tworzê wskaŸnik pomocniczy
		pom = glowa->Head; //ustawiam ten wskaŸnik na g³owê
		int ile = 0; //tworzê zmienn¹ pomocnicz¹
		bool nie_jest; //tworzê now¹ flagê 
		nie_jest = false; //ustawiam wartoœæ flagi na true
		while (glowa->Head != nullptr) //je¿eli wskaŸnik na g³owê nie bêdzie wskazywaæ na nullprt
		{
			int i = (porownaj(autor, pom->autor));
			switch (i)
			{
			case 1:
			{
				if (ile == 0) //je¿eli jest to pierwsze wywo³anie pêtli to znaczy ¿e dodaje nowy element przed tym na który aktualnie wksazuje g³owa
				{
					pom->podlista_poprzedni = new podlista; //dodaje now¹ podlistê przed elementem na który wskazuje g³owa
					pom->podlista_poprzedni->podlista_nast = glowa->Head;//nasz nowy element który jest teraz pierwszy w podliscie wsksazuje na ten element który wczesniej by³ pierwszy czyli na to co wskazuje g³owa
					glowa->Head = pom->podlista_poprzedni;//teraz g³owa wskazuje na element który w³asnie dodajemy
					glowa->Head->autor = autor; //uzupe³niam zawartoœæ podlisty
					glowa->Head->tytul = tytul; //uzupe³niam zawartoœæ podlisty
					glowa->Head->podlista_poprzedni = nullptr; //wskaŸnik na poprzedni wskazuje na nullprt poniewa¿ jest to teraz pierwszy element podlisty
					nie_jest = true;
				}
				else //je¿eli nie jest to pierwsze wywo³anie czyli dodajemy element pomiêdzy dwa inne 
				{
					pom->podlista_poprzedni->podlista_nast = new podlista; //dodaje nowy element podlisty
					pom->podlista_poprzedni->podlista_nast->podlista_nast = pom; //poprzedni element wskazuje teraz na nowy obszar który przed chwil¹ stworzyliœmy
					pom->podlista_poprzedni->podlista_nast->podlista_poprzedni = pom->podlista_poprzedni; //nowy element wskazuje teraz na poprzedni w podliscie
					pom->podlista_poprzedni = pom->podlista_poprzedni->podlista_nast; //element który jest po nowym elemencie wskazuje teraz na niego 
					pom->podlista_poprzedni->autor = autor; //uzupe³niam wartoœæ podlisty
					pom->podlista_poprzedni->tytul = tytul; //uzupe³niam wartoœæ podlisty
					nie_jest = true;
				}
				break;
			}
			case 2:
			{
				
				if (pom==glowa->Tail)//je¿eli pokazujemy na ostatni element a to co chcemy dodac dalej jest alfabetycznie poŸniej to dodajemy ten element jako ostatni, za ogon
				{
					glowa->Tail->podlista_nast = new podlista; //ogon pokazuje teraz na nowo utworzony element 
					glowa->Tail->podlista_nast->podlista_poprzedni = glowa->Tail; // ustawiam wskaŸnik nowego elementu na element poprzedni
					glowa->Tail = glowa->Tail->podlista_nast; // przypisuje wskaŸnik ogona do nowego elementu
					glowa->Tail->autor = autor; //wype³niam wartoœæ podlisty 
					glowa->Tail->tytul = tytul; //wype³niam wartoœæ podlisty 
					glowa->Tail->podlista_nast = nullptr; // ustwiam wartoœæ wskaŸnika na nastêpny element jako nullprt 
					nie_jest = true;
				}
				else {
					pom = pom->podlista_nast;
				}
				break;
			}
			case 0: //jeœli dwie ksazki s¹ takie same to dodaje jedna za drug¹ 
			{
				if (ile == 0) //je¿eli jest to pierwsze wywo³anie pêtli to znaczy ¿e dodaje nowy element przed tym na który aktualnie wksazuje g³owa
				{
					pom->podlista_poprzedni = new podlista; //dodaje now¹ podlistê przed elementem na który wskazuje g³owa
					pom->podlista_poprzedni->podlista_nast = glowa->Head;//nasz nowy element który jest teraz pierwszy w podliscie wsksazuje na ten element który wczesniej by³ pierwszy czyli na to co wskazuje g³owa
					glowa->Head = pom->podlista_poprzedni;//teraz g³owa wskazuje na element który w³asnie dodajemy
					glowa->Head->autor = autor; //uzupe³niam zawartoœæ podlisty
					glowa->Head->tytul = tytul; //uzupe³niam zawartoœæ podlisty
					glowa->Head->podlista_poprzedni = nullptr; //wskaŸnik na poprzedni wskazuje na nullprt poniewa¿ jest to teraz pierwszy element podlisty
					nie_jest = true;
				}
				else
				{
					pom->podlista_poprzedni->podlista_nast = new podlista; //dodaje nowy element podlisty
					pom->podlista_poprzedni->podlista_nast->podlista_nast = pom; //poprzedni element wskazuje teraz na nowy obszar który przed chwil¹ stworzyliœmy
					pom->podlista_poprzedni->podlista_nast->podlista_poprzedni = pom->podlista_poprzedni; //nowy element wskazuje teraz na poprzedni w podliscie
					pom->podlista_poprzedni = pom->podlista_poprzedni->podlista_nast; //element który jest po nowym elemencie wskazuje teraz na niego 
					pom->podlista_poprzedni->autor = autor; //uzupe³niam wartoœæ podlisty
					pom->podlista_poprzedni->tytul = tytul; //uzupe³niam wartoœæ podlisty
					nie_jest = true;
				}
				break;
			}

			
			
			}
			ile++;
			if (nie_jest)//jezeli przejrza³em ca³¹ podlistê i ¿aden autor nie by³ alfabetycznie wczeœniej to dodaj ksiazke jako ostatni element podlisty 
			{
				break;
			}
		}
	}
}
bool wczytaj(lista_info &dane_z_lista_info, ifstream & plik)  //lista &lista, podlista &dane_z_podlisty funkcja wczytuj¹ca zawartosc pliku tekstowego linijka po linijce 
{
	//plik.open("Text.txt"); //otwieram plik o nazwie Text.txt
	string linia; //tworzê zmienn¹ pomocnicz¹ która bêdzie przechowywa³a linijkê wczytan¹ z pliku 

	
		plik.seekg(0, ios::beg); // wstawienie wskaŸnika na pocz¹tek pliku

		do
		{
			int licznik = 0; //tworzê zmienn¹ pomocnicz¹ 
			int ilosc = 0;
			string autor; //tworzê zmienn¹ pomocnicz¹ przechowuj¹c¹ autora
			string tytul; //tworzê zmienn¹ pomocnicz¹ przechowuj¹c¹ tytu³
			string etykieta; //tworzê zmienn¹ pomocnicz¹ przechowuj¹c¹ etykiete
			string reszta;//tworze pomocniczego stringa w którym zapiszê etykietê bez dodatkowych spacji 
			string cos;
			
			getline(plik, linia); // pobieram z pliku ca³¹ linijkê
			int dlugosc = linia.length(); // tworzê zmienn¹ przechowuj¹c¹ d³ugosæ pobranej linii tekstu 
			for (int r = 0; r < dlugosc; r++)//w tej petli sprawdzam ile jest sredników w ca³ej linijce 
			{
				if (linia[r] == ';')//jesli jest ich mniej niz 2 onazacz ze uzytkownik blednie wpisa³ ksiazke, program zignoruje ta linijkê i wykona pêtle do nastêpnej linijki
				{
					ilosc++;
				}
			}
			if (ilosc < 2)
			{
				continue;
			}
			int i = 0; // zmienna pomocnicza 
			if (dlugosc < 5)// Je¿eli linijka kodu bedzie mniejsza b¹dŸ równa 5 to znaczy ¿e u¿ytkownik wpisa³ niepoprawnie dane i pomijam wtedy t¹ linijkê
			{
				continue;
			}
			while (linia[i] != ';')//czytam autora i zaposuje go 
			{
				if (linia[i] == '/' || linia[i] == '.' || linia[i] == ',' || linia[i] == '(' || linia[i] == ')' || linia[i] == '!' || linia[i] == '@' || linia[i] == '#' || linia[i] == '$'
					|| linia[i] == '%' || linia[i] == '^' || linia[i] == '&' || linia[i] == '*' || linia[i] == '-' || linia[i] == '+' || linia[i] == '=' || linia[i] == '[' || linia[i] == ']'
					|| linia[i] == '{' || linia[i] == '}' || linia[i] == '"' || linia[i] == '<' || linia[i] == '>' || linia[i] == '~' || linia[i] == '`' || linia[i] == '|' || linia[i] =='_'
					||linia[i]=='\t')//usuawm przypadkowe b³edy u¿ytkownika ignoruj¹c niekótre znaki 
					i++;
				else if ((linia[i] == ' ') && (linia[(i + 1)] == ' '))// usuwam ci¹g przecinków zamieniaj¹c go w jeden przecinek
				{
					i++;
				}
				else {
					autor = autor + linia[i]; // sklejam autora 
					i++; // zwiêkszam zmienn¹ która mówi na jakim miejscu w linii jestem
				}

			}
			int m = autor.length();
			if (m == 0)// jezelu uzytkownik nie poda³ autora przechodze do nastepnej linikjki ignoruj¹c dalsz¹ czêœæ aktualnej 
			{
				continue;
			}
			
			i++; // zwiêkszam zmienn¹ aby wskaŸnik przesun¹³ siê z ';' na kolejny znak 
			while (linia[i] != ';')//czytam linie i ja zapisuje
			{
				if (linia[i] == '/' || linia[i] == '.' || linia[i] == ',' || linia[i] == '(' || linia[i] == ')' || linia[i] == '!' || linia[i] == '@' || linia[i] == '#' || linia[i] == '$'
					|| linia[i] == '%' || linia[i] == '^' || linia[i] == '&' || linia[i] == '*' || linia[i] == '-' || linia[i] == '+' || linia[i] == '=' || linia[i] == '[' || linia[i] == ']'
					|| linia[i] == '{' || linia[i] == '}' || linia[i] == '"' || linia[i] == '<' || linia[i] == '>' || linia[i] == '~' || linia[i] == '`' || linia[i] == '|' || linia[i] == '_' || linia[i] == '\t')//usuawm przypadkowe b³edy u¿ytkownika ignoruj¹c niekótre znaki 
					i++;
				else
				{
					tytul = tytul + linia[i]; //sklejam tytu³
					i++; // zwiêkszam zmienn¹ która mówi na jakim miejscu w linii jestem
				}
			}

			
			int q = i;
		
			while (q < dlugosc)// wykonuje pêtle sprawdzaj¹c¹ i usuwaj¹c¹ nadmiaj przecinków 
			{
				if (linia[q] == '/' || linia[q] == '.'  || linia[q] == '(' || linia[q] == ')' || linia[q] == '!' || linia[q] == '@' || linia[q] == '#' || linia[q] == '$'
					|| linia[q] == '%' || linia[q] == '^' || linia[q] == '&' || linia[q] == '*' || linia[q] == '-' || linia[q] == '+' || linia[q] == '=' || linia[q] == '[' || linia[q] == ']'
					|| linia[q] == '{' || linia[q] == '}' || linia[q] == '"' || linia[q] == '<' || linia[q] == '>' || linia[q] == '~' || linia[q] == '`' || linia[q] == '|' || linia[q] == '_'
					|| linia[q] == ' ' ||linia[q] == '\t')
				{
					q++;
				}
				else if ((linia[q] == ',') && (linia[(q + 1)] == ','))// usuwam ci¹g przecinków zamieniaj¹c go w jeden przecinek
				{
					q++;
				}
				else//dodaje kolejne litery do stringów 
				{
					reszta= reszta + linia[q]; // tworze stringa reszta w którym bêde mia³ wszystkie etykiety sklaejone jednym stringiem 
					q++;
				}

			}
			int j = reszta.length();//sprawdzam dlugosc stringa reszta czyli stringa w którym mam zapisane wszystkie etykiety 
		
			
			for (int m=0; m <j; m++)			//petla sprawdzajaca ile w linijce jest przecinkow, jesli znajdzie jakis to zwieksza wartosc licznika
			{
				
				if (reszta[m] == ',') // czytam linijkê do koñca i jeli napotkam przecinek to zwiêkszam licznik
				{					
						licznik++;//ilosc tych przecinkow, ilosc etykiet jest o jeden wieksza niz ilosc przecinkow
					
				}
			}

			int g = 0;
			for (int k = 0; k < (licznik + 1); k++) // pêtla która skleja etykiety w linijce 
			{
				
				g++;
				while ((reszta[g] != ',') && (g < j)) {

					etykieta = etykieta + reszta[g]; // sklejam etykietê 
					g++;


				}
				int e = etykieta.length();
				if (e < 2) {
					continue;
				}
				

				
					sprawdz(dane_z_lista_info, etykieta, autor, tytul); // wywo³ujê funkcjê która najpierw sprawdza czy etykieta któr¹ chcê dodaæ ju¿ istnieje w liœcie etykiet
					// jeœli nie istnieje to dodaje nowy element listy etykiet a do tego elementu tworzê podlistê z autorem i tytu³em 
					etykieta = ""; // czyszczê zawartoœæ etykiety aby by³o mo¿liwe wczytanie kolejnej 
					
					cos = "";
				
			}
		} while (!plik.eof()); // powtarzam dopóki nie natrafiê na koniec pliku 

		plik.close(); // zamykam plik 
		return true;
	

}
void help() // funkcja która wyœwietla komunikat w przypadku b³ednego wprowadzenia argumentów
{
	cout << endl<< "=================================================" << endl;
	cout << "======================POMOC=====================" << endl;
	cout << "Argumenty wprowadzono w sposob nieprawidlowy" << endl;
	cout << " -i  argument wejscia Text.txt" << endl;
	cout << "-o argument wyjscia Etykiety.txt" << endl;
	cout << "Proszê spróbowaæ ponownie z argumentami jak wy¿ej" << endl;
	cout << "=================================================" << endl;

}
void pokazList(lista * listainfo, ofstream & plik_wyjsciowy) // funkcja zapisuj¹ca zawartoœæ listy i podlisty do pliku Ksiazki
{
	
	lista *kolejny;	//wskaznik o nazwie kolejny
	podlista *pom;
	kolejny = listainfo;
	
	while (kolejny != nullptr)
	{
		plik_wyjsciowy << endl;
		plik_wyjsciowy << "etykieta to " << kolejny->etykieta << endl;

		while (kolejny->Head != nullptr)
		{
			plik_wyjsciowy << " autor : " << kolejny->Head->autor << " tytul : " << kolejny->Head->tytul << endl;
			kolejny->Head = kolejny->Head->podlista_nast;
			plik_wyjsciowy << '\t';
		}
		kolejny = kolejny->lista_nast;
		plik_wyjsciowy << endl << endl;
	}
	plik_wyjsciowy << "\n";
}
void zwolnij(lista_info & listainfo) // funkcja która zwalnia pamiêæ po wykonaniu programu 
{
	lista *pom; // tworzê wskaŸnik pomocniczy 
	podlista * wsk; // wskaŸnik pomocniczy 
	while (listainfo.H != nullptr) //dopóki wska¿nik g³owy listy nie wskazuje na nullprt 
	{
		pom = listainfo.H; // wskaŸnik pomocniczy wskazuje na g³owê 
	
		while (listainfo.H->Tail!=nullptr) // dopóki wskaŸnik ogona podlisty danego elementy nie jest równy nullprt usuwam elementy podlisty od koñca 
		{
			wsk = listainfo.H->Tail; // wskaŸnik pokazuje teraz na to co ogon podlisty 
			listainfo.H->Tail = listainfo.H->Tail->podlista_poprzedni;// ogon pokazuje na poprzedni element podlisty 
			delete wsk; // usuwam wskaŸnik 
		}
		listainfo.H = listainfo.H->lista_nast; // g³owa listy pokazuje teraz na nastêpny element listy 
		delete pom; // usuwam wskaŸnik 
	}
}

int zaladowanie_pliku(int argc, char** argv, ifstream & plik, ofstream & plik_wyjsciowy) { // Funkcja , która za³adowuje pliki do programu
	// "-i" dotyczy pliku wejsciowego
	// "-o" dotyczy pliku wyjsciowego

	bool poprawnie = false;
	int zmienna1 = 1; // Zmienna pomocnicza 
	int zmienna2 = 1;
	for (int i = 1; i < argc; i++)
	{
		if (argc > 1 && argv[i] == (string) "-i")
			zmienna1 = i;
		if (argc > 1 && argv[i] == (string) "-o")
			zmienna2 = i;
	}
	if (argc > 1 && argv[zmienna1] == (string) "-i") 
	{  // Je¿eli iloœæ argumentów jest wiêksza od jedynki i jednoczesnie drugi argument to "-i"
		if ((!argv[zmienna1 + 1])|| !argv[zmienna2 + 1]) { // Je¿eli nie zosta³a okreœlona scie¿ka drugiego argumentu
			cout << "Nie okreœlono scie¿ki wejœciowej" << endl; // Je¿eli otwarcie pliku siê nie powiod³o
			help(); // Funkcja, wyœwietlaj¹ca pomocne informacje w przypadku nie poprawnego wprowadzenia argumentów podczas uruchamiania programu
			return 0;
		}
		else { // Je¿eli zosta³a okreœlona scie¿ka drugiego argumentu
			plik.open(argv[zmienna1 + 1]); // Skojarzenie obiektu plik_wejsciowy z scie¿k¹ "-i"
			if (plik.is_open() == 1) // Sprawdzenie czy plik do odczytu zosta³ otwarty poprawnie
			{ 
				cout << "Plik wejsciowy zosta³ otworzony prawid³owo" << endl; // Je¿eli otwarcie pliku siê nie powiod³o
				plik.seekg(0, ios::end);
				if(plik.tellg())
				{
					
					if (argc > 1 && argv[zmienna2] == (string) "-o") // Je¿eli iloœæ argumentów jest wiêksza od jedynki i jednoczesnie trzeci argument to "-o"
					{


						if (!argv[zmienna2 + 1] || argv[zmienna2 + 1] == (string)"-i") // Je¿eli nie zosta³a okreœlona scie¿ka czwartego argumentu
						{
							cout << "Nie okreœlono œcie¿ki wyjœciowej" << endl; //Je¿eli otwarcie pliku siê nie powiod³o
							help(); // Funkcja, wyœwietlaj¹ca pomocne informacje w przypadku nie poprawnego wprowadzenia argumentów podczas uruchamiania programu
							return 0;
						}
						else
							plik_wyjsciowy.open(argv[zmienna2 + 1]); // Skojarzenie obiektu plik_wyjsciowy z scie¿k¹ "-o"
						if (plik_wyjsciowy.is_open() == 1) // Sprawdzenie czy plik do zapisu zosta³ otwarty poprawnie
						{
							cout << "Plik wyjœciowy zosta³ utworzony prawid³owo" << endl; // Je¿eli otwarcie pliku siê nie powiod³o
							return 1;
						}
						else
						{
							cout << "Nie uda³o siê otworzyæ pliku wyjœciowego z podanej œcie¿ki" << endl;  // Je¿eli otwarcie pliku siê nie powiod³o 
							help(); // Funkcja, wyœwietlaj¹ca pomocne informacje w przypadku nie poprawnego wprowadzenia argumentów podczas uruchamiania programu
							return 0;
						}
					}
					else
					{  // Je¿eli nie zosta³a okreœlona scie¿ka trzeciego argumentu
						cout << "Nie okreœlono œcie¿ki wyjœciowej" << endl;  // Odpowiedni komunikat
						help(); // Funkcja, wyœwietlaj¹ca pomocne informacje w przypadku nie poprawnego wprowadzenia argumentów podczas uruchamiania programu
						return 0;
					}
				}
				else
				{
					cout << "Plik wejsciowy jest pusty" << endl;
					help();
					return 0;
				}
			}
			else 
			{
				cout << endl<< "Nie uda³o siê otworzyæ pliku wejœciowego z podanej œcie¿ki" << endl;  // Je¿eli otwarcie pliku siê nie powiod³o 
				help(); // Funkcja, wyœwietlaj¹ca pomocne informacje w przypadku nie poprawnego wprowadzenia argumentów podczas uruchamiania programu
				return 0;
			}
		}
	}
	
	else
	{
		help(); // Funkcja, wyœwietlaj¹ca pomocne informacje w przypadku  b³êdnego wprowadzenia argumentów podczas uruchamiania programu
		return 0;
	}
};

