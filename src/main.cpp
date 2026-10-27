#include "matrix.h"
#include <filesystem> 
#include <locale> 
namespace fs = std::filesystem;
int main() {
    try {
        std::cout << "Калькулятор матриц вариант 22\n\n";

        std::string path_str = "data/valid_matrix.txt";
        
        std::cout << "Загрузка матрицы из файла: " << path_str << "\n";
        
        if (!fs::exists(path_str)) {
             throw std::runtime_error("Файл не найден: " + path_str);
        }

        Matrix A = matrix_from_file(path_str.c_str());
        
        std::cout << "Успешно загружена матрица A (" << A.rows << "x" << A.cols << "):\n";
        print_matrix(A);
        
        free_matrix(A);
        
        
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}