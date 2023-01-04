#pragma once 
#ifndef __TWO_SUM_V2__
#define __TWO_SUM_V2__

/*
Title:Hash: Two Sum
Written By 練鈞揚
This is a code for HW 7 Hash: Two sum code
using -std=c++11 version
Date: 24/12/2022
*/

#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>

namespace tools {

    using _IdType = std::int64_t;
    using _valType = std::int32_t;

    class HashLinkedListQueue {
    private:
        struct _Node {
            _valType val, index;
            _Node* next;
            _Node() = default;

            _Node(const _valType& val, const _valType& index, _Node* next = nullptr)
                : val(val), index(index), next(next) {

            }
        };

    public:
        static constexpr auto notFindIndex = std::numeric_limits<_IdType>::min();

        HashLinkedListQueue() = default;
        ~HashLinkedListQueue() {
            while (this->_head != nullptr) {
                auto tmp = this->_head;
                this->_head = this->_head->next;
                delete tmp;
                tmp = nullptr;
            }
            this->_back = nullptr;
            this->_size = 0;
        }

        _valType top() const {
            return this->_head->val;
        }

        // add value to the linked list
        inline void push(const _valType& val, const _IdType& index) {
            if (this->_head == nullptr) { // empty
                this->_head = new _Node(val, index);
                this->_back = this->_head;
                this->_size++;
                return;
            }

            this->_back->next = new _Node(val, index);
            this->_back = this->_back->next;
            this->_size++;
        }

        // find the value is in the queue 
        inline _IdType index(const _valType& val) const {
            if (this->_head == nullptr) { // empty
                return HashLinkedListQueue::notFindIndex;
            }
            for (auto curr = this->_head; curr != nullptr; curr = curr->next) {
                if (curr->val == val) {
                    return curr->index;
                }
            }
            return HashLinkedListQueue::notFindIndex;
        }

    private:
        _Node* _head, * _back;
        std::size_t _size;
    };

    class Solution {
    public:
        static constexpr auto primeNum = 999983;
        static constexpr auto maxArrayData = 100000;

    private:
        inline static std::uint32_t __hashFunc(const _valType& number) {
            return (((number % Solution::primeNum) + Solution::primeNum) % Solution::primeNum);
        }

    public:
        Solution() = default;
        ~Solution() = default;

        inline void read_file(const std::string& fileNameIn) {
            std::ifstream inFile;
            inFile.exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);
            std::stringstream ssInFile;

            try {
                inFile.open(fileNameIn); ssInFile << inFile.rdbuf(); inFile.close();
            }
            catch (const std::exception& e) {
                inFile.close(); throw e;
            }

            ssInFile >> this->_targetNum;

            while (this->_sizeInData < Solution::maxArrayData && ssInFile >> this->_inDataArr[this->_sizeInData]) {
                auto hashNum = Solution::__hashFunc(this->_inDataArr[this->_sizeInData]);
                this->_hashTable[hashNum].push(this->_inDataArr[this->_sizeInData], this->_sizeInData);
                this->_sizeInData++;
            }

        }

        // https://leetcode.com/problems/two-sum/
        inline void run_solution(const std::string& fileNameIn) {
            std::ofstream outFile(fileNameIn);
            for (size_t i = 0; i < this->_sizeInData; i++) {
                auto targetFindNum = this->_targetNum - this->_inDataArr[i];
                auto targetHashNum = Solution::__hashFunc(targetFindNum);

                if (targetHashNum >= 0 && targetHashNum < Solution::primeNum) {
                    auto findIndex = this->_hashTable[targetHashNum].index(targetFindNum);
                    if (findIndex != HashLinkedListQueue::notFindIndex) {

                        if (i == findIndex) { // sample index
                            continue;
                        }

                        outFile << i << '\n' << findIndex;
                        outFile.close();
                        return;
                    }
                }
            }
            outFile.close();

        }
    private:
        // count the input data size 
        std::size_t _sizeInData;

        _IdType _inDataArr[Solution::maxArrayData];

        HashLinkedListQueue _hashTable[Solution::primeNum];

        _IdType _targetNum;

    }solutionTools;
}

#endif // !__TWO_SUM_V2__