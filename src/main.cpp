#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	FMatrix m = init_fmatrix();
	m->print();

	

	/*Matrix m = init_matrix();
	print_matrix(m);

	Matrix mt = matrix_transpose(m);
	cout << endl;
	print_matrix(mt);*/

	return 0;
}
