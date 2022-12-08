#pragma once

#ifndef __GATE_CALCULATOR_H__
#define __GATE_CALCULATOR_H__

/*
Title:DS HW4 Gate Calculator
Written By 練鈞揚
This is a code of the DS HW 4 Gate Calculator

using std=c++11 version
Date: 14/11/2022
*/

#include <unordered_set> 
// https://shengyu7697.github.io/std-set/
#include <unordered_map>
#include <sstream>
// https://cplusplus.com/reference/string/string/find/
// https://iter01.com/346671.html
#include <fstream>
#include <vector>
#include <deque>
#include <tgmath.h>
#include <algorithm>
#include <functional>
// https://shengyu7697.github.io/std-function/

#define all(c) c.begin(), c.end()

namespace tools {
	using _IdType = std::uint32_t;

	// https://www.sololearn.com/discuss/107828/can-xor-and-xnor-be-applied-by-c-logic
	class GateCalculator { // this is a class for choose
	private:
		using _Inv = bool;
		static bool _AND(const std::vector<std::int16_t>& input) {
			return std::all_of(all(input), [](const std::int16_t& a) { return a == 1; });
		}

		static bool _OR(const std::vector<std::int16_t>& input) {
			return std::any_of(all(input), [](const std::int16_t& a) { return a == 1; });
		}

		static bool _XOR(const std::vector<std::int16_t>& input) {
			return (std::count(all(input), 1) & 1);
		}

	public:
		GateCalculator() = default;
		~GateCalculator() = default;

		inline static std::vector<std::int16_t> to_binary(const std::uint32_t& number, const std::uint32_t& bitsNumber) {
			std::vector<std::int16_t> res(bitsNumber, 0);

			for (std::int32_t i = bitsNumber - 1; i >= 0; i--) {
				res[bitsNumber - 1 - i] = ((number >> i) & 1);
			}

			return res;
		}

	public:
		inline bool superGate(const std::vector<std::int16_t>& input, const std::string& gateFuncName) {
			std::pair <_Inv, std::function<bool(std::vector<std::int16_t>)>> findFunc;
			try {
				findFunc = this->_gateMap.at(gateFuncName); // find the function is in the gate table
			}
			catch (const std::exception& e) {
				throw e;
			}

			auto& gateFunc = findFunc.second;

			// calculate the output 
			if (input.empty()) {
				return false;
			}
			std::vector<std::int16_t> cpy = input;

			if (input.size() == 1) {
				cpy.push_back(input.front());
			}

			return (findFunc.first ? !gateFunc(cpy) : gateFunc(cpy));
		}

	private:
		const std::unordered_map<std::string, std::pair<_Inv, std::function<bool(std::vector<std::int16_t>)>>> _gateMap = {
			{"AND" , {false, GateCalculator::_AND}},
			{"OR"  , {false, GateCalculator::_OR }},
			{"XOR" , {false, GateCalculator::_XOR}},
			{"NAND", {true , GateCalculator::_AND}},
			{"NOR" , {true , GateCalculator::_OR }},
			{"XNOR", {true,  GateCalculator::_XOR}}
		};

	}gateCalculator;

	class Solution {
	private:
		const std::string _satisfiableStr[2] = {
			"UNSAT" , // if not find the input can make SAT output in 1												 
			"SAT"  // can find the input can make SAR output in 1
		};

	private:
		// is a function to classification the gate 
		inline void __to_gate_array() {
			for (size_t i(0); i < this->_indexWithGateType.size(); i++) {
				try {
					this->_gateToIndexArray.at(this->_indexWithGateType[i]).push_back(i);
				}
				catch (const std::exception& e) {
					this->_gateToIndexArray.insert({ this->_indexWithGateType[i], {1, static_cast<std::uint32_t>(i)} });
				}
			}

			for (auto& elm : this->_gateToIndexArray) {
				std::sort(all(elm.second));
			}
		}

		// https://leetcode.com/problems/minimum-height-trees/
		inline void __find_Minimum_Height_Tree() {
			if (this->_numberOfRoot == 1) {
				this->_minimumHeadIndex = { 0 };
				return;
			}

			std::vector<std::unordered_set<_IdType>> graphCpy(this->_graph);

			std::vector<std::int32_t> degree(this->_graphNodeDegree);

			std::deque<_IdType> q;
			for (size_t i = 0; i < degree.size(); i++) {
				if (degree[i] == 1) {
					q.push_back(i);
				}
			}

			auto numberRoot = this->_numberOfRoot;
			while (numberRoot > 2) {
				auto len = q.size();
				numberRoot -= len;

				for (size_t _ = 0; _ < len; _++) {
					auto node = q.front();
					q.pop_front();
					for (const auto& elm : graphCpy[node]) {
						if (--degree[elm] == 1) {
							q.push_back(elm);
						}
					}
				}
			}
			this->_minimumHeadIndex.assign(all(q));
		}

		// input the root to find the output //  rootHead it the root father
		inline bool __gate_tree_calculator(_IdType root, _IdType rootHead) {
			if (this->_indexWithGateType[root] == "INPUT") {
				return bool(this->_nodeOutputStateArr[root]);
			}

			std::vector<std::int16_t> gateInputArray;
			for (const auto& indexOfNeighbor : this->_graph[root]) {
				if (indexOfNeighbor == rootHead) {
					continue;
				}
				if (this->_indexWithGateType[indexOfNeighbor] != "INPUT" && this->_nodeOutputStateArr[indexOfNeighbor] == -1) {
					this->_nodeOutputStateArr[indexOfNeighbor] = this->__gate_tree_calculator(indexOfNeighbor, root);
				}
				gateInputArray.push_back(this->_nodeOutputStateArr[indexOfNeighbor]);

			}
			this->_nodeOutputStateArr[root] = gateCalculator.superGate(gateInputArray, this->_indexWithGateType[root]);
			return bool(this->_nodeOutputStateArr[root]);
		}

		// output the pattern in the string 
		inline std::string __output_to_string(const std::vector<std::int16_t>& inputState) const {
			std::string res;

			try {
				for (const auto& elm : this->_gateToIndexArray.at("INPUT")) {
					res += std::to_string(elm) + ":" + std::to_string(inputState[elm]) + "\n";
				}
			}
			catch (const std::exception& e) { throw e; }

			return res;
		}

	public:
		Solution() = default;
		~Solution() = default;

		//read file
		inline void read_file(const std::string& file_name) {
			std::ifstream inFile;
			inFile.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
			std::stringstream tran, ss;
			try {
				inFile.open(file_name);
				ss << inFile.rdbuf();
				inFile.close();
			}
			catch (const std::exception& e) {
				inFile.close();
				throw e;
			}

			ss >> this->_numberOfRoot;

			this->_indexWithGateType.assign(this->_numberOfRoot, "INPUT");
			this->_graphNodeDegree.assign(this->_numberOfRoot, 0);
			this->_graph.assign(this->_numberOfRoot, {});
			this->_nodeOutputStateArr.assign(this->_numberOfRoot, std::int16_t(-1));

			std::string tmpIn;
			while (std::getline(ss, tmpIn, '\n')) {
				tran.str("");
				tran.clear();
				if (tmpIn[0] == '(') { // get the edge  
					auto tmp = tmpIn.substr(tmpIn.find('(') + 1, tmpIn.find(')') - 1);
					tran << tmp.replace(tmp.find(','), 1, " ");
					_IdType a, b;
					tran >> a >> b;

					this->_graph[a].insert(b);
					this->_graph[b].insert(a);

					this->_graphNodeDegree[a]++;
					this->_graphNodeDegree[b]++;

				}
				else if (tmpIn.find(':') != std::string::npos) { // get type 
					tran << tmpIn.replace(tmpIn.find(':'), 1, " ");
					_IdType a;
					std::string gateName;

					tran >> a >> gateName;

					auto&& gateStrTmp = this->_indexWithGateType[a];
					gateStrTmp = {};

					//this->_indexWithGateType[a] = gateNameUp;
					std::transform(all(gateName),
						std::back_inserter(gateStrTmp),
						[](const char& a) -> char {
							return std::toupper(a);
						}
					);

				}
			}


		}

		inline void run_solution(const std::string& fileName) {
			std::ofstream outFile;
			outFile.exceptions(std::ios::badbit);
			try {
				outFile.open(fileName);
			}
			catch (const std::exception& e) {
				throw e;
			}

			this->__find_Minimum_Height_Tree();
			std::sort(all(this->_minimumHeadIndex));
			this->__to_gate_array();

			// TODO:
			// using for to travel the gate tree head 
			for (const auto& indexOfHead : this->_minimumHeadIndex) {
				// if the head is INPUT type //continue

				outFile << "root=" << indexOfHead << '\n';
				if (this->_indexWithGateType[indexOfHead] == "INPUT") {
					outFile << this->_satisfiableStr[0] << '\n';
					continue;
				}

				// 1 setup the input array range 0 to number of input bits // init in to the nodeOutputStateArr
				auto& getInput = this->_gateToIndexArray.at("INPUT");
				for (std::int32_t numberCnt = 0; numberCnt < pow(2, getInput.size()); numberCnt++) {
					// init 
					this->_nodeOutputStateArr.assign(this->_numberOfRoot, -1);
					auto binaryArr = gateCalculator.to_binary(numberCnt, getInput.size());

					for (size_t i = 0; i < getInput.size(); i++) {
						this->_nodeOutputStateArr[getInput[i]] = binaryArr[i];
					}

					// 1.1 put in to the gate tree calculator
					this->__gate_tree_calculator(indexOfHead, -1);
					// if find the output is 1
					if (this->_nodeOutputStateArr[indexOfHead] == 1) {
						outFile << Solution::_satisfiableStr[1] << '\n';
						// output it the input state 
						outFile << this->__output_to_string(this->_nodeOutputStateArr);
						break;
					}

				}

				if (this->_nodeOutputStateArr[indexOfHead] == 0) {
					outFile << Solution::_satisfiableStr[0] << '\n';
				}

			}
			outFile.close();
		}
	private:
		_IdType _numberOfRoot;

		// save the graph using map 
		std::vector<std::unordered_set<_IdType>> _graph;
		std::vector<std::int32_t> _graphNodeDegree;
		std::vector<std::int16_t> _nodeOutputStateArr;

		// head of the minimum tree // find in the __find_Minimum_Height_tree
		std::vector<_IdType> _minimumHeadIndex;

		// save the index with type gate 
		std::vector<std::string> _indexWithGateType;

		// save the type and the index array 
		std::unordered_map<std::string, std::vector<_IdType>> _gateToIndexArray;

	};

}

#endif // !__GATE_CALCULATOR_H__
