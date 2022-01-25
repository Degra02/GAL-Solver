#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	Function f = init_function("f");
	print_function(f);
	setFVectorsPtr ker = Ker(f);
	print_set_fvectors(ker);

	return 0;
}
