/* Witam. 
Jest program rysujacy strza�ke skierowan� w d� z mo�liwo�� manipulacji.
Program rysuje strza�k� za pomoc� wielu p�tli for umieszczonych w p�tli do while.
Zwi�kszanie i zmniejszanie odbywa si� poprzez p�tle switch case kt�ra poprostu zwi�ksza/zmniejsza odpowiednie dane.
Ograniczenie ruchu figury wewn�trz okna odbywa si� poprzez p�dle if, kt�re natychmiast
odwracaj� rz�dane dzia�anie je�eli wykracza ono poza za�o�enia, np powi�kszenie ponad jak�� wielko��
albo przesuni�cie poza kt�r�� �cian�.

Grzegorz Staniewicz 167938.

*/



#include "stdafx.h"
#include "Funkcje.h"

using namespace std;


int main()
{
	rozmiar_okna();
	/*==========================*/

	polskie_litery();
	/*==========================*/

	Naglowek();
	/*==========================*/

 	_getch();
	/*==========================*/

	HideCursor();
	/*==========================*/

 	RysFunk();
	/*==========================*/

	return 0;
}

