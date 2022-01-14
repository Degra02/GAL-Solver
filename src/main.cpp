#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	Matrix m = init_matrix();
	print_matrix(m);

	return 0;
}
