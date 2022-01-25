#pragma once
#include "matrix.h"
#include <thread>
#include <future>
#include <iostream>
#include <deque>
#include <cmath>


class CalculationManager final{
public:

    CalculationManager(const Matrix &_m1, const Matrix &_m2, size_t _count_of_threads);

    CalculationManager(const Matrix &_m1, size_t _count_of_threads);

    Matrix sum();

    Matrix multiply();

    Matrix subtract();
private:
    size_t count_of_threads;
    const Matrix &m1;
    const Matrix &m2;

    [[nodiscard]] std::vector<std::pair<size_t, size_t>> make_intervals_for_det() const;

    [[nodiscard]] std::vector<std::pair<size_t, size_t>> make_intervals() const;

    Matrix calculate(void (CalculationManager::* f)(std::pair<size_t, size_t> &, Matrix *));

    void sub_sum(std::pair<size_t, size_t> &interval, Matrix *result);

    void sub_multi(std::pair<size_t, size_t> &interval, Matrix *result);

    void sub_substr(std::pair<size_t, size_t> &interval, Matrix *result);
};