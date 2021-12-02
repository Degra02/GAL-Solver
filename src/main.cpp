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
	Matrix m = new Tmatrice(3, 3, 0, 10);
	m->stampa();
	printf("det=%f", det(m));
	printf("det sarrus=%f", sarrus(m));
	
	return 0;
}