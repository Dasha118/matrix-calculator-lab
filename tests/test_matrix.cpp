#include <gtest/gtest.h>
#include "matrix.h"
#include <fstream>
#include <cstdio> 
class MatrixFileTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream out("test_temp_matrix.txt");
        out << "2 3\n1 2 3\n4 5 6\n";
        out.close();
    }
    
    void TearDown() override {
        std::remove("test_temp_matrix.txt");
    }
};
TEST_F(MatrixFileTest, Load_ValidFile) {
    Matrix M = matrix_from_file("test_temp_matrix.txt");
    
    EXPECT_EQ(M.rows, 2);
    EXPECT_EQ(M.cols, 3);
    EXPECT_DOUBLE_EQ(M.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(M.data[1][2], 6.0);
    
    free_matrix(M);
}
TEST_F(MatrixFileTest, Load_NonExistentFile) {
    EXPECT_THROW(matrix_from_file("no_such_file_xyz.txt"), std::runtime_error);
}