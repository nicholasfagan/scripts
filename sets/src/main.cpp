//
// Created by nfagan on 10/20/19.
//


#include <iostream>
#include <vector>
#include "sets.hpp"
#include "Graph.hpp"
#include "lsis.cpp"

int main() {
    std::vector<float> A {
        1, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
    };
    float c = std::numeric_limits<float>::max();
    size_t subSeq = longestSlowlyIncreasingSubsequence(A,c);
    std::cout << "Max slowly increasing subseq has length " << subSeq << std::endl;
}
