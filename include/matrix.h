#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>

typedef struct {
    double** data;
    int rows;
    int cols;
} Matrix;

Matrix create_matrix(int rows, int cols);
void free_matrix(Matrix m);
Matrix matrix_add(Matrix a, Matrix b);
Matrix matrix_multiply(Matrix a, Matrix b);
void print_matrix(Matrix m);
Matrix matrix_from_array(double* data, int rows, int cols);
Matrix matrix_from_file(const char* filename);

#endif