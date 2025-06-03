// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>

void prtPerm(const std::vector<char>& elem) {
    JKL_Tree tr(elem);
    auto perms = gAllPerm(tr);
    
    std::cout << "All permutations for [";
    for (char c : elem) std::cout << c << " ";
    std::cout << "] (" << perms.size() << " total):\n";
    
    for (const auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << " ";
    }
    std::cout << "\n\n";
}

void runExp() {
    std::ofstream dFile("experiment_data.csv");
    dFile << "n,gAllPerm_time,gPermFrst_time,gPermScnd_time\n";
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 1; n <= 10; ++n) {
        std::vector<char> elem(n);
        for (int i = 0; i < n; ++i) elem[i] = '1' + i;

        JKL_Tree tr(elem);
        size_t tPerm = tr.gPermCount();
        std::uniform_int_distribution<> distr(1, tPerm);
        int tNum = distr(gen);

        auto start = std::chrono::high_resolution_clock::now();
        gAllPerm(tr);
        auto end = std::chrono::high_resolution_clock::now();
        double t1 = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        gPermFrst(tr, tNum);
        end = std::chrono::high_resolution_clock::now();
        double t2 = std::chrono::duration<double>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        gPermScnd(tr, tNum);
        end = std::chrono::high_resolution_clock::now();
        double t3 = std::chrono::duration<double>(end - start).count();

        dFile << n << "," << t1 << "," << t2 << "," << t3 << "\n";
        std::cout << "n=" << n << " completed. Times: " << t1 << "s, " 
                  << t2 << "s, " << t3 << "s\n";
    }
    dFile.close();
    std::cout << "Experiment data saved to experiment_data.csv\n";
}

void analyzeResults() {
    std::ifstream inFile("experiment_data.csv");
    if (!inFile.is_open()) {
        std::cerr << "Error opening results file\n";
        return;
    }

    std::string header;
    std::getline(inFile, header);

    double avg1 = 0, avg2 = 0, avg3 = 0;
    int count = 0;

    int n;
    char comma;
    double t1, t2, t3;
    while (inFile >> n >> comma >> t1 >> comma >> t2 >> comma >> t3) {
        avg1 += t1;
        avg2 += t2;
        avg3 += t3;
        count++;
    }

    if (count > 0) {
        avg1 /= count;
        avg2 /= count;
        avg3 /= count;

        std::cout << "\nPerformance Analysis:\n";
        std::cout << "Average gAllPerm time: " << avg1 << "s\n";
        std::cout << "Average gPermFrst time: " << avg2 << "s\n";
        std::cout << "Average gPermScnd time: " << avg3 << "s\n";

        if (avg3 < avg2 && avg3 < avg1) {
            std::cout << "gPermScnd is the fastest method overall\n";
        } else if (avg2 < avg3 && avg2 < avg1) {
            std::cout << "gPermFrst is the fastest method overall\n";
        } else {
            std::cout << "gAllPerm is the fastest method overall\n";
        }
    }

    inFile.close();
}

int main() {
    prtPerm({'1','2','3'});
    prtPerm({'a','b','c','d'});
    
    runExp();
    analyzeResults();
    
    return 0;
}
