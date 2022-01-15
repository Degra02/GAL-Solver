#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

int main() {
	srand(time(0));

	FMatrix m1 = init_fmatrix();
	print_fmatrix(m1);

	return 0;
}
