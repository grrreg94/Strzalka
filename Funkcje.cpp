
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

void polskie_litery() // umo�liwia pisanie nazw funkcji itp po polsku 
{
	locale locpl("Polish_Poland");	
	locale::global(locpl);			
	cout.imbue(locpl);				
	cin.imbue(locpl);				
}

/*=================================================================================*/

void gotoxy(int x, int y) // kireuje kursor na porz�deane wsp�rz�dne x oraz y 
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/*=================================================================================*/

void HideCursor() // sprawia �e obok figury lub te� tekstu nie mruga poziomy kursor
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

/*=================================================================================*/

void PoczatkowyRozmiar(int & bok, int & bok1) // funkcja wyboru pocz�tkowego rozmiaru poprzez dob�r odpowiednich warto��i 
											  // bok i bok1 odpowiedzoanych za rysowanie trzonu strza�ki oraz daszka strza�ki
{
	int Wybor;

	do
	{

		cout << "\nPodaj wymiar pocz�tkowy figury, od 1 do 3: ";
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

void Czyszczenie() // Funkcja czy�ci ekran pomi�dzy
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

void Naglowek() // nic doda� nic uj��, wypisuje nag��wek
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << "================================================================================\n";
	SetConsoleTextAttribute(color, FOREGROUND_GREEN);

	cout << "\t\t\t  Grzegorz Staniewicz 167938\n";
	cout << "\t\t\t\tZadanie nr 62\n";
	cout << "\tNapisz program rysowania za pomoc� znaku ASCII poni�szej figury.\n \tProgram powinien umo�liwi�\n";
	cout << "\tWyb�r znaku kodu ASCII\n";
	cout << "\tWczytanie pocz�tkowych rozmiar�w figury\n";
	cout << "\tPrzesuwanie figury klawiszami strza�ek\n";
	cout << "\tPowi�kszanie oraz mniejszanie figury za pomoc� znak� + i -\n";
	cout << "\tOgraniczanie przesuwania i rozmiar�w figury do obszaru ekranun\n";
	cout << "\tFigur� jest strza�ka sierowana w d�\n\n";
	SetConsoleTextAttribute(color, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	cout << "================================================================================\n\n";
	SetConsoleTextAttribute(color, BACKGROUND_RED | BACKGROUND_GREEN |FOREGROUND_BLUE);

	cout << "Naci�nij dowolny klawisz";

}



/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/



void RysFunk() //Funkcja najwa�niejsza, odpowiedzialna za rysowanie, powi�kszanie i przes�wanie fig�ry
 {
	Czyszczenie();

//-----------------------------------------------------------------------------------

	const int Esq = 27;
	int x, y, x1, y1, y3, xPrawy, xLewy, bok, bok1, d�ugo��_prawa, d�ugo��_lewa;


			/*
			Legenda danych:
			x, y, x1, y1, y3: Zmienne wsp�rz�dnych x oraz y, w kilku wersjach aby m�c w pewnych momentach programu wraca� do jakich�, 
			wcze�niejszych warto�ci.

			xPrawy, xLewy: Wykorzystywane do rysowania podstawy grotu.

			bok, bok1 : bok to d�ugo�� boku trzonu strza�ki a bok1 d�ugo�� boku grotu (daszka) strza�ki.

			d�ugo��_prawa, d�ugo��_lewa : To zmienne wykorzystywane przy ogarniczaniu przesuwania strza�ki horyzontalnie 

			znak: Znak kodu ASCI, w tej zmiennej przechowujemy czym ma by� rysowana figura.
			przysk: To przysik + - oraz strza�ki - do maniupulowania fig�r�
			*/


	char przycisk;
	char znak;

	x = 33;
	y = 4;
	

//-----------------------------------------------------------------------------------


				cout << "==========================================================\n";
				cout << "Podaj jakim znakiem z klawiatury figura ma by� narysowana: ";
				cin >> znak; cout << "\n";
				cin.sync();

	


//-----------------------------------------------------------------------------------

PoczatkowyRozmiar(bok, bok1); //####################################################

//-----------------------------------------------------------------------------------

// Tu mamy zestaw p�tli rysuj�cych nasz� figur�
	do
	{

				// Definicje zmiennych koniecznych do utrzymania figury w polu na osi x przy r�nych jej rozmiarach 
				d�ugo��_lewa = 0;
				d�ugo��_prawa = -1;

				if (bok <= 3)
					d�ugo��_prawa = -3;
				if (bok >= 7)
					d�ugo��_prawa = 1;
				if (bok >= 9)
					d�ugo��_prawa = 2;
//-----------------------------------------------------------------------------------

				Czyszczenie();

		x1 = x; 
		y1 = y;

		gotoxy(x1, y1);
//------------
		for (int i = 1; i <= bok; i++)      // Rysowanie g�rnej kraw�dzi trzonu strz��ki 
		{
			cout << znak << " ";
			d�ugo��_prawa++;
			d�ugo��_prawa++;
		}
//------------
		for (int i = 1; i <= bok - 1; i++)    // Rysowanie bok�w trzonu strza�ki
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

		y1++; // Obni�enie warto�ci y-owej aby zacz�� rysowanie grotu strza�ki

//------------
		for (int i = 1; i < bok - 1 ; i++)   // Pionowa podstawa grotu z lewej strony
		{
			x1--;					
			x1--;
			gotoxy(x1, y1);					
			cout << znak << " ";
			xLewy = x1;
			d�ugo��_lewa++;
			d�ugo��_lewa++;


			/*Funkcja rysuje t� prost� poruszaj�c si� w lewo,
			od defaultowej sta�ej jak� jest x, czyli od miejca w kt�rym zako�czono rysowanie
			trzonu strza�ki*/
		}
//------------

		x1 = x + 2 * bok - 2; // Przesuni�cie kursora rysuj�cego pionow� podstaw� grotu na prawo 

//------------
		for (int i = 1; i < bok - 1; i++)   // Pionowa podstawa grotu z prawej strony
		{
			x1++;
			x1++;
			gotoxy(x1, y1);
			cout << znak << " ";
			xPrawy = x1;
			d�ugo��_prawa++;

			/*Funkcja rysuje t� prost� poruszaj�c si� w prawo,
			od defaultowej sta�ej jak� jest x, czyli od miejca w kt�rym zako�czono rysowanie
			trzonu strza�ki*/
		}
//------------

		y3 = y1; // Y1 to wsp��dna lewego boku ostrego zako�czenia strza�ki a nowa, Y3 - prawego 

//------------
		for (int i = 1; i < bok1; i++)    // Lewy bok ostrego zako�czenia
		{
			y1++;
			gotoxy(xLewy + 1, y1);
			cout << znak;
			xLewy++;
			xLewy++;
		}

//------------		 
		for (int i = 1; i < bok1; i++)    // Prawy bok ostrego zako�czenia
		{
			y3++;
			gotoxy(xPrawy - 1, y3);
			cout << znak;
			xPrawy--;
			xPrawy--;
		}


		


//-----------------------------------------------------------------------------------
// Tutaj odbywa si� operacja powi�kszania i pomniejszania figury
		
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


// Ta cz�� kodu pilnuje tego, aby figura nie wychodzi�a poza okno konsoli 


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
				case '+': {bok = bok - 2;    // Blokuje nadmierne powi�kszenie
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
			if (x - d�ugo��_lewa < 0)
			{
				switch (przycisk)
				{
				case 75: {x++; break; }		// Blokuje nadmierne przesuniecie w lewo
				}
			}
			if (x + d�ugo��_prawa > 76)
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
				case 80: {y--; break; }		// Blokuje nadmierne przesuniecie w d�
				}
			}


	} while (przycisk != Esq );
}

