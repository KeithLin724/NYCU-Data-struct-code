#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

/*
Title:DS HW4 Gate Calculator
Written By 練鈞揚
This is a code of the DS HW 4 Gate Calculator

using std=c++11 version
Date: 14/11/2022
*/

#include <iostream>
#include "109511276.h"
using namespace std;

int main(int argc, char* argv[]) {

	tools::Solution solution;
	try {
		solution.read_file(argv[1]);
		solution.run_solution(argv[2]);
	}
	catch (const std::exception& e) {
		cerr << e.what() << '\n';
		exit(-1);
	}
	return 0;
}
