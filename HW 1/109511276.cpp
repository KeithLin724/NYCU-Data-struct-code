/*
Title:Data Struct HW 1
Written By 練鈞揚
This is a code for DS HW1
using std=c++14 version
Date: 29/9/2022
*/

#include "109511276.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define all(c) c.begin(), c.end()

using namespace std;

int main(int argc, char *argv[]) {
    ifstream inFile;
	inFile.exceptions(ifstream::badbit);

	string tmp;

	vector<tools::ArrType> dataInArr;

	stringstream ss;

	try {
		inFile.open(argv[1]);

		while (getline(inFile, tmp)) {
                        dataInArr.emplace_back(tools::ArrType());

			ss.str(""); ss.clear();

			ss << tmp;
			int tmpNum = 0;
			while (ss >> tmpNum) {
				dataInArr.back().push_back(tmpNum);
			}


		}
		inFile.close();
	}
	catch (const std::exception& e) {
		cerr << e.what() << '\n';
		exit(-1);
	}

	ofstream outFile;
	outFile.exceptions(ofstream::badbit);

	tools::ArrType fArr = dataInArr.front(), dArr = dataInArr.back(); 

	fArr = tools::take_out_front_zero(fArr);
	dArr = tools::take_out_front_zero(dArr);

	try {
		outFile.open(argv[2]);
		auto res = tools::div(fArr, dArr);

		outFile << tools::ArrType_to_string(res.first) << '\n';
		outFile << tools::ArrType_to_string(res.second) << '\n';

		outFile.close();
	}
	catch (const std::exception& e) {
		cerr << e.what() << '\n';
		exit(-2);
	}

    return 0;
}


