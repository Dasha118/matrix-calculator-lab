#include "matrix.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) throw std::invalid_argument("Dimensions must be positive");  
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        mat.data[i] = nullptr;
    }

    try {
        for (int i = 0; i < rows; ++i) {
            mat.data[i] = new double[cols];
            memset(mat.data[i], 0, cols * sizeof(double));
        }
    } catch (...) {
        for (int j = 0; j < rows; ++j) {
            if (mat.data[j]) {
                delete[] mat.data[j];
            }
        }
        delete[] mat.data;
        throw;
    }
    return mat;
}

void free_matrix(Matrix m) {
    if (m.data == nullptr) return;
    for (int i = 0; i < m.rows; ++i) {
        if (m.data[i]) { delete[] m.data[i]; m.data[i] = nullptr; }
    }
    delete[] m.data;
    m.data = nullptr;
    m.rows = 0; m.cols = 0;
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) throw std::invalid_argument("Size mismatch in add");
    Matrix res = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i)
        for (int j = 0; j < a.cols; ++j)
            res.data[i][j] = a.data[i][j] + b.data[i][j];
    return res;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) throw std::invalid_argument("Incompatible dims in multiply");
    Matrix res = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i)
        for (int k = 0; k < a.cols; ++k) {
            double val = a.data[i][k];
            if (val == 0.0) continue;
            for (int j = 0; j < b.cols; ++j)
                res.data[i][j] += val * b.data[k][j];
        }
    return res;
}

void print_matrix(Matrix m) {
    if (!m.data || m.rows <= 0 || m.cols <= 0) { std::cout << "[Empty]\n"; return; }
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < m.rows; ++i) {
        std::cout << "[";
        for (int j = 0; j < m.cols; ++j) {
            std::cout << std::setw(8) << m.data[i][j];
            if (j < m.cols - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    Matrix mat = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mat.data[i][j] = data[i * cols + j];
    return mat;
}

Matrix matrix_from_file(const char* filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Cannot open file: ") + filename);
    }

    int rows = 0, cols = 0;
    
    if (!(file >> rows >> cols)) {
        throw std::invalid_argument("Invalid header: could not read dimensions");
    }

    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Dimensions must be positive integers");
    }

    Matrix mat = create_matrix(rows, cols);

    try {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double value;
                if (!(file >> value)) {
                    throw std::invalid_argument("Unexpected end of file or invalid number format");
                }
                mat.data[i][j] = value;
            }
        }
    } catch (...) {
        free_matrix(mat);
        throw;
    }

    return mat;
}