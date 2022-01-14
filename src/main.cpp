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
	Vector b = new Tvettore(m->nr, 1, 5);

	cout << "Matrice dei coefficienti:" << endl;
	m->stampa();

	cout << endl << "Gram Schmidt" << endl;
	m = gram_schmidt(m);
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
	
	cout << endl << endl;
	print_fract_matrix(m);
	cout << endl << endl;
	return 0;
}
