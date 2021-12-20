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

int main() {
	srand(time(0));
	Matrix m = new Tmatrix(3, 3, 1, 5);

	cout << "Normal matrix" << endl;
	m->stampa();

	m = matrix_orthonormal_base(m);

	cout << endl << endl << "Orthonormal base" << endl;
	m->stampa();
	
	
}
