/*
Title:DS HW 2 find path
Written By 練鈞揚
This is a code for Data struct HW 2 find path

using -std=c++11 version
Date: 17/10/2022
*/

#include <iostream>
#include "109511276.h"

using namespace std;

int main(int argc, char* argv[]) { //int argc, char* argv[])
  tools::Path path;
  try {

    path.read(argv[1]);
    path.find_path(argv[2]);
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    exit(-1);
  }


  return 0;
}


