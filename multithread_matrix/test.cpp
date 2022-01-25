#include <gtest/gtest.h>
#include "../matrix.h"
#include "../calculator_manager.h"
#include <chrono>

static const unsigned long big_size_for_mult = 500;
static const unsigned long big_size_for_sum = 1000;

static Matrix big_mult_matrix(big_size_for_mult, big_size_for_mult, 777);
static Matrix big_diagonal_matrix = Matrix::create_diagonal(big_size_for_mult, 1);
static Matrix big_filled_matrix(big_size_for_sum, big_size_for_sum, 777);
static Matrix big_empty_matrix(big_size_for_sum, big_size_for_sum);


TEST(Matrix_determinant, simple) {
    Matrix identity = Matrix::create_diagonal(9, 2);
    double det = identity.det();
    EXPECT_TRUE(det == 512);
}


TEST(Matrix_determinant, multithreading) {
    Matrix identity = Matrix::create_diagonal(9, 2);
    identity.multithreading_on();
    double det = identity.det();
    EXPECT_TRUE(det == 512);
}

TEST(Matrix_determinant, testing_multithreading_det_with_no_recursion) {
    Matrix identity = Matrix::create_diagonal(30, 2);
    identity.multithreading_on();
    double det = identity.det();
    EXPECT_EQ(det, 1073741824);
}

TEST(Matrix_multiplication, simple) {

    Matrix multiplied = big_diagonal_matrix * big_mult_matrix;
    EXPECT_TRUE(multiplied == big_mult_matrix);
}

TEST(Matrix_multiplication, multithreading) {
    big_diagonal_matrix.multithreading_on();
    Matrix multiplied = big_diagonal_matrix * big_mult_matrix;
    big_diagonal_matrix.multithreading_off();
    EXPECT_TRUE(multiplied == big_mult_matrix);
}

TEST(Matrix_sum, simple) {
    Matrix sum = big_empty_matrix + big_filled_matrix;
    EXPECT_TRUE(sum == big_filled_matrix);
}

TEST(Matrix_sum, multithreading) {
    big_empty_matrix.multithreading_on();
    Matrix sum = big_empty_matrix + big_filled_matrix;
    big_empty_matrix.multithreading_off();
    EXPECT_TRUE(sum == big_filled_matrix);
}

TEST(Matrix_substract, simple) {
    Matrix substract = big_filled_matrix - big_empty_matrix;
    EXPECT_TRUE(substract == big_filled_matrix);
}

TEST(Matrix_substract, multithreading) {
    big_filled_matrix.multithreading_on();
    Matrix substract = big_filled_matrix - big_empty_matrix;
    EXPECT_TRUE(substract == big_filled_matrix);
}

Matrix diagonal0(size_t n, double val = 1.0) {
    Matrix m{n};
    for (size_t i = 0; i < m.get_rows(); i++)
        for (size_t k = 0; k < m.get_rows(); k++)
            if (i != k) m.at(i, k) = val;
    return m;
}

TEST(Matrix_determinant, simple_d0) {
    Matrix identity = diagonal0(9);
    double det = identity.det();
    EXPECT_DOUBLE_EQ(det, 8.0);
}

TEST(Matrix_determinant, no_rec_d0) {
    Matrix identity = diagonal0(9);
    identity.multithreading_on();
    double det = identity.det();
    EXPECT_DOUBLE_EQ(det, 8.0);
}

TEST(Matrix_determinant, simple_d010) {
    Matrix identity = diagonal0(10);
    double det = identity.det();
    EXPECT_DOUBLE_EQ(det, -9.0);
}

TEST(Matrix_determinant, no_rec_d010) {
    Matrix identity = diagonal0(10);
    identity.multithreading_on();
    double det = identity.det();
    EXPECT_DOUBLE_EQ(det, -9.0);
}