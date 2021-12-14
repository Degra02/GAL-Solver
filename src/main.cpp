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
	// // fraction
	// Fraction f1 = new Tfraction(-2, 1);
	// Fraction f2 = new Tfraction(500, 25);
	// fraction_simplification(fraction_sum(f1, f2))->print();
	// fraction_simplification(fraction_difference(f1, f2))->print();
	// fraction_simplification(fraction_product(f1, f2))->print();
	// fraction_simplification(fraction_quotient(f1, f2))->print();
	// fraction_simplification(fraction_power(f1, 3))->print();
	// Fraction f3 = new Tfraction(8.5647);
	// fraction_simplification(f3)->print();

	FMatrix m1 = new Tfmatrix(3, 4, 0, 10);
	// m1->init(); m1->print();
	m1->print();
	FMatrix m2 = fraction_matrix_transpose(m1);
	printf("\n");
	m2->print();
	return 0;
}
