#include "external_sort.h"
#include <fstream>
#include <vector>

ExternalMergeSort::ExternalMergeSort(const std::string &ifile, const std::string &ofile, std::size_t size) {
    if(!ifile.empty() and !ofile.empty() and size) {
        this->ifile = ifile;
        this->ofile = ofile;
        this->max_size = size;
    }
}

namespace {
    void sort_file(const std::string &file) {
        std::ifstream inp(file);
        std::vector<int> v;
        std::string num;
        while (inp >> num) {
            v.push_back(stoi(num));
        }
        inp.close();
        remove(file.c_str());

        std::ofstream onp(file);
        std::sort(v.begin(), v.end());

        for (auto &elem: v) {
            onp << std::to_string(elem) << " ";
        }
    }

    void merge_files(const std::string &hard_mem, const std::string &rom, const std::string &write_file) {
        std::fstream onp(write_file);
        std::ifstream rom_nums(rom);
        std::ifstream hard_mem_nums(hard_mem);

        std::vector<int> ROM;
        std::string num;
        while (rom_nums >> num) {
            ROM.push_back(stoi(num));
        }

        int num_from_hard_mem;
        hard_mem_nums >> num_from_hard_mem;
        auto elem = ROM.begin();
        while (not hard_mem_nums.eof() and elem != ROM.end()) {

            if (*elem > num_from_hard_mem) {
                onp << num_from_hard_mem << " ";
                hard_mem_nums >> num_from_hard_mem;
            } else if (*elem <= num_from_hard_mem) {
                onp << *elem << " ";
                elem++;
            }
        }

        if (not hard_mem_nums.eof()) {
            onp << num_from_hard_mem << hard_mem_nums.rdbuf();
        }

        if (elem != ROM.end()) {
            for (; elem != ROM.end(); elem++)
                onp << *elem << " ";
        }

        onp.close();
        rom_nums.close();
        hard_mem_nums.close();
    }

}

const void ExternalMergeSort::MergeSort() const {
    std::size_t size = max_size;
    std::string num;

    std::ifstream inp(ifile);

    std::size_t i = 1;
    while (not inp.eof()) {
        std::ofstream chunk("chunk" + std::to_string(i++) + ".txt");
        for (size_t j = 0; j < max_size; j++) {
            inp >> num;
            chunk << num << " ";
            if (inp.eof()) break;
        }
        chunk.close();
    }
    inp.close();


    for (int j = 1; j < i; j++)
        sort_file("chunk" + std::to_string(j) + ".txt");

    size_t temp = i;
    for (int k = 1; k < temp; k++) {
        merge_files("chunk" + std::to_string(k) + ".txt",
                    "chunk" + std::to_string(k + 1) + ".txt",
                    "chunk" + std::to_string(k + 1) + ".txt");
    }

    std::ofstream onp(ofile);
    std::ifstream last_chunk("chunk" + std::to_string(i - 1) + ".txt");
    onp << last_chunk.rdbuf();

    for (int j = 1; j < i; j++)
        remove(("chunk" + std::to_string(j) + ".txt").c_str());
}