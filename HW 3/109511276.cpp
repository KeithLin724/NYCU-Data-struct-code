#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

/*
Title:DS HW 3 K map
Written By 練鈞揚
this is a code for DS HW 3 K map
using std=c++11 version
Date: 3/11/2022
*/

#include <iostream>
#include "109511276.h"
using namespace std;

int main(int argc, char* argv[]) {
	tools::Kmap kmap;
	// ofstream testOut("test_print_v3.txt");
	try {
		kmap.read_file(argv[1]); // input2_s.txt
		kmap.run_Quine_McCluskey_to_file(argv[2]);
	}
	catch (const std::exception& e) {
		cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}

