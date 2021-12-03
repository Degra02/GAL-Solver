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
	Matrix m = new Tmatrix(4, 4);
	m->init();
	m->stampa();
	cout << endl << endl;

	printf("%d\n", rg(m));
	m->stampa();
	
	return 0;
}