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

	Matrix m = init_matrix();
	m->stampa();

	/*cout << "Vettore termini noti" << endl;
	b->stampa();
	cout << endl;
	
	cout << endl << "Sistema lineare" << endl;
	Linear_System ls = new Tlisys(m, b);
	Matrix m2 = to_matrix(ls);
	m2->stampa();

	cout << endl << "Riduzione a scalini" << endl;
	m2 = ls_rref_full(ls);
	m2->stampa();*/

	return 0;
}
