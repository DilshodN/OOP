#pragma once

#include <iostream>
#include "sum_all_traits.h"

template<typename T>
auto sum_all(const T &v) {
    return v;
}

template<template<class, class> typename Container, typename Type, typename Alloc = std::allocator<Type>,
        typename =std::enable_if_t<(
                std::is_copy_assignable_v<Type> and
                std::is_default_constructible_v<Type>)>
>
auto sum_all(const Container<Type, Alloc> &v) {
    typename SumAllTraits<Type>::SumType res{};
    for (const auto& i: v) {
        res = res + i;
    }
    return res;
}

template<template<class, class, class, class> typename Map, typename Key, typename Value,
        typename Comp = std::less<Key>, typename Alloc = std::allocator<std::pair<const Key, Value>>,
        typename =
        std::enable_if_t<(
                std::is_copy_assignable_v<Value> and
                std::is_default_constructible_v<Value>)>>
auto sum_all(const Map<Key, Value, Comp, Alloc> &v) {
    typename SumAllTraits<Value>::SumType res{};
    for (const auto& [key, value]: v) {
        res = res + value;
    }
    return res;
}