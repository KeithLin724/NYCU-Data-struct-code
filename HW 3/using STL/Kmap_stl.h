#ifndef __KMAP_STL_H__
#define __KMAP_STL_H__

/*
Title:DS HW 3 K map STL version
Written By KYLiN
This is a code for HW 3 example
using std=c++11 version
Date: 4/11/2022
*/


#include <list>
#include <vector>
#include <sstream>
#include <fstream>
#include <bitset>
#include <algorithm>

namespace tools {

	class Bin {
	public:
		static constexpr auto dontCare = '-';
	private:
		Bin(const std::string& bin, const std::uint32_t& bitSize, const std::int32_t& oneBitsNumber)
			:_bits(bin), _bitsSize(bitSize), _oneBitsNumber(oneBitsNumber) {

		}
	public:
		Bin()
			:_bitsSize(std::uint32_t()), _oneBitsNumber(std::uint32_t()) {

		}
		Bin(std::int32_t& number, std::int32_t bitSize) {
			if (bitSize > 16) {
				throw std::invalid_argument("bit over 16");
			}

			this->_bitsSize = bitSize;
			// init the arr 

			auto tmpStr = std::bitset<16>(number).to_string();
			auto strItr = std::next(tmpStr.begin(), 16 - this->_bitsSize);

			this->_bits.assign(strItr, tmpStr.end());
			this->_oneBitsNumber = std::count(this->_bits.begin(), this->_bits.end(), '1');

		}

		~Bin() {
			// None
		}

		inline std::uint32_t get_oneBitsNumber() const {
			return this->_oneBitsNumber;
		}

		bool operator ==(const Bin& objBin) {
			if (this->_bitsSize != objBin._bitsSize || this->_oneBitsNumber != objBin._oneBitsNumber) {
				return false;
			}
			return this->_bits == objBin._bits;
		}

		inline static std::pair<bool, Bin> combine(const Bin& obj1, const Bin& obj2) { // same format 
			if (obj1._bitsSize != obj2._bitsSize) {
				return { false, Bin() };
			}

			std::uint32_t notSameBitsCnt = 0, dontCareIndex = 0;
			std::string copyRes = obj1._bits;  // copy array

			for (std::uint32_t i = 0; i < obj1._bits.size(); i++) {
				if (obj1._bits[i] != obj2._bits[i]) {
					notSameBitsCnt++;
					dontCareIndex = i;
				}

				if (notSameBitsCnt > 1) {
					return { false, Bin() };
				}
			}

			copyRes[dontCareIndex] = Bin::dontCare;

			return { true, Bin(copyRes, obj1._bitsSize, obj1._oneBitsNumber) };
		}
		std::string to_string() const {
			return this->_bits;
		}

	private:
		std::string _bits;
		std::uint32_t _bitsSize;
		std::uint32_t _oneBitsNumber;
	};

	struct Node {
		bool havePair;
		Bin bin;
		Node(const Bin& bin = Bin(), const bool& havePair = false)
			:bin(bin), havePair(havePair) {

		}
		bool operator == (const Node& obj) {
			return this->bin == obj.bin;
		}
	};

	class Kmap {
	private:
		const std::vector<std::string> _StateStr = { "Initial Grouping" , "Combination " };

	private:
		inline static std::string __list_to_string(const std::list<Node>& ls) {
			std::string res;
			for (auto listItr = ls.begin(); listItr != ls.end(); listItr++) {
				res += listItr->bin.to_string();

				if (std::next(listItr, 1) != ls.end()) {
					res += ", ";
				}

			}
			return res;
		}
	public:
		Kmap()
			:_bitsNumber(std::uint32_t()) {

		}
		~Kmap() {

		}

		void read_file(const std::string& fileName) {
			std::ifstream inFile;
			inFile.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

			try {
				inFile.open(fileName);
			}
			catch (const std::exception& e) {
				throw e;
			}

			// read file 
			std::stringstream ss, toNum;
			ss << inFile.rdbuf();
			ss >> this->_bitsNumber;

			if (this->_bitsNumber > 16) {
				throw std::invalid_argument("out of the array buffer");
			}

			this->_termArr.assign(this->_bitsNumber + 1, std::list<Node>());

			std::string numberBuffStr;
			std::int32_t numberBuff;

			while (std::getline(ss, numberBuffStr, ',')) {
				toNum.str(""); toNum.clear();
				toNum << numberBuffStr;

				toNum >> numberBuff;

				auto tmpBin = Bin(numberBuff, this->_bitsNumber);
				this->_termArr[tmpBin.get_oneBitsNumber()].push_back(tmpBin);
			}

			inFile.close();
		}

		inline void output_Term_to_file(std::ofstream& outfile, const std::uint32_t& step, const std::int32_t& baseLine) const {
			std::int32_t printBitRange = baseLine;
			for (; printBitRange >= 0; printBitRange--) {
				if (this->_termArr[printBitRange].empty() == false) {
					break;
				}
			}

			if (printBitRange == -1) {
				return;
			}

			outfile << Kmap::_StateStr[(step > 0)];
			if (step > 0) {
				outfile << step;
			}
			outfile << '\n';

			for (std::size_t i = 0; i <= printBitRange; i++) {
				outfile << i << ":";
				if (this->_termArr[i].empty() == false) {
					outfile << " ";
					outfile << Kmap::__list_to_string(this->_termArr[i]);
				}
				outfile << '\n';
			}

		}

		inline void run_Quine_McCluskey_to_file(const std::string& fileName) {

			std::ofstream outFile;
			outFile.exceptions(std::ios::badbit);

			try {
				outFile.open(fileName);
			}
			catch (const std::exception& e) {
				throw e;
			}

			std::uint32_t step = 0;
			this->output_Term_to_file(outFile, 0, this->_bitsNumber);

			// about the 
			for (std::int32_t baseLine = this->_bitsNumber, step = 1; baseLine >= 0; baseLine--, step++) {
				if (this->_termArr[baseLine].empty()) { // if the list is empty 
					step--;
					continue;
				}
				for (std::int32_t runLineIndex = 0; runLineIndex < baseLine; runLineIndex++) {
					// TODO 
					// check runLineIndex -> do continue if it is empty  
					if (this->_termArr[runLineIndex].empty()) {
						continue;
					}

					// if runLineIndex + 1 is empty -> pop it or save it to prime list if it is not use  (runLineIndex)
					if (this->_termArr[runLineIndex + 1].empty()) {
						while (!this->_termArr[runLineIndex].empty()) {
							Node res = this->_termArr[runLineIndex].front();
							this->_termArr[runLineIndex].pop_front();

							if (res.havePair == false) {
								this->_primeList.push_back(res.bin);
							}
						}

						continue;
					}

					// 1 runLineIndex combine runLineIndex +1 
					std::list<Node> newListTmp;
					for (auto& line1Elm : this->_termArr[runLineIndex]) {

						for (auto& line2Elm : this->_termArr[runLineIndex + 1]) {
							auto res = Bin::combine(line1Elm.bin, line2Elm.bin);

							if (res.first == true) {
								// 1.1add new in the runLineIndex 
								auto findItr = std::find(newListTmp.begin(), newListTmp.end(), Node(res.second, false));
								if (findItr == newListTmp.end()) {
									newListTmp.push_back(res.second);
								}

								line1Elm.havePair = true;
								line2Elm.havePair = true;
							}
						}

					}

					// 2 pop front of the runLineIndex 
					while (!this->_termArr[runLineIndex].empty()) {
						Node res = this->_termArr[runLineIndex].front();
						this->_termArr[runLineIndex].pop_front();

						if (!res.havePair) {
							this->_primeList.push_back(res.bin);
						}
					}

					//
					this->_termArr[runLineIndex] = newListTmp;
				}
				// TODO 
				// 0 if it is empty to continue
				if (this->_termArr[baseLine].empty()) {
					this->output_Term_to_file(outFile, step, baseLine);
					continue;
				}

				// here is end of the base line 
				// pop it or save it to prime list if it is not use 
				while (!this->_termArr[baseLine].empty()) {
					Node res = this->_termArr[baseLine].front();
					this->_termArr[baseLine].pop_front();

					if (res.havePair == false) {
						this->_primeList.push_back(res.bin);
					}
				}

				// print it out (to file or cout)
				this->output_Term_to_file(outFile, step, baseLine);
			}
			outFile << "Prime Implicants\n";

			for (auto listItr = this->_primeList.begin(); listItr != this->_primeList.end(); listItr++) {
				outFile << listItr->to_string();

				if (std::next(listItr, 1) != this->_primeList.end()) {
					outFile << ", ";
				}

			}

			outFile << '\n';
			outFile.close();
		}

	private:
		std::uint32_t _bitsNumber;
		std::vector<std::list<Node>> _termArr;
		std::list<Bin> _primeList;
	};
}

#endif // !__KMAP_STL_H__
