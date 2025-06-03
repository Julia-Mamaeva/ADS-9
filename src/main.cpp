// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include "tree.h"

void printPermutations(const std::vector<char>& elements) {
    PMTree tree(elements);
    auto perms = getAllPerms(tree);

    std::cout << "All permutations for [";
    for (char c : elements) std::cout << c << " ";
    std::cout << "] (" << perms.size() << " total):\n";

    for (const auto& perm : perms) {
        for (char c : perm) std::cout << c;
        std::cout << " ";
    }
    std::cout << "\n\n";
}

void runExperiment() {
    std::ofstream data_file("experiment_data.csv");
    data_file << "n,getAllPerms_time,getPerm1_time,getPerm2_time\n";
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 1; n <= 10; ++n) {
        std::vector<char> elements(n);
        for (int i = 0; i < n; ++i) elements[i] = '1' + i;

        PMTree tree(elements);
        size_t total_perms = tree.getPermutationsCount();
        std::uniform_int_distribution<> distr(1, total_perms);
        int test_num = distr(gen);

        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double all_perms_time = 
            std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm1(tree, test_num);
        end = std::chrono::high_resolution_clock::now();
        double get_perm1_time = 
            std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm2(tree, test_num);
        end = std::chrono::high_resolution_clock::now();
        double get_perm2_time = 
            std::chrono::duration<double>(end - start).count();

        data_file << n << "," << all_perms_time << "," 
                 << get_perm1_time << "," << get_perm2_time << "\n";
        std::cout << "n=" << n << " completed. Times: " 
                 << all_perms_time << "s, " << get_perm1_time 
                 << "s, " << get_perm2_time << "s\n";
    }
    data_file.close();
    std::cout << "Experiment data saved to experiment_data.csv\n";
}

int main() {
    printPermutations({'1', '2', '3'});
    printPermutations({'a', 'b', 'c', 'd'});
    runExperiment();
    return 0;
}
