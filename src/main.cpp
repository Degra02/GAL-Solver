#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrici.h"
using namespace std;

/* 
	Main per fare test volta per volta
	Sarà necessario creare delle procedure (void) per stampare un menù 
	di opzioni che l'utente potrà scegliere
*/

int main()
{
	srand(time(NULL));
	Matrice m(3, 3, 0, 10);
	m.stampa();

	return 0;
}