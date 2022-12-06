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

int main(int argc, char* argv[]) {

    try {
        // reading file 
        solutionTools.read_file(argv[1]);

        // check member function 
        solutionTools.print_class_data();

        // run solution
        solutionTools.run_solution(argv[2]);
    }
    catch (const std::exception& e) {
        cerr << e.what() << '\n';
        exit(-1);
    }
    return 0;

}