#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	// Lists list = new Tlists();
	// function_call(list);

	setFVectorsPtr sv = init_set_fvectors("a");
	print_set_fvectors(sv);
	FMatrix m = set_vectors_to_fmatrix(sv);
	print_fmatrix(m);

	return 0;
}
