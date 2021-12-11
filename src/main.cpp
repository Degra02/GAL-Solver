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
	// fraction
	Fraction f1 = new Tfraction(-2, 1);
	Fraction f2 = new Tfraction(500, 25);

	simplification(f1)->print();
	simplification(f2)->print();

	sum(f1, f2)->print();	
	difference(f1, f2)->print();
	simplification(product(f1, f2))->print();
	simplification(quotient(f1, f2))->print();
	power(f1, 3)->print();
	
	return 0;
}
