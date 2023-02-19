#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
/*
Title:DS HW 7 STL version
Written By KYLiN
This is a code of DS HW 7 , using the STL to make it
Date: 20/2/2023
*/

#include <iostream>
#include "Solution_Std.hpp"
using namespace std;

int main(int argc, char* argv[]) {

    try {
        tools::solutionTools.readFile(argv[1]);
        tools::solutionTools.runSolution(argv[2]);

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}