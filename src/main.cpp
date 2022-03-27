#include <iostream>
#include "jacobi_pd.hpp"
#include "Utilities/commands.h"
#include "Utilities/database.h"
using namespace jacobi_pd;

int main() {
	srand(time(0));
	Lists list = new Tlists();
	function_call(list);

	// TODO: Create a function that checks if a given square representative matrix is symmetric when 
	// TODO: it's calculated from and to the canonical base (orthonormal) of it's dimension. 
	// TODO: If true, then create and return that new matrix, which will be used for the Jacobi Algorithm

	
	/*
		If you're reading this, then it means that you're interested in how the code works.
		Structures are the pillars of the program, meaning that everything is centered around them.
		If you find any errors, bugs or want to suggest some improvements, just ask a pull request or create
		an issue on GitHub.
	*/

	return 0;
}
