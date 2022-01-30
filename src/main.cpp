#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));
	// Lists list = new Tlists();
	// function_call(list);
	FEqsys eq = init_feqsys("s");
	print_feqsys(feq_sys_rref(eq));
	cout << Rouche_Capelli(eq) << endl;
	print_set_fvectors(feq_sys_sol(eq));
	

	// TODO: improve the parse_linear_function_input() function adapting the variable names

	return 0;
}
