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
	Matrix m = new Tmatrix(4, 4, 0, 1);
	m->stampa();
	cout << endl << endl;

	/*D(m, 1, 10);
	m->stampa();
	cout << endl << endl;
	

	E(m, 2, 1, -2);
	m->stampa();
	cout << endl << endl;
	
	S(m, 1, 2);
	m->stampa();
	gauss_jordan(m);*/

	gauss_jordan_stairs(m);
	m->stampa();

	return 0;
}