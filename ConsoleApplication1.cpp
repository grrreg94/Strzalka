/* Witam. 
Jest program rysujacy strza³ke skierowan¹ w dó³ z mo¿liwoœæ¹ manipulacji.
Program rysuje strza³kê za pomoc¹ wielu pêtli for umieszczonych w pêtli do while.
Zwiêkszanie i zmniejszanie odbywa siê poprzez pêtle switch case która poprostu zwiêksza/zmniejsza odpowiednie dane.
Ograniczenie ruchu figury wewn¹trz okna odbywa siê poprzez pêdle if, które natychmiast
odwracaj¹ rz¹dane dzia³anie je¿eli wykracza ono poza za³o¿enia, np powiêkszenie ponad jak¹œ wielkoœæ
albo przesuniêcie poza któr¹œ œcianê.

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

