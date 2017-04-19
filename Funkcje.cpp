
#include "stdafx.h"
#include "Funkcje.h"

using namespace std;

/*=================================================================================*/
void rozmiar_okna() // definiuje rozmiar okna konsoli
{
	HANDLE okno = GetStdHandle(STD_INPUT_HANDLE);

	COORD size;

  	size.X = 80;
	size.Y = 25;

	SetConsoleScreenBufferSize(okno, size);
}
/*=================================================================================*/

void polskie_litery() // umo¿liwia pisanie nazw funkcji itp po polsku 
{
	locale locpl("Polish_Poland");	
	locale::global(locpl);			
	cout.imbue(locpl);				
	cin.imbue(locpl);				
}

/*=================================================================================*/

void gotoxy(int x, int y) // kireuje kursor na porz¹deane wspó³rzêdne x oraz y 
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/*=================================================================================*/

void HideCursor() // sprawia ¿e obok figury lub te¿ tekstu nie mruga poziomy kursor
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

/*=================================================================================*/

void PoczatkowyRozmiar(int & bok, int & bok1) // funkcja wyboru pocz¹tkowego rozmiaru poprzez dobór odpowiednich wartoœæi 
											  // bok i bok1 odpowiedzoanych za rysowanie trzonu strza³ki oraz daszka strza³ki
{
	int Wybor;

	do
	{

		cout << "\nPodaj wymiar pocz¹tkowy figury, od 1 do 3: ";
		cin >> Wybor;
		cin.clear();
		cin.sync();

	} while (Wybor < 1 || Wybor > 3);

			switch (Wybor)
			{
			case 1: { bok = 3; bok1 = 3; break; }
			case 2: { bok = 5; bok1 = 6; break; }
			case 3: { bok = 7; bok1 = 9; break; }
			}

			HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(color, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	
}


/*=================================================================================*/

void Czyszczenie() // Funkcja czyœci ekran pomiêdzy
{

	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(hStdout, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;
	if (!FillConsoleOutputAttribute(hStdout, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;
	SetConsoleCursorPosition(hStdout, coordScreen);
}

/*=================================================================================*/

void Naglowek() // nic dodaæ nic uj¹æ, wypisuje nag³ówek
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << "================================================================================\n";
	SetConsoleTextAttribute(color, FOREGROUND_GREEN);

	cout << "\t\t\t  Grzegorz Staniewicz 167938\n";
	cout << "\t\t\t\tZadanie nr 62\n";
	cout << "\tNapisz program rysowania za pomoc¹ znaku ASCII poni¿szej figury.\n \tProgram powinien umo¿liwiæ\n";
	cout << "\tWybór znaku kodu ASCII\n";
	cout << "\tWczytanie pocz¹tkowych rozmiarów figury\n";
	cout << "\tPrzesuwanie figury klawiszami strza³ek\n";
	cout << "\tPowiêkszanie oraz mniejszanie figury za pomoc¹ znakó + i -\n";
	cout << "\tOgraniczanie przesuwania i rozmiarów figury do obszaru ekranun\n";
	cout << "\tFigur¹ jest strza³ka sierowana w dó³\n\n";
	SetConsoleTextAttribute(color, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << "================================================================================\n\n";
	SetConsoleTextAttribute(color, BACKGROUND_RED | BACKGROUND_GREEN |FOREGROUND_BLUE);

	cout << "Naciœnij dowolny klawisz";

}



/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/



void RysFunk() //Funkcja najwa¿niejsza, odpowiedzialna za rysowanie, powiêkszanie i przesówanie figóry
 {
	Czyszczenie();

//-----------------------------------------------------------------------------------

	const int Esq = 27;
	int x, y, x1, y1, y3, xPrawy, xLewy, bok, bok1, d³ugoœæ_prawa, d³ugoœæ_lewa;


			/*
			Legenda danych:
			x, y, x1, y1, y3: Zmienne wspó³rzêdnych x oraz y, w kilku wersjach aby móc w pewnych momentach programu wracaæ do jakichœ, 
			wczeœniejszych wartoœci.

			xPrawy, xLewy: Wykorzystywane do rysowania podstawy grotu.

			bok, bok1 : bok to d³ugoœæ boku trzonu strza³ki a bok1 d³ugoœæ boku grotu (daszka) strza³ki.

			d³ugoœæ_prawa, d³ugoœæ_lewa : To zmienne wykorzystywane przy ogarniczaniu przesuwania strza³ki horyzontalnie 

			znak: Znak kodu ASCI, w tej zmiennej przechowujemy czym ma byæ rysowana figura.
			przysk: To przysik + - oraz strza³ki - do maniupulowania figór¹
			*/


	char przycisk;
	char znak;

	x = 33;
	y = 4;
	

//-----------------------------------------------------------------------------------


				cout << "==========================================================\n";
				cout << "Podaj jakim znakiem z klawiatury figura ma byæ narysowana: ";
				cin >> znak; cout << "\n";
				cin.sync();

	


//-----------------------------------------------------------------------------------

PoczatkowyRozmiar(bok, bok1); //####################################################

//-----------------------------------------------------------------------------------

// Tu mamy zestaw pêtli rysuj¹cych nasz¹ figurê
	do
	{

				// Definicje zmiennych koniecznych do utrzymania figury w polu na osi x przy ró¿nych jej rozmiarach 
				d³ugoœæ_lewa = 0;
				d³ugoœæ_prawa = -1;

				if (bok <= 3)
					d³ugoœæ_prawa = -3;
				if (bok >= 7)
					d³ugoœæ_prawa = 1;
				if (bok >= 9)
					d³ugoœæ_prawa = 2;
//-----------------------------------------------------------------------------------

				Czyszczenie();

		x1 = x; 
		y1 = y;

		gotoxy(x1, y1);
//------------
		for (int i = 1; i <= bok; i++)      // Rysowanie górnej krawêdzi trzonu strz¹³ki 
		{
			cout << znak << " ";
			d³ugoœæ_prawa++;
			d³ugoœæ_prawa++;
		}
//------------
		for (int i = 1; i <= bok - 1; i++)    // Rysowanie boków trzonu strza³ki
		{
			y1++;
			gotoxy(x1, y1);
			cout << znak;
			x1 = x + 2 * bok - 2;
			gotoxy(x1, y1);
			cout << znak;
			x1 = x;
		}
//------------	

		y1++; // Obni¿enie wartoœci y-owej aby zacz¹æ rysowanie grotu strza³ki

//------------
		for (int i = 1; i < bok - 1 ; i++)   // Pionowa podstawa grotu z lewej strony
		{
			x1--;					
			x1--;
			gotoxy(x1, y1);					
			cout << znak << " ";
			xLewy = x1;
			d³ugoœæ_lewa++;
			d³ugoœæ_lewa++;


			/*Funkcja rysuje tê prost¹ poruszaj¹c siê w lewo,
			od defaultowej sta³ej jak¹ jest x, czyli od miejca w którym zakoñczono rysowanie
			trzonu strza³ki*/
		}
//------------

		x1 = x + 2 * bok - 2; // Przesuniêcie kursora rysuj¹cego pionow¹ podstawê grotu na prawo 

//------------
		for (int i = 1; i < bok - 1; i++)   // Pionowa podstawa grotu z prawej strony
		{
			x1++;
			x1++;
			gotoxy(x1, y1);
			cout << znak << " ";
			xPrawy = x1;
			d³ugoœæ_prawa++;

			/*Funkcja rysuje tê prost¹ poruszaj¹c siê w prawo,
			od defaultowej sta³ej jak¹ jest x, czyli od miejca w którym zakoñczono rysowanie
			trzonu strza³ki*/
		}
//------------

		y3 = y1; // Y1 to wspó³¿êdna lewego boku ostrego zakoñczenia strza³ki a nowa, Y3 - prawego 

//------------
		for (int i = 1; i < bok1; i++)    // Lewy bok ostrego zakoñczenia
		{
			y1++;
			gotoxy(xLewy + 1, y1);
			cout << znak;
			xLewy++;
			xLewy++;
		}

//------------		 
		for (int i = 1; i < bok1; i++)    // Prawy bok ostrego zakoñczenia
		{
			y3++;
			gotoxy(xPrawy - 1, y3);
			cout << znak;
			xPrawy--;
			xPrawy--;
		}


		


//-----------------------------------------------------------------------------------
// Tutaj odbywa siê operacja powiêkszania i pomniejszania figury
		
			przycisk = _getch();
			
			{
				switch (przycisk) 
				{
				case '+': { bok = bok + 2;   // Powiekszenie figury
					x--; y--; bok1 += 3;
					break; }

				case '-': {bok = bok - 2;    // Pomniejszenie figury
					x++; y++; bok1 -= 3; 
					break; }

				case 75: {x--; break; }		// Przesuniecie w lewo
				case 77: {x++; break; }		// Przesuniecie w prawo
				case 72: {y--; break; }		// Przesuniecie do gory
				case 80: {y++; break; }		// Przesuniecie do dolu
				case Esq: {break; }			// Wyjscie  
				}
			}
//-----------------------------------------------------------------------------------


// Ta czêœæ kodu pilnuje tego, aby figura nie wychodzi³a poza okno konsoli 


			if (bok < 2)
			{
				switch (przycisk)
				{
				case '-': {bok = bok + 2;   // Blokuje nadmierne zmniejszenie
					x--; y--; bok1 += 3; 
					break; }
				}
			}
			if (bok >= 11)
			{
				switch (przycisk)
				{
				case '+': {bok = bok - 2;    // Blokuje nadmierne powiêkszenie
					x++; y++; bok1 -= 3; 
					break; }
				}
			}
			if (y < 0)
			{
				switch (przycisk)
				{
				case 72: {y++; break; }		// Blokuje nadmierne przesuniecie do gory
				case Esq: {break; }
				}

			}
			if (x - d³ugoœæ_lewa < 0)
			{
				switch (przycisk)
				{
				case 75: {x++; break; }		// Blokuje nadmierne przesuniecie w lewo
				}
			}
			if (x + d³ugoœæ_prawa > 76)
			{
				switch (przycisk)
				{
				case 77: {x--; break; }		// Blokuje nadmierne przesuniecie w prawo
				}

			}
			if (y + (bok1 + bok) > 25)
			{
				switch (przycisk)
				{
				case 80: {y--; break; }		// Blokuje nadmierne przesuniecie w dó³
				}
			}


	} while (przycisk != Esq );
}

