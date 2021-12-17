#pragma once

#include  <vector>

class Matrix final {
private:
    bool multithreading = false;

    std::vector<std::vector<double>> matrix;
    size_t cols{};
    size_t rows{};

    const size_t max_rows_sum = 300;
    const size_t max_rows_mult = 200;
    const size_t max_rows_det = 2;

    [[nodiscard]] size_t size() const;

    friend class CalculationManager;

public:
    Matrix() = default;

    explicit Matrix(size_t rank);

    Matrix(size_t _rows, size_t _cols);

    Matrix(size_t _rows, size_t _cols, double value);

    void multithreading_on();

    void multithreading_off();

    static Matrix create_diagonal(size_t rank, double value);

    void fill(double value);

    [[nodiscard]] size_t get_rows() const;

    [[nodiscard]] Matrix subtract_with(const Matrix &another) const;

    [[nodiscard]] Matrix fast_subtract_with(const Matrix &another, size_t num_of_threads) const;

    [[nodiscard]] Matrix sum_with(const Matrix &another) const;

    [[nodiscard]] Matrix fast_sum_with(const Matrix &another, size_t num_of_threads) const;

    [[nodiscard]] Matrix multiply_with(const Matrix &another) const;

    [[nodiscard]] Matrix fast_multiply_with(const Matrix &another, size_t num_of_threads) const;

    [[nodiscard]] double det() const;

    [[nodiscard]] double simple_det(const Matrix &mat) const;

    [[nodiscard]] double fast_det(const Matrix &mat, size_t num_of_threads) const;

    [[nodiscard]] static Matrix minor(const Matrix &mat, size_t col_index);

    friend Matrix operator+(const Matrix &first, const Matrix &second);

    friend Matrix operator-(const Matrix &first, const Matrix &second);

    friend Matrix operator*(const Matrix &first, const Matrix &second);

    bool operator==(const Matrix &another) const;

    size_t col_max(const size_t column) const;

    double& at(size_t i, size_t j);

    void swap_rows(const size_t i, const size_t j);

    static double calculate_det_without_recursion(const Matrix &mat, size_t num_of_threads);

    static void triangulation(Matrix& mat, const size_t current, const size_t begin, const size_t end);
};