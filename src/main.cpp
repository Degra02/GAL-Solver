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
	Fraction f1 = new Tfraction(1.2);
	Fraction f2 = new Tfraction(2.4);
	fraction_simplification(f1)->print(); cout << endl;
	fraction_simplification(f2)->print(); cout << endl;
	fraction_sum(f1, f2)->print(); cout << endl;
	fraction_difference(f1, f2)->print(); cout << endl;
	fraction_product(f1, f2)->print(); cout << endl;
	fraction_quotient(f1, f2)->print(); cout << endl;

	return 0;
}
