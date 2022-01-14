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
<<<<<<< HEAD
	Fraction f1 = new Tfraction(1.2);
	Fraction f2 = new Tfraction(2.4);
	fraction_simplification(f1)->print(); cout << endl;
	fraction_simplification(f2)->print(); cout << endl;
	fraction_sum(f1, f2)->print(); cout << endl;
	fraction_difference(f1, f2)->print(); cout << endl;
	fraction_product(f1, f2)->print(); cout << endl;
	fraction_quotient(f1, f2)->print(); cout << endl;

=======
	Matrix m = new Tmatrix(3, 3, 1, 5);

	cout << "Normal matrix" << endl;
	m->stampa();

	cout << endl << endl;
	print_fract_matrix(m);
	cout << endl << endl;

	m = matrix_orthonormal_base(m);

	cout << endl << endl << "Orthonormal base" << endl;
	m->stampa();

	cout << endl << endl;
	print_fract_matrix(m);
	cout << endl << endl;
	
>>>>>>> c7576a75d2f20060732c3e58634ee4d8fff61b13
	return 0;
}
