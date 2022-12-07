/*
Title:This is code for the Data Structure Homework Template
Written By KYLiN
using Template example
Date: 6/12/2022
*/

// open the debug mode 
#define DEBUG 

#include <iostream>
#include "Solution.h"
using namespace std;

int main() {
    try {
        // run solution
        solutionTools.run_solution("test.txt", "output.txt");
    }
    catch (const std::exception& e) {
        cerr << e.what() << '\n';
        exit(-1);
    }
    return 0;
}