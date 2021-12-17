#pragma once

template <typename T,
        size_t TableSize = 64>
class BaseFilter{
public:
    virtual void insert(const T& value) = 0;
    virtual bool query(const T& value) = 0;
    virtual const std::bitset<TableSize>& read() const = 0;
    virtual void load(std::bitset<TableSize>& array) = 0;
    virtual ~BaseFilter() = default;
};