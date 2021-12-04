#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
using namespace std;

#ifndef __DETERMINANTI_H__
#define __DETERMINANTI_H__

float det(Matrix m);
Matrix reverse_matrix_det(Matrix m);
bool reverse_matrix_validation(Matrix m);
float sarrus(Matrix m);

#endif
