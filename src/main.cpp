#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));
	
	FMatrix m = init_fmatrix();
	print_fmatrix(m);
	fraction_matrix_gauss_jordan(m);
	print_fmatrix(m);

	return 0;
}
