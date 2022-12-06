#pragma once
#ifndef __SOLUTION_H__
#define __SOLUTION_H__

/*
Title:This is code for the Data Structure Homework Template
Written By KYLiN
Template
Date: 6/12/2022
*/

#include <sstream>
#include <fstream>

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::cin;

#define debug_string(c) cout << c <<'\n'
#define console_out(ssStream) cout << ssStream.rdbuf()

#else 
#define debug_string(c)
#define console_out(ssStream)
#endif

class Solution {
private:
    //private static function

    /// @brief This is a function to convert the file data to stringstream
    /// @param ssFileIn stringstream memory
    /// @param fileName input file name
    static inline void __read_file_stream(std::stringstream& ssFileIn, const std::string& fileName) {
        std::ifstream inFile;
        inFile.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
        try {
            inFile.open(fileName);
            ssFileIn << inFile.rdbuf();
            inFile.close();
        }
        catch (const std::exception& e) { inFile.close(); throw e; }

    }

    /// @brief This is a function to convert stringstream data to the file data
    /// @param ssOut stringstream data
    /// @param outFileName output file name
    static inline void __to_file_stream(std::stringstream& ssOut, const std::string& outFileName) {
        std::ofstream outFile;
        outFile.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
        try {
            outFile.open(outFileName);
            outFile << ssOut.rdbuf();
            outFile.close();
        }
        catch (const std::exception& e) { outFile.close(); throw e; }

    }


#define READ_FILE(ssIn) try { this->__read_file_stream(ssIn, fileName); } catch (const std::exception& e) { throw e; }
#define WRITE_FILE(ssOut)  try { this->__to_file_stream(ssOut, fileNameOut); } catch (const std::exception& e) { throw e; }
    // function
private:

public:
    Solution() = default;
    ~Solution() = default;

public:
    /// @brief This is a function for debug the class member
    void print_class_data() const {
#ifdef DEBUG
        /*TODO: */
#endif
    }

public:
    /// @brief read file template code 
    /// @param fileName file name input
    void read_file(const std::string& fileName) {
        std::stringstream ssIndata;

        READ_FILE(ssIndata);

        std::string lineReadStrTmp;
        while (std::getline(ssIndata, lineReadStrTmp, '\n')) {
            /*TODO: read format and save */
        }

        /*TODO:*/
    }

    /// @brief this a run solution template
    /// @param fileNameOut output file name
    void run_solution(const std::string& fileNameOut) {
        std::stringstream ssOut;
        /*TODO:*/


        WRITE_FILE(ssOut);
    }


private:
    /* DATA: data */
} solutionTools;

#endif //!__SOLUTION_H__