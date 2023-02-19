#ifndef __SOLUTION_STD_HPP__
#define __SOLUTION_STD_HPP__

/*
Title:DS HW 7 STL version
Written By KYLiN
This is a code of DS HW 7 , using the STL to make it
Date: 20/2/2023
*/


#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

namespace tools {
    class Solution {
    public:
        Solution() = default;
        ~Solution() = default;

        void readFile(const std::string& fileName) {
            std::ifstream inFile;
            inFile.exceptions(std::ios::eofbit | std::ios::badbit | std::ios::failbit);
            std::stringstream ssFileIn;

            try {
                inFile.open(fileName); ssFileIn << inFile.rdbuf(); inFile.close();
            }
            catch (const std::exception& e) { inFile.close(); throw e; }

            ssFileIn >> this->__targetNumber;

            std::size_t indexCnt = 0;
            std::int32_t numberIn = 0;

            while (ssFileIn >> numberIn) {
                this->__hashMap.insert({ numberIn , indexCnt++ });
                this->__inArray.push_back(numberIn);
            }
        }

        void runSolution(const std::string& fileName) {
            std::ofstream outFile(fileName);

            for (size_t i = 0; i < this->__inArray.size(); i++) {

                const auto& item = this->__inArray[i];
                auto findItr = this->__hashMap.find(this->__targetNumber - item);

                if (findItr != this->__hashMap.end()) { // find it 
                    if (findItr->second == i) { // same 
                        continue;
                    }
                    outFile << i << '\n' << findItr->second;
                    outFile.close();
                    return;
                }
            }

            outFile.close();
        }

    private:
        std::unordered_map<std::int32_t, std::size_t> __hashMap;
        std::vector<std::int32_t> __inArray;
        std::int32_t __targetNumber;
    } solutionTools;


} // namespace tools



#endif __SOLUTION_STD_HPP__