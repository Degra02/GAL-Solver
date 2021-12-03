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

	cout << "Riduzione a scalini:" << endl << endl;
	gauss_jordan_stairs(m);
	m->stampa();
	cout << endl << endl;

	cout << "rref(m):" << endl << endl;;
	rref(m);
	m->stampa();

	return 0;
}