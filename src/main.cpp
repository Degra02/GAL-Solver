#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	// Lists list = new Tlists();
	// function_call(list);

	FMatrix m = init_fmatrix("m");
	cout << "det=";
	det(m)->print();


	return 0;
}
