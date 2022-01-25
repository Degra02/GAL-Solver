#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	// Lists list = new Tlists();
	// function_call(list);

	setFVectorsPtr sv = init_set_fvectors("b");
	print_set_fvectors(sv);
	setFVectorsPtr a = Gram_Schmidt(sv);
	print_set_fvectors(a);
	setFVectorsPtr ao = orthogonal_complement(sv);
	print_set_fvectors(ao);


	return 0;
}
