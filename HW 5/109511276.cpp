#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

/*
Title:Graph critical path
Written By 練鈞揚
This is a code of DW HW 5 Graph critical path
using -std=c++11 version
Date: 3/12/2022
*/

#include <iostream>
#include "109511276.h"
using namespace std;

int main(int argc, char* argv[]) {
	try {
		tools::solutionTools.read_file(argv[1]);
		tools::solutionTools.run_solution(argv[2]);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		exit(-1);
	}
	return 0;
}

