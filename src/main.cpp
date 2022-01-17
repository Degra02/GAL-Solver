#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));
	
	FMatrix m = init_fmatrix("A");
	print_fmatrix(m); print_fmatrix_float(m);
	FMatrix mg = fraction_matrix_gauss_jordan(m);
	print_fmatrix(mg); print_fmatrix_float(mg);
	cout << "rango = " << fraction_matrix_rg(m) << endl;
	FMatrix mr = fraction_matrix_rref(m);
	print_fmatrix(mr); print_fmatrix_float(mr);

	return 0;
}
