#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
#include "jacobi_pd.hpp"
using namespace jacobi_pd;

int main() {
	// srand(time(0));
	// Lists list = new Tlists();
	// function_call(list);

	// TODO: Create a function that checks if a given square representative matrix is symmetric when 
	// TODO: it's calculated from and to the canonical base (orthonormal) of it's dimension. 
	// TODO: If true, then create and return that new matrix, which will be used for the Jacobi Algorithm

	double **matrix = new double*[3];
	for(int i = 0; i < 3; i++){
		matrix[i] = new double[3];
	}

	matrix[0][0] = 1; matrix[0][1] = -1; matrix[0][2] = 0.5; 
	matrix[1][0] = -1; matrix[1][1] = 0; matrix[1][2] = 2.5; 
	matrix[2][0] = 0.5; matrix[2][1] = 2.5; matrix[2][2] = -3; 

	double *evals = new double[3]; 
	double **evecs = new double*[3];
	for(int i = 0; i < 3; i++){
		evecs[i] = new double[3];
	}

	Jacobi<double, double*, double**> eigen_calc(3);

	eigen_calc.Diagonalize(matrix, evals, evecs);

	cout << "Eigenvalues\n";
	for(int i = 0; i < 3; i++){
		cout << evals[i] << " ";
	}










	/*
		If you're reading this, then it means that you're interested in how the code works.
		Structures are the pillars of the program, meaning that everything is centered around them.
		If you find any errors, bugs or want to suggest some improvements, just ask a pull request or create
		an issue on GitHub.
	*/

	return 0;
}
