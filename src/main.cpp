#include <iostream>
#include "jacobi_pd.hpp"
#include "Utilities/commands.h"
#include "Utilities/database.h"
using namespace jacobi_pd;

int main() {
	srand(time(0));
	Lists list = new Tlists();
	function_call(list);
	
	/*
		If you're reading this, then it means that you're interested in how the code works.
		Structures are the pillars of the program, meaning that everything is centered around them.
		If you find any errors, bugs or want to suggest some improvements, just ask a pull request or create
		an issue on GitHub.
	*/

	return 0;
}
