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
	Matrix m = new Tmatrix(4, 4, 0, 10);
	m->stampa();
	cout << endl << endl;
<<<<<<< HEAD

	/*print_fract_matrix(m);
	printf("det=%f\n", det(m));
	cout << endl;
	Matrix i = reverse_matrix_det(m);
	i->stampa();*/

	gauss_jordan(m);
	m->stampa();

	
=======
	System S = System(3, 4);

	Matrix m1 = new Tmatrix(3, 3); 
	m1->init();
	m1->stampa();

	S.stampa();
>>>>>>> b1f66410aaf7dbfe94435d9b8f44c2b4af75b365
	
	return 0;
}