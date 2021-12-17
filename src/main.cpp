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
	m1->print();
	fraction_matrix_stairs_gauss_jordan(m1);
	m1->print();
	return 0;

	
}
