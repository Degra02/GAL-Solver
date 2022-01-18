#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	// Lists list = new Tlists();
	// function_call(list);

	FEqsys eq = init_feqsys("AB");
	print_feqsys(eq);


	return 0;
}
