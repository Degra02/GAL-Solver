#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrici.h"
#include "determinanti.h"
#include "vettori.h"
using namespace std;

/* 
	Main per fare test volta per volta
	Sarà necessario creare delle procedure (void) per stampare un menù 
	di opzioni che l'utente potrà scegliere
*/

int main()
{
	srand(time(NULL));
	Matrix m = new Tmatrice(4, 4, 0, 10);
	m->stampa();
	printf("det=%.1f", det(m)); cout << endl;
	printf("det sarrus=%.1f", sarrus(m));

	S(m, 1, 2);
	cout << endl; m->stampa();

	Matrix c = new Tmatrice;
	c->copy_matrix(m);
	c->stampa();
	
	return 0;
}