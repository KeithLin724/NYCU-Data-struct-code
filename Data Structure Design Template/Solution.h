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

    /// @brief This is a function to convert the file data to stringstream
    /// @param ssFileIn stringstream memory
    /// @param fileName input file name
    static inline void __read_file_stream(std::stringstream& ssFileIn, const std::string& fileName) {
        std::ifstream inFile;
        inFile.exceptions(FILE_EXCEP);
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
        outFile.exceptions(FILE_EXCEP);
        try {
            outFile.open(outFileName);
            outFile << ssOut.rdbuf();
            outFile.close();
        }
        catch (const std::exception& e) { outFile.close(); throw e; }

    }


#define READ_FILE(ssIn) try { this->__read_file_stream(ssIn, fileName); } catch (const std::exception& e) { throw e; }
    //#define WRITE_FILE(ssOut)  try { this->__to_file_stream(ssOut, fileNameOut); } catch (const std::exception& e) { throw e; }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    struct OutPut {
        std::stringstream ssOut;
        std::streambuf* oriCoutBuff = nullptr;
    }__outputTools;
    void __change_cout() {
        this->__outputTools.oriCoutBuff = std::cout.rdbuf();
        std::cout.rdbuf(this->__outputTools.ssOut.rdbuf());
    }
    enum class Mode {
        console,
        file,
        both
    };
    void __output(Mode mode, const std::string& fileName = "") {
        std::cout.rdbuf(this->__outputTools.oriCoutBuff);

        switch (mode)
        {
        case Solution::Mode::console:
            std::cout << __outputTools.ssOut.str();
            break;
        case Solution::Mode::file:
            if (fileName == "") {
                throw std::invalid_argument("error file Name");
            }
            this->__to_file_stream(this->__outputTools.ssOut, fileName);
            break;
        case Solution::Mode::both:
            std::cout << __outputTools.ssOut.str();
            this->__to_file_stream(this->__outputTools.ssOut, fileName);
            break;
        }

    }

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




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////Using for DEBUG//////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /// @brief This is a function for debug the class member
    void print_class_data() const {
#ifdef DEBUG
        /*TODO: */
#endif
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////Start your design//////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    /* DATA: data */
public:
    /*TODO:*/

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
        this->__change_cout();
        /*TODO:*/


        this->__output(Mode::file, fileNameOut);
    }

} solutionTools;

#endif //!__SOLUTION_H__