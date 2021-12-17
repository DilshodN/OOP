#include "calculator_manager.h"

CalculationManager::CalculationManager(const Matrix &_m1, const Matrix &_m2, size_t _count_of_threads)
        : count_of_threads(_count_of_threads), m1(_m1), m2(_m2) {}

CalculationManager::CalculationManager(const Matrix &_m1, size_t _count_of_threads)
        : count_of_threads(_count_of_threads), m1(_m1), m2(_m1) {}

double CalculationManager::sub_det(std::pair<size_t, size_t> &interval) {
    double det = 0;
    int sign;
    if (interval.first % 2 == 0) sign = 1;
    else sign = -1;
    for (size_t i = interval.first; i < interval.second; i++) {
        det = det + (sign * m1.matrix[0][i] * m1.simple_det(m1.minor(m1, i)));
        sign = -sign;
    }
    return det;
}

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


double CalculationManager::calculate_det() {
    auto intervals = make_intervals_for_det();
    std::vector<std::future<double>> all_futures;
    all_futures.reserve(intervals.size());
    for (auto &interval: intervals) {
        all_futures.push_back(
                std::async(std::launch::async, &CalculationManager::sub_det, this, std::ref(interval)));
    }
    double det = 0;
    for (size_t i = 0; i < intervals.size(); i++) {
        det += all_futures[i].get();
    }
    return det;
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

double CalculationManager::determinant() {
    return calculate_det();
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

double Matrix::fast_det(const Matrix &mat, size_t num_of_threads) const {
    size_t threads_count = rows / max_rows_det;
    if (threads_count == 1) return simple_det(mat);
    if (threads_count > num_of_threads) threads_count = num_of_threads;
    CalculationManager det_calculator(mat, threads_count);
    return det_calculator.determinant();
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