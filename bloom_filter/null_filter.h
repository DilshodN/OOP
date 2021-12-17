#pragma once
#include "base_filter.h"

template <typename T,
        size_t TableSize = 64>
class NullFilter final : public BaseFilter<T, TableSize>{
public:
    NullFilter() = default;
    void insert(const T& value) override{};
    bool query(const T& value) override {
        return false;
    };
    const std::bitset<TableSize>& read() const override{};
    void load(std::bitset<TableSize>& array) override{};
};