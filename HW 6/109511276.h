#pragma once

#ifndef __SORTING_V3_H__
#define __SORTING_V3_H__

/*
Title:DS HW 6 Sorting
Written By 練鈞揚
This is a code for DS HW 6 Sorting
using -std=c++11 version
Date: 15/12/2022
*/

#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

namespace tools {
    class Solution {
    private:
        using _IdType = std::int64_t;
        // first is val , second is the idex
        using _PairIndex = std::pair<std::int64_t, _IdType>;


    private:
        // make a merge sort to cnt 
        inline void __helper() {
            std::sort(this->_valArr.begin(), this->_valArr.end(),
                [](const _PairIndex& a, const _PairIndex& b) {
                    return a.first < b.first;
                }
            );

            this->_totalCnt = _IdType();
            auto _sz = this->_valArr.size();

            for (_IdType i = 0; i < _sz; i++) {
                _IdType j = i + 1;
                while (j < _sz && std::llabs(this->_valArr[i].first - this->_valArr[j].first) <= this->_valA) {
                    this->_totalCnt += (std::llabs(this->_valArr[i].second - this->_valArr[j].second) <= this->_valB);
                    j++;
                }
            }
        }

        inline void __helper2() {
            for (size_t i = 0; i < this->_valArr.size(); i++) {
                auto tmpSz = this->_valB + i + 1;
                if (tmpSz >= this->_valArr.size()) {
                    tmpSz = this->_valArr.size();
                }
                for (size_t j = i + 1; j < tmpSz; j++) {

                    this->_totalCnt += (std::llabs(this->_valArr[i].first - this->_valArr[j].first) <= this->_valA);
                }
            }
        }

    public:
        Solution() = default;
        ~Solution() = default;

        void read_file(const std::string& fileNameIn) {
            std::stringstream ss, tranSplit;
            std::ifstream inFile;
            inFile.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);


            try {
                inFile.open(fileNameIn);
                ss << inFile.rdbuf();
                inFile.close();
            }
            catch (const std::exception& e) {
                inFile.close(); throw e;
            }

            std::string tmpLine;
            bool nextLine = false;
            while (std::getline(ss, tmpLine, '\n')) {
                tranSplit.str(""); tranSplit.clear();
                tranSplit << tmpLine;

                if (!nextLine) {
                    std::int64_t numberInt;

                    size_t memberCnt = 0;

                    this->_maxVal = std::numeric_limits<_IdType>::min();
                    this->_minVal = std::numeric_limits<_IdType>::max();

                    while (tranSplit >> numberInt) {
                        this->_valArr.push_back({ numberInt  , memberCnt++ });

                        this->_maxVal = std::max(this->_maxVal, numberInt);
                        this->_minVal = std::min(this->_minVal, numberInt);
                    }

                    nextLine = true;
                    continue;
                }
                tranSplit >> this->_valA >> this->_valB;
            }

        }

        void run_solution(const std::string& fileNameOut) {
            std::ofstream outFile;
            outFile.exceptions(std::ifstream::badbit);
            outFile.open(fileNameOut);

            auto proA = static_cast<double>(this->_valArr.size()) / static_cast<double>(std::llabs(this->_maxVal - this->_minVal));
            proA *= static_cast<double>(2 * std::llabs(this->_valA));

            auto proB = static_cast<double>(this->_valB);

            if (proA < proB) {
                this->__helper();
            }
            else {
                this->__helper2();
            }

            outFile << this->_totalCnt;
            outFile.close();
        }


    private:

        std::vector<_PairIndex> _valArr;
        _IdType _valA, _valB, _totalCnt;
        _IdType _maxVal, _minVal;


    }solutionTools;

}


#endif // !__SORTING_V3_H__
