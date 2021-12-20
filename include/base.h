#include "all-headers.h"

#ifndef __BASE_H__
#define __BASE_H__

bool matrix_is_square(Matrix m);
bool matrix_is_base(Matrix m);
Vector matrix_column_to_vector(Matrix m, int c);
Matrix gram_schmidt(Matrix m, Matrix a1, Vector v);
Matrix matrix_orthonormal_base(Matrix m);
void matrix_init_column(Matrix m, Vector v, int c);

#endif