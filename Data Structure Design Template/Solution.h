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

#define FILE_EXCEP std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit

#include <iostream>
using std::cout;
using std::cin;

#include <vector>
#ifdef DEBUG
#define debug(c) std::cerr c
#define debug_stringln(c) std::cerr << c << '\n'
#else 
#define debug(c)
#define debug_stringln(c)
#endif

class Solution {
    ////////////////////////////////////////!!!Dont Change!!!//////////////////////////////////////////////////////////////////////////////
private:
    //private static function
    /// @brief This is a function to convert stringstream data to the file data
    /// @param ssOut stringstream data
    /// @param outFileName output file name
    static inline void __to_file_stream(std::stringstream& ssOut, const std::string& outFileName) {
        std::ofstream outFile;
        outFile.exceptions(FILE_EXCEP);
        try {
            outFile.open(outFileName);
            outFile << ssOut.rdbuf();
            outFile.close();
        }
        catch (const std::exception& e) { outFile.close(); throw e; }

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
private:
    struct debugTools {
        std::ofstream outLogFile;
        std::streambuf* oriCerrBuff = nullptr;
    }__debug;
    inline void __DEBUG_init() {
        this->__debug.outLogFile.exceptions(FILE_EXCEP);

        try { this->__debug.outLogFile.open("Log.txt"); }
        catch (const std::exception& e) { throw e; }

        this->__debug.oriCerrBuff = std::cerr.rdbuf();
        std::cerr.rdbuf(this->__debug.outLogFile.rdbuf());
    }

    inline void __DEBUG_end() {
        std::cerr.rdbuf(this->__debug.oriCerrBuff);
        this->__debug.outLogFile.close();
    }

public:
    Solution() { this->__DEBUG_init(); };
    ~Solution() { this->__DEBUG_end(); };
#else
public:
    Solution() = default;
    ~Solution() = default;
#endif // DEBUG
public:
    /// @brief read file template code 
    /// @param fileName file name input
    inline static std::vector<std::string> read_file(const std::string& fileName) {
        std::stringstream ssIndata;
        std::ifstream inFile;
        std::vector<std::string> _res;
        inFile.exceptions(FILE_EXCEP);
        try {
            inFile.open(fileName);
            ssIndata << inFile.rdbuf();
            inFile.close();
        }
        catch (const std::exception& e) { inFile.close(); throw e; }

        std::string lineReadStrTmp;
        while (std::getline(ssIndata, lineReadStrTmp, '\n')) {
            _res.push_back(lineReadStrTmp);
        }
        return _res;
    }
private:
    enum class Mode {
        console,
        file,
        both
    };
public:
    void run_solution(const std::string& fileNameIn, const std::string& fileNameOut) {
        // config the cout to sstream
        std::stringstream ssOut;
        auto oriCoutBuff = std::cout.rdbuf();
        std::cout.rdbuf(ssOut.rdbuf());

        auto outPutMode = this->run_your_design(fileNameIn);

        // re config the output stream
        std::cout.rdbuf(oriCoutBuff);
        switch (outPutMode) {
        case Solution::Mode::console:
            std::cout << ssOut.str();
            break;
        case Solution::Mode::file:
            if (fileNameOut == "") {
                throw std::invalid_argument("error file Name");
            }
            this->__to_file_stream(ssOut, fileNameOut);
            break;
        case Solution::Mode::both:
            std::cout << ssOut.str();
            this->__to_file_stream(ssOut, fileNameOut);
            break;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////Start your design//////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    /* DATA: data */
public:
    Mode run_your_design(const std::string& fileNameIn) {
        auto inFileData = Solution::read_file(fileNameIn);

        /*TODO: */

        debug(<< "output Log file : Hello world");
        std::cout << "output file Hello world\n";

        // chose your output mode
        return Mode::file;
    }

    /*TODO: some design*/

} solutionTools;

#endif //!__SOLUTION_H__