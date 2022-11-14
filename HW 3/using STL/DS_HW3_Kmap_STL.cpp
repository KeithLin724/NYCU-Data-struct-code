/*
Title:DS HW 3 K map STL version
Written By KYLiN
This is a code for HW 3 example
using std=c++11 version
Date: 4/11/2022
*/


#include <iostream>
#include "Kmap_stl.h"
using namespace std;

int main() {
	tools::Kmap kmap;
	//ofstream testOut("test_print_stl.txt");
	try {
		kmap.read_file("input2_s.txt"); // input2_s.txt
		kmap.run_Quine_McCluskey_to_file("test2_stl.txt");
	}
	catch (const std::exception& e) {
		cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}

