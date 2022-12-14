#ifndef __COMB_CIRCUIT_V2_HPP__
#define __COMB_CIRCUIT_V2_HPP__

/*
Title:Graph critical path
Written By 練鈞揚
This is a code of DW HW 5 Graph critical path
using -std=c++11 version
Date: 3/12/2022
*/

#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>
#include <stdexcept>
#include <algorithm>

namespace tools {
	class Solution {
	private:
		//using the ID Type 
		using _IdType = std::string;
		//first is index , second is length
		using DegreeMap = std::unordered_map<_IdType, std::int32_t>;
		using AdjListMap = std::unordered_map<_IdType, std::vector<_IdType>>;

		// is a struct to save the graph //book 6-63
		struct _Edge {
			_IdType idK, idL; // left K , right L
			std::uint32_t edgeLen;
			std::int32_t priorityK, priorityL;

			_Edge() = default;
			_Edge(const _IdType& idKIn, const _IdType& idLIn, const std::uint32_t& edgeLenIn)
				:idK(idKIn), idL(idLIn), edgeLen(edgeLenIn) {

				std::unordered_map<char*, std::int32_t*> priorityMap = {
					{&idK.front(), &this->priorityK},
					{&idL.front(), &this->priorityL}
				};

				for (auto& elm : priorityMap) {
					switch (*elm.first) {
					case 'I': *elm.second = 0; break;
					case 'G': *elm.second = 1; break;
					case 'O': *elm.second = 2; break;
					default: throw std::invalid_argument("_Edge : error type"); break;
					}
				}
			}
			_Edge& operator=(const _Edge&) = default;

			// for sorting 
			bool operator< (const _Edge& obj) const {
				if (this->idK.front() == obj.idK.front()) {
					auto oriNum = std::stoi(this->idK.substr(1));
					auto objNum = std::stoi(obj.idK.substr(1));

					if (oriNum != objNum) {
						return oriNum < objNum;
					}

					if (this->idL.front() == obj.idL.front()) {
						return (std::stoi(this->idL.substr(1)) < std::stoi(obj.idL.substr(1)));
					}
					return this->priorityL < obj.priorityL;

				}
				return this->priorityK < obj.priorityK;
			}
		};

	private:
		inline void __add_node_in_adj_list(const _IdType& aNodeIndex, const _IdType& bNodeIndex, const std::uint32_t& abLength) {
			// about a insert in adjList
			try {
				this->_adjList.at(aNodeIndex).push_back(bNodeIndex);
			}
			catch (const std::exception& e) {
				this->_adjList.insert({ aNodeIndex,{1,bNodeIndex} });
			}

			//about b insert in adjListInv 
			try {
				this->_adjListInv.at(bNodeIndex).push_back(aNodeIndex);
			}
			catch (const std::exception& e) {
				this->_adjListInv.insert({ bNodeIndex,{1,aNodeIndex} });
			}
			this->_edgeTable.insert({ {aNodeIndex + bNodeIndex, abLength}, {bNodeIndex + aNodeIndex, abLength} });

		}

		inline void __add_node_inDegree(const _IdType& aNodeIndex, const _IdType& bNodeIndex) {
			// add in the inDegree 
			try {
				this->_inDegree.at(bNodeIndex)++;
			}
			catch (const std::exception& e) {
				this->_inDegree.insert({ bNodeIndex,1 });
			}

			// add in the inDegreeInv 
			try {
				this->_inDegreeInv.at(aNodeIndex)++;
			}
			catch (const std::exception& e) {
				this->_inDegreeInv.insert({ aNodeIndex,1 });
			}
		}

		// using in the run solution 

		// https://www.youtube.com/watch?v=Yh5o_PSK9to
		static std::deque<_IdType> __topological_sort(const AdjListMap& adjMap, const DegreeMap& inDegreeIn) {
			// make inDegree map 
			std::unordered_map<_IdType, std::int32_t> inDegree(inDegreeIn);
			std::deque<_IdType> res, pq;

			for (const auto& elm : inDegree) {
				if (elm.second == 0) {
					pq.push_back(elm.first);
				}
			}
			while (!pq.empty()) {
				res.push_back(pq.front());
				pq.pop_front();
				try {
					for (const auto& it : adjMap.at(res.back())) {
						if (--inDegree.at(it) == 0) {
							pq.push_back(it);
						}
					}
				}
				catch (const std::exception& e) { /*None*/ }
			}
			return res;
		}

		inline std::deque<std::string> __make_critical_path_str() const {
			//std::deque<std::deque<std::string>> res(1, std::deque<std::string>());
			std::deque<std::string> resArr;

			bool isFindIt = false;

			for (const auto& itemEdge : this->_criticalPath) {
				isFindIt = false;
				auto _size = resArr.size();
				// run the resArr
				for (auto i = 0; i < _size; i++) {

					// find the last substring is same
					if (resArr[i].substr(resArr[i].rfind(" ") + 1) == itemEdge.idK) {
						resArr[i] += " " + itemEdge.idL;
						isFindIt = true;
						continue;
					}

					// find the substring have same
					auto findItr = resArr[i].find(itemEdge.idK);
					if (findItr != std::string::npos) {
						resArr.push_back(
							{ resArr[i].substr(0, findItr + itemEdge.idK.size()) + " " + itemEdge.idL }
						);
						isFindIt = true;
					}
				}
				// if is not find and push_back a new string
				if (isFindIt == false) { resArr.push_back(itemEdge.idK + " " + itemEdge.idL); }
			}

			return resArr;
		}

	public:
		Solution() = default;
		~Solution() = default;

		//read file function 
		void read_file(const std::string& fileName) {
			std::ifstream inFile;
			std::stringstream ss, transformSS;
			inFile.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

			try { inFile.open(fileName);  ss << inFile.rdbuf(); inFile.close(); }
			catch (const std::exception& e) { inFile.close(); throw e; }

			// TODO:
			// mapping the type to the index 
			std::string tempIn;
			while (std::getline(ss, tempIn, '\n')) {
				transformSS.str(""); transformSS.clear();
				transformSS << tempIn;

				std::string aIndex, bIndex;
				std::uint32_t lengthAB;

				transformSS >> aIndex >> bIndex >> lengthAB;

				this->__add_node_in_adj_list(aIndex, bIndex, lengthAB);

				this->_inDegree.insert({ aIndex,0 });
				this->_inDegreeInv.insert({ bIndex,0 });

				this->__add_node_inDegree(aIndex, bIndex);

				this->_dataEvents.push_back({ aIndex, bIndex, lengthAB });

				this->_setOfNode.insert({ aIndex,bIndex });
			}
			this->_eventNumber = this->_dataEvents.size();
			this->_nodeNumber = this->_setOfNode.size();
		}

		void run_solution(const std::string& fileName) {
			// run topological sort in adj list // save in topological sort list 

			auto topologicalSortList = Solution::__topological_sort(this->_adjList, this->_inDegree);

			if (topologicalSortList.empty()) { // check is it have empty 
				throw std::invalid_argument("Graph have circuit path");
			}

			auto topologicalSortListInv = Solution::__topological_sort(this->_adjListInv, this->_inDegreeInv);

			if (topologicalSortListInv.empty()) {
				throw std::invalid_argument("Inv Graph have circuit path");
			}

			std::int64_t nodeMaxNum = 0;

			// run ee solution 
			std::unordered_map<_IdType, std::int64_t> eeMap;
			for (const auto& i : topologicalSortList) { eeMap.insert({ i,0 }); }

			// like pop stack 
			for (const auto& popItem : topologicalSortList) {
				try {
					for (const auto& item : this->_adjList.at(popItem)) {
						eeMap.at(item) = std::max(eeMap.at(item), eeMap.at(popItem) + this->_edgeTable.at(popItem + item));
						nodeMaxNum = std::max(nodeMaxNum, eeMap.at(item));
					}
				}
				catch (const std::exception& e) { /*None*/ }
			}

			// run le solution
			std::unordered_map<_IdType, std::int64_t> leMap;
			for (const auto& i : topologicalSortListInv) { leMap.insert({ i,nodeMaxNum }); }

			for (const auto& popItemInv : topologicalSortListInv) {
				try {
					for (const auto& item : this->_adjListInv.at(popItemInv)) {
						leMap.at(item) = std::min(leMap.at(item), leMap.at(popItemInv) - this->_edgeTable.at(popItemInv + item));
					}
				}
				catch (const std::exception& e) { /*None*/ }
			}

			std::stringstream ssOut;

			// output the Critical Activities 
			try {
				for (auto& dataEvent : this->_dataEvents) {
					auto eePart = eeMap.at(dataEvent.idK);
					auto lePart = leMap.at(dataEvent.idL) - dataEvent.edgeLen;

					ssOut << dataEvent.idK << ' ' << dataEvent.idL << ' '
						<< eePart << ' ' << lePart << ' '
						<< lePart - eePart << ' '
						<< (eePart == lePart ? 'Y' : 'N')
						<< '\n';

					if (eePart == lePart) {
						this->_criticalPath.push_back(dataEvent);
					}
				}
			}
			catch (const std::exception& e) { throw e; }

			// get the critical paths latency 
			ssOut << "max latency: " << nodeMaxNum << '\n';
			//sort the critical Path in the Edge 
			std::sort(this->_criticalPath.begin(), this->_criticalPath.end());

			//print the critical path 
			auto criticalPathList = this->__make_critical_path_str();
			ssOut << "critical paths:\n";
			for (const auto& partOfStr : criticalPathList) {
				ssOut << partOfStr << '\n';
			}

			std::ofstream outFile;
			outFile.exceptions(std::ios::badbit);

			try { outFile.open(fileName); outFile << ssOut.rdbuf(); outFile.close(); }
			catch (const std::exception& e) { outFile.close(); throw e; }
		}

	private:
		std::size_t _nodeNumber, // about the node number 
			_eventNumber; // about the event between 2 node 
		std::unordered_set<_IdType> _setOfNode;

		//adj list // using for dp 
		AdjListMap _adjList, // left to right 
			_adjListInv; // right to lefts 

		DegreeMap _inDegree, // left to right inDegree 
			_inDegreeInv; //  right to left inDegree 

		// event map // save left and right length for find e and l // book 6-63
		std::vector<_Edge> _dataEvents,
			_criticalPath; // save the critical path 

		//save the edge between two node (key = p1 + p2)
		std::unordered_map<std::string, std::uint32_t> _edgeTable;

	}solutionTools;


}

#endif // !__COMB_CIRCUIT_V2_HPP__