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
	Matrix m = new Tmatrix(4, 4, 1, 5);
	m->stampa();
	cout << endl << endl;
	
	print_fract_matrix(m);
	cout << endl << endl;

	Vector vec = new Tvettore(m->nc, 1, 5);
	cout << "Known terms: ";
	vec->stampa();
	Linear_System ls = new Tlisys(m, vec);

	cout << endl << endl;
	cout << "Linear system:" << endl;
	ls->stampa();

	Matrix m2;
	m2 = to_matrix(ls);
	cout << endl << endl << "to_matrix:" << endl;
	m2->stampa();

	cout << endl << endl << "stairs_form:" << endl;
	m2 = ls_rref_full(ls);
	m2 ->stampa();

	return 0;
}