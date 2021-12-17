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

void time_test_sum(Matrix &A, Matrix &B, size_t thread_count) {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    Matrix C = A.fast_sum_with(B, thread_count);
    std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Multithreading calculation of the sum " << A.get_rows() << "x" << A.get_rows() << " with "
              << thread_count << " threads : " << dur.count() << std::endl;
}

void time_test_mult(Matrix &A, Matrix &B, size_t thread_count) {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    Matrix C = A.fast_multiply_with(B, thread_count);
    std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Multithreading calculation of the mult " << A.get_rows() << "x" << A.get_rows() << " with "
              << thread_count << " threads : " << dur.count() << std::endl;
}

void time_test_det(Matrix &A, size_t thread_count) {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    double det = A.fast_det(A, thread_count);
    std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Multithreading calculation of the det " << A.get_rows() << "x" << A.get_rows() << " with "
              << thread_count << " threads : " << dur.count() << std::endl;
}

void time_test_det_no_rec(Matrix &A, size_t thread_count) {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    double det = A.calculate_det_without_recursion(A, thread_count);
    std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Multithreading calculation of the det without recursion " << A.get_rows() << "x" << A.get_rows() << " with "
              << thread_count << " threads : " << dur.count() << std::endl;
}

TEST(time_research, sum100) {
    Matrix A(100, 100, 1);
    Matrix B(100, 100, 1);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    Matrix C = A.sum_with(B);
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;

    for (size_t i = 2; i <= 10; i++) {
        time_test_sum(A, B, i);
    }
}

TEST(time_research, sum500) {
    Matrix A(500, 500, 1);
    Matrix B(500, 500, 1);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    Matrix C = A.sum_with(B);
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;

    for (size_t i = 2; i <= 10; i++) {
        time_test_sum(A, B, i);
    }
}

TEST(time_research, sum1000) {
    Matrix A(1000, 1000, 1);
    Matrix B(1000, 1000, 1);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    Matrix C = A.sum_with(B);
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;

    for (size_t i = 2; i <= 10; i++) {
        time_test_sum(A, B, i);
    }
}

TEST(time_research, sum5000) {
    Matrix A(5000, 5000, 1);
    Matrix B(5000, 5000, 1);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    Matrix C = A.sum_with(B);
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;

    for (size_t i = 2; i <= 10; i++) {
        time_test_sum(A, B, i);
    }
}

TEST(time_research, mult100) {
    Matrix A(100, 100, 1);
    Matrix B(100, 100, 1);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    Matrix C = A.multiply_with(B);
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Execution of sum " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;

    for (size_t i = 2; i <= 10; i++) {
        time_test_mult(A, B, i);
    }
}

TEST(time_research, mult250) {
    Matrix A(250, 250, 1);
    Matrix B(250, 250, 1);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    Matrix C = A.multiply_with(B);
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Execution of multiply " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;

    for (size_t i = 2; i <= 10; i++) {
        time_test_mult(A, B, i);
    }
}

TEST(time_research, det9x9) {
    Matrix A(9, 9, 1);

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    double det = A.det();
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Execution of det " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;

    for (size_t i = 2; i <= 6; i += 2) {
        time_test_det(A, i);
    }
}

TEST(time_research, det10x10) {
    Matrix A(10, 10, 1);

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    double det = A.det();
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout << "Execution of det " << A.get_rows() << "x" << A.get_rows() << " " << dur.count() << std::endl;

    for (size_t i = 2; i <= 6; i += 2) {
        time_test_det(A, i);
    }
}

TEST(time_research, det15x15) {
    Matrix A(15, 15, 1);

    for (size_t i = 1; i <= 10; i += 1) {
        time_test_det_no_rec(A, i);
    }
}


TEST(Matrix_determinant, simple) {
    Matrix identity = Matrix::create_diagonal(9, 2);
    double det = identity.det();
    EXPECT_TRUE(det == 512);
}

TEST(Matrix_determinant, no_rec) {
    Matrix identity = Matrix::create_diagonal(9, 2);
    double det = Matrix::calculate_det_without_recursion(identity, 4);
    EXPECT_TRUE(det == 512);
}

TEST(Matrix_determinant, multithreading) {
    Matrix identity = Matrix::create_diagonal(9, 2);
    identity.multithreading_on();
    double det = identity.det();
    EXPECT_TRUE(det == 512);
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