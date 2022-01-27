#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));
	// Lists list = new Tlists();
	// function_call(list);

	Function f = init_function("f");
	print_function(f);
	FVector v = init_fvector("v");
	setFVectorsPtr sv = Counter_Im(f, v);
	print_set_fvectors(sv);

	// TODO: improve the parse_linear_function_input() function adapting the variable names

	return 0;
}
