#pragma once

#include <iostream>
#include "sum_all_traits.h"

template <typename T>
std::enable_if_t<std::is_arithmetic_v<T> || std::is_same_v<T, std::string>, int>
auto sum_all(const T& v){
    return v;
}

template <typename T>
auto sum_all(const T& v){
    typename SumAllTraits<typename T::value_type>::SumType res{};
    for (const auto i : v)
        res += i;
    return res;
}

template <typename T, std::enable_if_t<std::is_arithmetic_v<typename T::mapped_type>, int> = 0>
auto sum_all(const T& v){
    typename SumAllTraits<typename T::mapped_type>::SumType res{};
    for (const auto i : v)
        res += i.second;
    return res;
}