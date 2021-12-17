#include  "matrix.h"
#include <thread>
#include <future>


size_t Matrix::size() const {
    return cols * rows;
}

Matrix::Matrix(size_t rank) : rows(rank), cols(rank) {
    matrix.resize(rank);
    for (size_t i = 0; i < rows; i++) {
        matrix[i].resize(rank);
    }
}

Matrix::Matrix(size_t _rows, size_t _cols) : rows(_rows), cols(_cols) {
    matrix.resize(rows);
    for (size_t i = 0; i < rows; i++) {
        matrix[i].resize(cols);
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(size_t _rows, size_t _cols, double value) : rows(_rows), cols(_cols) {
    matrix.resize(rows);
    for (size_t i = 0; i < rows; i++) {
        matrix[i].resize(cols);
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = value;
        }
    }
}

void Matrix::multithreading_on() {
    multithreading = true;
}

void Matrix::multithreading_off() {
    multithreading = false;
}

Matrix operator+(const Matrix &first, const Matrix &second) {
    return first.multithreading or second.multithreading ?
           first.fast_sum_with(second, std::thread::hardware_concurrency()) : first.sum_with(second);
}

Matrix operator*(const Matrix &first, const Matrix &second) {
    return first.multithreading or second.multithreading ?
           first.fast_multiply_with(second, std::thread::hardware_concurrency()) : first.multiply_with(second);
}


Matrix operator-(const Matrix &first, const Matrix &second) {
    return first.multithreading or second.multithreading ?
           first.fast_subtract_with(second, std::thread::hardware_concurrency()) : first.subtract_with(second);
}

double Matrix::det() const {
    return multithreading ?
           fast_det(*this, std::thread::hardware_concurrency()) : simple_det(*this);
}

bool Matrix::operator==(const Matrix &another) const {
    if (rows != another.rows || cols != another.cols) return false;
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] != another.matrix[i]) return false;
    }
    return true;
}


Matrix Matrix::create_diagonal(size_t rank, double value) {
    auto diagonal = Matrix(rank, rank);

    for (size_t i = 0; i < rank; i++) {
        diagonal.matrix[i][i] = value;
    }

    return diagonal;
}


void Matrix::fill(double value) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = value;
        }
    }
}

size_t Matrix::get_rows() const {
    return rows;
}

Matrix Matrix::sum_with(const Matrix &another) const {
    if (rows != another.rows || cols != another.cols) {
        return {};
    }
    Matrix sum(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            sum.matrix[i][j] = matrix[i][j] + another.matrix[i][j];
        }
    }
    return sum;
}

Matrix Matrix::subtract_with(const Matrix &another) const {
    if (rows != another.rows or cols != another.cols) {
        return {};
    }
    Matrix subtract(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            subtract.matrix[i][j] = matrix[i][j] - another.matrix[i][j];
        }
    }
    return subtract;
}

Matrix Matrix::multiply_with(const Matrix &another) const {
    Matrix result(rows, another.cols);
    for (size_t i = 0; i < result.rows; i++) {
        for (size_t j = 0; j < result.cols; j++) {
            for (size_t k = 0; k < result.cols; k++) {
                result.matrix[i][j] += matrix[i][k] * another.matrix[k][j];
            }
        }
    }
    return result;
}


Matrix Matrix::minor(const Matrix &mat, size_t col_index) {
    auto col_idx = static_cast<long>(col_index);
    Matrix sub_mat(mat.rows - 1);
    for (size_t i = 1; i < mat.rows; i++) {
        const std::vector<double> &temp_row = mat.matrix[i];
        std::copy(temp_row.begin(), temp_row.begin() + col_idx, sub_mat.matrix[i - 1].begin());
        std::copy(temp_row.begin() + col_idx + 1, temp_row.end(), sub_mat.matrix[i - 1].begin() + col_idx);
    }
    return sub_mat;
}

double Matrix::simple_det(const Matrix &mat) const {
    double det = 0;
    int sign = 1;
    if (mat.cols == 1) {
        return mat.matrix[0][0];
    }
    if (mat.cols == 2) {
        return mat.matrix[0][0] * mat.matrix[1][1] - mat.matrix[0][1] * mat.matrix[1][0];
    }
    for (size_t i = 0; i < mat.cols; i++) {
        det = det + (sign * mat.matrix[0][i] * simple_det(minor(mat, i)));
        sign = -sign;
    }
    return det;
}

size_t Matrix::col_max(const size_t column) const{
    double max = std::abs(matrix[column][column]);
    auto max_pos = column;
    for (auto i = column + 1; i < rows; ++i) {
        double element = std::abs(matrix[i][column]);
        if (element > max) {
            max = element;
            max_pos = i;
        }
    }
    return max_pos;
}

double& Matrix::at(size_t i, size_t j) {
    return matrix[i][j];
}

void Matrix::swap_rows(const size_t i, const size_t j) {
    std::swap(matrix[i], matrix[j]);
}

void Matrix::triangulation(Matrix& mat, const size_t current, const size_t begin, const size_t end)
{
    for (auto j = begin; j < end; ++j) {
        const auto mul = - mat.at(j, current) / mat.at(current, current);
        for (auto k = current; k < mat.rows; ++k) {
            mat.at(j, k) += mat.at(current, k) * mul;
        }
    }
}

double Matrix::calculate_det_without_recursion(const Matrix &mat, size_t num_of_threads) {
    Matrix _matrix(mat);
    auto sgn = 1;
    for(size_t i = 0; i < _matrix.rows - 1; ++i){
        const auto imax = _matrix.col_max(i);
        if(std::abs(_matrix.at(imax, i)) < std::numeric_limits<double>::epsilon()) {
            return 0;
        }
        if(i != imax){
            sgn *= -1;
            _matrix.swap_rows(i, imax);
        }

        std::vector<std::future<void>> threads;
        double n = static_cast<double>(_matrix.rows - i - 1) / static_cast<double>(num_of_threads);
        for(size_t j = 0; j < num_of_threads; j++) {
            auto begin = static_cast<size_t>(j * n + 1 + i);
            auto end = static_cast<size_t>((j + 1) * n + 1 + i);

            if(j < num_of_threads - 1) {
                threads.push_back(std::async(triangulation, std::ref(_matrix), i, begin, end));
            }
            else{
                triangulation(_matrix, i, begin, end);
            }
        }
        for(auto& j: threads){
            j.get();
        }
    }
    auto det = 1;
    for(size_t i = 0; i < _matrix.rows; ++i){
        det *= _matrix.at(i, i);
    }
    return det;
}






