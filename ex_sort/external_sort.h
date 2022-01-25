#pragma once

#include <iostream>


class ExternalMergeSort final {
    std::string ifile;
    std::string ofile;
    std::size_t max_size;
public :
    ExternalMergeSort(const std::string& ifile, const std::string& ofile, std::size_t size);

    const void MergeSort() const;
};

