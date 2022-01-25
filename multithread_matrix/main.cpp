#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <array>
#include <fstream>

Matrix diagonal0(size_t n, double val = 1.0) {
    Matrix m{n};
    for (size_t i = 0; i < m.get_rows(); i++)
        for (size_t k = 0; k < m.get_rows(); k++)
            if (i != k) m.at(i, k) = val;
    return m;
}

constexpr size_t theads_max = 9u;

void SubstrTest(std::ostream &ostream);

template<size_t Threads>
void PrintResult(std::ostream& stream, std::initializer_list<int>& dimensions,
                 std::array<std::vector<double>, Threads>& times){
    stream << std::setw(6) << "dim/th" << ";";
    for(auto dim: dimensions){
        stream << std::setw(12) << dim << ";";
    }
    stream << std::endl;
    for(size_t th = 0; th < times.size(); ++th){
        stream << std::setw(6) << (th + 1) << ";";
        for(size_t dim = 0; dim < times[th].size(); ++dim){
            stream << std::setw(12) << std::fixed << times[th][dim]  << ";";
            stream.flush();
        }
        stream << std::endl;
    }
}

void DeterminantTest(std::ostream& stream)
{
    stream << "Determinant:" << std::endl;
    auto dimensions = { 6, 7, 10, 11, 15, 25, 50, 111, 150, 201, 300, 500};
    std::array<std::vector<double>, theads_max> times;

    stream << std::setw(11) << "th/dim" << ";";
    for (size_t th = 1; th <= theads_max; ++th) {
        stream << std::setw(12) << th << ";";
    }
    stream << std::endl;
    stream << std::setprecision(7);
    for (auto dim : dimensions) {
        auto d = diagonal0(dim);
        double res = ((double)(dim & 1) != 0 ? 1 : -1) * ((double)dim - 1);
        stream << std::setw(4) << d.get_cols();
        stream << "(" << std::setw(5) << std::defaultfloat << res << ");"; stream.flush();
        for (size_t th = 1; th <= theads_max; ++th) {
            double time = std::numeric_limits<double>::max();
            for (int i = 0; i < 5; i++)
            {
                auto start = std::chrono::high_resolution_clock::now();
                d.multithreading_on();
                d.set_limits(1, 1, 1);
                auto det = d.det();
                time = std::min(time, std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count());
                if (std::abs(res - det) > 1e-6) {
                    stream << std::endl << "ERROR: calculation("<<
                    dim <<"/"<< th <<") current det = " << std::setprecision(11) <<
                    std::fixed << det << " != res = " << res; stream.flush();
                    break;
                }
            }
            stream << std::setw(12) << std::setprecision(7) << std::fixed << time << ";"; stream.flush();
            times[th - 1].emplace_back(time);
        }
        stream <<std::endl;
    }
    PrintResult(stream, dimensions, times);
    std::cout << "Determinant test finished" << std::endl;
}

void SumTest(std::ostream& stream)
{
    stream << "Sum:" << std::endl;
    auto dimensions = {6, 7, 10, 11, 15, 25, 50, 111, 150, 201, 300, 500, 501, 1000};
    std::array<std::vector<double>, theads_max> times;

    stream << std::setw(11) << "th/dim" << ";";
    for (size_t th = 1; th <= theads_max; ++th) {
        stream << std::setw(12) << th << ";";
    }
    stream << std::endl;
    for (auto dim : dimensions) {
        auto d1 = diagonal0(dim);
        auto d2 = diagonal0(dim);
        auto res = diagonal0(dim, 2);
        stream << std::setw(4) << d1.get_cols();
        stream << "(" << std::setw(7)  << ");"; stream.flush();
        for (size_t th = 1; th <= theads_max; ++th) {
            double time = std::numeric_limits<double>::max();
            for (int i = 0; i < 5; i++)
            {
                auto start = std::chrono::high_resolution_clock::now();
                d1.multithreading_on();
                d1.set_limits(1, 1, 1);
                d2.set_limits(1, 1, 1);
                auto sum = d1.fast_sum_with(d2, th);
                time = std::min(time, std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count());
                if (res != sum) {
                    stream << std::endl << "ERROR: calculation("<<
                           dim <<"/"<< th <<") current sum =! sum";
                    stream.flush();
                    break;
                }
            }
            stream << std::setw(12) << std::setprecision(7) << std::fixed << time << ";"; stream.flush();
            times[th - 1].emplace_back(time);
        }
        stream <<std::endl;
    }
    PrintResult(stream, dimensions, times);
    std::cout << "Sum test finished" << std::endl;
}

void SubstrTest(std::ostream &stream) {
    stream << "Substr:" << std::endl;
    auto dimensions = {6, 7, 10, 11, 15, 25, 50, 111, 150, 201, 300, 500, 501, 1000};
    std::array<std::vector<double>, theads_max> times;

    stream << std::setw(11) << "th/dim" << ";";
    for (size_t th = 1; th <= theads_max; ++th) {
        stream << std::setw(12) << th << ";";
    }
    stream << std::endl;
    for (auto dim : dimensions) {
        auto d1 = diagonal0(dim, 2);
        auto d2 = diagonal0(dim);
        auto res = diagonal0(dim);
        stream << std::setw(4) << d1.get_cols();
        stream << "(" << std::setw(7)  << ");"; stream.flush();
        for (size_t th = 1; th <= theads_max; ++th) {
            double time = std::numeric_limits<double>::max();
            for (int i = 0; i < 5; i++)
            {
                auto start = std::chrono::high_resolution_clock::now();
                d1.multithreading_on();
                d1.set_limits(1, 1, 1);
                d2.set_limits(1, 1, 1);
                auto sub = d1.fast_subtract_with(d2, th);
                time = std::min(time, std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count());
                if (res != sub) {
                    stream << std::endl << "ERROR: calculation("<<
                    dim <<"/"<< th <<") current sub =! sub";stream.flush();

                    break;
                }
            }
            stream << std::setw(12) << std::setprecision(7) << std::fixed << time << ";"; stream.flush();
            times[th - 1].emplace_back(time);
        }
        stream <<std::endl;
    }
    PrintResult(stream, dimensions, times);
    std::cout << "Substr test finished" << std::endl;
}

void MultTest(std::ostream &stream) {
    stream << "Mult:" << std::endl;
    auto dimensions = {6, 7, 10, 11, 15, 25, 50, 111, 150, 201, 300, 500};
    std::array<std::vector<double>, theads_max> times;

    stream << std::setw(11) << "th/dim" << ";";
    for (size_t th = 1; th <= theads_max; ++th) {
        stream << std::setw(12) << th << ";";
    }
    stream << std::endl;
    for (auto dim : dimensions) {
        auto d1 = Matrix::create_diagonal(dim, 1);
        auto d2 = Matrix::create_diagonal(dim, 1);
        auto res = Matrix::create_diagonal(dim, 1);
        stream << std::setw(4) << d1.get_cols();
        stream << "(" << std::setw(7)  << ");"; stream.flush();
        for (size_t th = 1; th <= theads_max; ++th) {
            double time = std::numeric_limits<double>::max();
            for (int i = 0; i < 5; i++)
            {
                auto start = std::chrono::high_resolution_clock::now();
                d1.multithreading_on();
                d1.set_limits(1, 1, 1);
                d2.set_limits(1, 1, 1);
                auto mul = d1.fast_multiply_with(d2, th);
                time = std::min(time, std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count());
                if (res != mul) {
                    stream << std::endl << "ERROR: calculation("<<
                    dim <<"/"<< th <<") current mult =! mult";stream.flush();

                    break;
                }
            }
            stream << std::setw(12) << std::setprecision(7) << std::fixed << time << ";"; stream.flush();
            times[th - 1].emplace_back(time);
        }
        stream <<std::endl;
    }
    PrintResult(stream, dimensions, times);
    std::cout << "Mult test finished" << std::endl;
}




int main() {
//    std::ostream& st = std::cout;
    std::ofstream st("results.txt");
//    SimpleDeterminantTest(st);
    DeterminantTest(st);
    SumTest(st);
    SubstrTest(st);
    MultTest(st);

    return 0;
}