#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

/* 
	Main per fare test volta per volta
	Sarà necessario creare delle procedure (void) per stampare un menù 
	di opzioni che l'utente potrà scegliere
*/

int main()
{
	srand(time(NULL));
	Matrix m = new Tmatrix(4, 4, 0, 10);
	m->stampa();
	cout << endl << endl;
	System S = System(3, 4);

	Matrix m1 = new Tmatrix(3, 3); 
	m1->init();
	m1->stampa();

	S.stampa();
	
	return 0;
}