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
	Matrice m(3, 3, 0, 10);
	m.stampa();
	printf("\nDet = %.1f", sarrus(m));
	
	int dim;
	cout << endl << "Dim array = "; cin >> dim;
	float valori[dim];
	for(int i = 0; i < dim; i++){
		cin >> valori[i];
	}

	Vettore v(valori, dim);
	v.stampa();
	
	return 0;
}