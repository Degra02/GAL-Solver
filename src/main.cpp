#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));


	FMatrix m1 = init_fmatrix();
	print_fmatrix(m1);
	Nodeptr matList = new Tnode();
	function_call(matList);
	


	return 0;
}
