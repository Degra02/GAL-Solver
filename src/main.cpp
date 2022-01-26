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
	setFVectorsPtr b = completion_of_base(sv);
	print_set_fvectors(b);

	return 0;
}
