#pragma once
#pragma GCC optimize(3,"Ofast","inline")
#ifndef __PATH_H__
#define __PATH_H__

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

namespace tools {
	class Path {
	private:
		inline static void __take_out_new_line(std::string& str) {
			str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		}

	private:
		using _MapUnit = std::uint64_t;
		using _PathLink = std::vector<std::vector<_MapUnit>>;
		using _PathVisitWeight = std::vector<std::pair<bool, std::int64_t>>;
		using _PathNameIndexMap = std::unordered_map<std::string, _MapUnit>;
		//
		using _ParentPath = std::vector<_MapUnit>;

	public:
		Path() {
			this->_nameInSizeCnt = _MapUnit();
		}

		~Path() {
			// None
		}


		inline void read(const std::string& file_name) {
			std::ifstream inFile;
			inFile.exceptions(std::ios::badbit);

			// this->_nameInSizeCnt
			try {
				inFile.open(file_name);
			}
			catch (const std::exception& e) {
				throw e;
			}
			std::string dataInBuff;
			std::getline(inFile, dataInBuff);

			Path::__take_out_new_line(dataInBuff);

			this->_nameInSizeCnt = std::stoull(dataInBuff);

			// init 
			this->_wightVisit = _PathVisitWeight(this->_nameInSizeCnt, std::pair<bool, std::int64_t>(false, 0));
			this->_pathMap = _PathLink(this->_nameInSizeCnt, std::vector<_MapUnit>());
			this->_parentPath = _ParentPath(this->_nameInSizeCnt, 0);

			for (std::size_t i = 0; i < this->_nameInSizeCnt; i++) {
				std::getline(inFile, dataInBuff);
				Path::__take_out_new_line(dataInBuff);

				this->_nameMap[dataInBuff] = i;
			}
			// link 

			std::getline(inFile, dataInBuff);

			std::size_t inputLinkCnt = std::stoull(dataInBuff);

			std::vector<std::size_t> buff(3, 0);
			std::stringstream ss;
			for (size_t i = 0; i < inputLinkCnt; i++) {
				ss.str(""); ss.clear();
				std::getline(inFile, dataInBuff);
				Path::__take_out_new_line(dataInBuff);

				ss << dataInBuff;

				for (auto& elm : buff) {
					ss >> elm;
				}
				this->_pathMap[buff[0]].push_back(buff[1]);
				this->_wightVisit[buff[1]].second = buff[2];
				//
				this->_parentPath[buff[1]] = buff[0];
				// init 
				buff.assign(3, 0);
			}

			std::getline(inFile, this->_dirLoc);
			Path::__take_out_new_line(dataInBuff);
			inFile.close();
		}

		// to file // dir from the 
		inline void find_path(const std::string& to_file) {
			std::ofstream outFile;
			outFile.exceptions(std::ios::badbit);

			try { // open file 
				outFile.open(to_file);
			}
			catch (const std::exception& e) {
				throw e;
			}

			// find the address is it exits 
			auto findDirItr = this->_nameMap.find(this->_dirLoc);
			if (findDirItr == this->_nameMap.end()) { // no this path 
				outFile << "-1\n";
				outFile.close();
				return;
			}

			// no open file 
			std::vector<_MapUnit> _stk;
			_stk.push_back(0); // start point 

			outFile << "push 0\n";

			auto dirLocIndex = findDirItr->second;

			while (_stk.empty() || _stk.back() != dirLocIndex) {
				if (_stk.empty()) {
					outFile << "-1\n"; // path not find 
					outFile.close();
					return;
				}

				auto curr = _stk.back();
				_stk.pop_back();
				outFile << "pop " << curr << '\n';

				for (auto& linkPos : this->_pathMap[curr]) {
					if (this->_wightVisit[linkPos].first == false) { // no visit 
						this->_wightVisit[linkPos].first = true;

						_stk.push_back(linkPos);

						outFile << "push " << linkPos << '\n';
					}
				}
			}

			std::int64_t totalStep = std::int64_t();
			std::size_t curr = dirLocIndex;

			while (curr != 0) {
				totalStep += this->_wightVisit[curr].second;
				curr = this->_parentPath[curr];
			}

			outFile << totalStep << '\n';
			outFile.close();
		}

	private:
		_PathLink _pathMap;
		_PathNameIndexMap _nameMap;
		_MapUnit _nameInSizeCnt;
		_PathVisitWeight _wightVisit;
		_ParentPath _parentPath;

		std::string _dirLoc;
	};


}


#endif // !__PATH_H__

