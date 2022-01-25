#include "calculator_manager.h"

CalculationManager::CalculationManager(const Matrix &_m1, const Matrix &_m2, size_t _count_of_threads)
        : count_of_threads(_count_of_threads), m1(_m1), m2(_m2) {}

CalculationManager::CalculationManager(const Matrix &_m1, size_t _count_of_threads)
        : count_of_threads(_count_of_threads), m1(_m1), m2(_m1) {}


void CalculationManager::sub_substr(std::pair<size_t, size_t> &interval, Matrix *result) {
    for (size_t i = interval.first; i < interval.second; i++) {
        for (size_t j = 0; j < result->cols; j++) {
            result->matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
        }
    }
}

void CalculationManager::sub_sum(std::pair<size_t, size_t> &interval, Matrix *result) {
    for (size_t i = interval.first; i < interval.second; i++) {
        for (size_t j = 0; j < result->cols; j++) {
            result->matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
        }
    }
}

void CalculationManager::sub_multi(std::pair<size_t, size_t> &interval, Matrix *result) {
    for (size_t i = interval.first; i < interval.second; i++) {
        for (size_t j = 0; j < result->cols; j++) {
            for (size_t k = 0; k < result->cols; k++) {
                result->matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
            }
        }
    }
}

std::vector<std::pair<size_t, size_t>> CalculationManager::make_intervals() const {
    std::vector<std::pair<size_t, size_t>> intervals;
    size_t distance = m1.rows / count_of_threads;
    size_t current_row = 0;
    for (size_t i = 0; i < count_of_threads; i++) {
        intervals.emplace_back(current_row, current_row + distance);
        current_row += distance;
    }
    intervals[count_of_threads - 1].second = m1.rows;
    return intervals;
}

std::vector<std::pair<size_t, size_t>> CalculationManager::make_intervals_for_det() const {
    std::vector<std::pair<size_t, size_t>> intervals;
    size_t distance = m1.rows / count_of_threads;
    if (distance == 0 || m1.rows % count_of_threads != 0) {
        distance++;
    }
    size_t current_row = 0;
    for (; current_row + distance < m1.rows; current_row += distance) {
        intervals.emplace_back(current_row, current_row + distance);
    }
    intervals.emplace_back(current_row, m1.rows);
    return intervals;
}


Matrix CalculationManager::calculate(void (CalculationManager::*f)(std::pair<size_t, size_t> &, Matrix *)) {
    Matrix result(m1.rows, m1.cols);
    auto intervals = make_intervals();
    std::vector<std::future<void>> all_futures(intervals.size() - 1);
    for (size_t i = 0; i < all_futures.size(); i++) {
        std::packaged_task<void(std::pair<size_t, size_t> &, Matrix *)> temp_task(
                [&](std::pair<size_t, size_t> &a, Matrix *b) { return (this->*f)(a, b); });
        all_futures[i] = std::async(std::launch::async, std::move(temp_task), std::ref(intervals[i]), &result);
    }
    (this->*f)(intervals[intervals.size() - 1], &result);
    for (size_t i = 0; i < intervals.size() - 1; i++) {
        all_futures[i].get();
    }
    return result;

}

Matrix CalculationManager::multiply() {
    return calculate(&CalculationManager::sub_multi);
}

Matrix CalculationManager::sum() {
    return calculate(&CalculationManager::sub_sum);
}

Matrix CalculationManager::subtract() {
    return calculate(&CalculationManager::sub_substr);
}




double Matrix::fast_det(const Matrix &mat, size_t num_of_threads) const{
    double det = 0;
    Matrix _matrix(mat);
    auto sgn = 1;
    for(size_t i = 0; i < _matrix.get_rows() - 1; ++i){
        const auto imax = _matrix.col_max(i);
        if(std::abs(_matrix.at(imax, i)) < std::numeric_limits<double>::epsilon()) {
            det = 0;
            return det;
        }
        if(i != imax){
            sgn *= -1;
            _matrix.swap_rows(i, imax);
        }

        std::vector<std::future<void>> threads;
        double n = static_cast<double>(_matrix.get_rows() - i - 1) / static_cast<double>(num_of_threads);
        for(size_t j = 0; j < num_of_threads; j++) {
            size_t begin = std::floor(j * n + 1 + i);
            size_t end = std::floor((j + 1) * n + 1 + i);

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
    det = 1;
    for(size_t i = 0; i < _matrix.get_rows(); ++i){
        det *= _matrix.at(i, i);
    }
    det *= sgn;
    return det;
}

Matrix Matrix::fast_subtract_with(const Matrix &another, size_t num_of_threads) const {
    if (rows != another.rows || cols != another.cols) {
        return {};
    }
    size_t threads_count = rows / max_rows_sum + 1;
    if (threads_count == 1) return subtract_with(another);
    if (threads_count > num_of_threads) threads_count = num_of_threads;
    CalculationManager subtractor(*this, another, threads_count);
    return subtractor.subtract();
}

Matrix Matrix::fast_sum_with(const Matrix &another, size_t num_of_threads) const {
    if (rows != another.rows || cols != another.cols) {
        return {};
    }
    size_t threads_count = rows / max_rows_sum + 1;
    if (threads_count == 1) return sum_with(another);
    if (threads_count > num_of_threads) threads_count = num_of_threads;
    CalculationManager adder(*this, another, threads_count);
    return adder.sum();
}

Matrix Matrix::fast_multiply_with(const Matrix &another, size_t num_of_threads) const {
    if (cols != another.rows) {
        return {};
    }
    size_t threads_count = rows / max_rows_mult + 1;
    if (threads_count == 1) return multiply_with(another);
    if (threads_count > num_of_threads){
        threads_count = num_of_threads;
    }
    CalculationManager multiplier(*this, another, threads_count);
    return multiplier.multiply();
}