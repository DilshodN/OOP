#pragma once
#include <iostream>
#include "sum_all_traits.h"

template <typename T>
std::enable_if_t<(std::is_arithmetic_v<T> or std::is_same_v<T, std::string>), T>
sum_all(const T& v){
    return v;
}

template <typename T, typename =
        std::enable_if_t<(
        std::is_copy_assignable_v<typename T::value_type> and
        std::is_default_constructible_v<typename T::value_type>)>
        >
decltype(auto) sum_all(const T& v){
    typename SumAllTraits<typename T::value_type>::SumType res{};
    for(const auto i: v){
        res = res + i;
    }
    return res;
}

template <typename T, typename =
        std::enable_if_t<(
        std::is_copy_assignable_v<typename T::mapped_type> and
        std::is_default_constructible_v<typename T::mapped_type>)>
        >
auto sum_all(const T& v){
    typename SumAllTraits<typename T::mapped_type>::SumType res{};
    for (const auto i : v)
        res = res + i.second;
    return res;
}