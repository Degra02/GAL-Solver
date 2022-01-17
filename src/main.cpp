#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	// Lists list = new Tlists();
	// function_call(list);

	FMatrix m = init_fmatrix("Alberto");
	print_fmatrix(m);
	FMatrix mt = fraction_matrix_transpose(m);
	print_fmatrix(mt);
	FMatrix s = fraction_matrix_sum(m, mt);
	print_fmatrix(s);
	FMatrix d = fraction_matrix_difference(s, m);
	print_fmatrix(d);

	return 0;
}
