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

	FMatrix m1 = new Tfmatrix(4, 4, 0, 10);
	FMatrix m2 = new Tfmatrix(4, 4, 0, 10);
	m1->print(); cout << endl;
	m2->print(); cout << endl;
	FMatrix m3 = fraction_matrix_multiplication(m1, m2);
	m3->print(); cout << endl;
	FMatrix m4 = fraction_matrix_scalar_multiplication(m1, 1.2);
	m4->print(); cout << endl;
	return 0;
}
