#ifndef __KMAP_V4_H__
#define __KMAP_V4_H__

/*
Title:DS HW 3 K map
Written By 練鈞揚
this is a code for DS HW 3 K map
using std=c++11 version
Date: 3/11/2022
*/

#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>

namespace tools {

	class Binary { // in a struct of the Binary 
	public:
		static constexpr auto dontCare = '-';

	private:
		Binary(const std::string& bitArr, const std::uint32_t& bitSize, const std::uint32_t& oneBitNumber) {
			this->_oneBitNumber = oneBitNumber;
			this->_bitsSize = bitSize;
			this->_bits = bitArr;
		}

	public:
		Binary() {
			this->_oneBitNumber = 0;
			this->_bitsSize = 0;
			this->_bits = ""; // init the array; 
		}

		Binary(const std::int32_t& number, const std::int32_t& bits) {

			this->_oneBitNumber = 0;
			this->_bitsSize = bits;
			this->_bits.assign(this->_bitsSize, ' ');

			std::int32_t val = 0;
			for (std::int32_t i = this->_bitsSize - 1; i >= 0; i--) { // to binary array 
				val = ((number >> i) & 1);
				this->_bits[this->_bitsSize - 1 - i] = val + '0'; // to char 
				this->_oneBitNumber += val;
			}
		}

		Binary(const Binary& obj) { // deep copy 
			this->_bitsSize = obj._bitsSize;
			this->_oneBitNumber = obj._oneBitNumber;

			this->_bits = obj._bits;// copy array 
		}

		inline std::string to_string() const {
			return this->_bits;
		}

		inline std::uint32_t get_oneBitsNumber() const {
			return this->_oneBitNumber;
		}

		// first is it success // second is Binary 
		inline static std::pair<bool, Binary> combine(const Binary& obj1, const Binary& obj2) { // same format 
			if (obj1._bitsSize != obj2._bitsSize) {
				return { false, Binary() };
			}

			auto size = obj1._bitsSize;
			std::uint32_t notSameBitsCnt = 0, dontCareIndex = 0;
			std::string copyRes = obj1._bits;

			for (std::uint32_t i(0); i < size; i++) {
				if (obj1._bits[i] != obj2._bits[i]) {
					notSameBitsCnt++;
					dontCareIndex = i;
				}

				if (notSameBitsCnt > 1) {
					return { false, Binary() };
				}
			}

			copyRes[dontCareIndex] = Binary::dontCare;

			return { true, Binary(copyRes, obj1._bitsSize, obj1._oneBitNumber) };
		}

		// is same  
		inline bool operator== (const Binary& obj) const {
			if ((this->_bitsSize != obj._bitsSize) || (this->_oneBitNumber != obj._oneBitNumber)) {
				return false;
			}

			return this->_bits == obj._bits;
		}

	private:
		std::string _bits;
		std::uint32_t _oneBitNumber;
		std::uint32_t _bitsSize;
	};


	struct NodeBinary { // Node of the bin 
		Binary bin;
		NodeBinary* prev, * next;

		// using for the k-map 
		bool have_pair;

		// construct 
		NodeBinary(const Binary& bin = Binary(), NodeBinary* prev = nullptr, NodeBinary* next = nullptr)
			: bin(bin), prev(prev), next(next), have_pair(false) {

		}
	};

	class LinkedListBin { // double linked list of the bin 
	public:
		LinkedListBin()
			:_head(nullptr), _tail(nullptr), _size(0), // linked list 
			_newHead(nullptr) { // for k-map 

		}

		LinkedListBin(const LinkedListBin& obj) { // deep copy 
			this->_head = nullptr;
			this->_tail = nullptr;
			this->_newHead = nullptr;
			this->_size = 0;

			if (obj._head == nullptr) {
				return;
			}

			NodeBinary* cpyList = obj._head;
			this->_head = new NodeBinary(cpyList->bin, nullptr, nullptr);
			if (obj._head == obj._newHead) {
				this->_newHead = this->_head;
			}
			NodeBinary* curr = this->_head;

			while (cpyList->next != nullptr) {
				cpyList = cpyList->next;

				curr->next = new NodeBinary(cpyList->bin, curr, nullptr);

				curr = curr->next; // move 

				if (cpyList == obj._newHead) {
					this->_newHead = curr; // copy 
				}

			}

			this->_tail = curr;
			if (cpyList == obj._newHead) {
				this->_newHead = this->_tail;
			}

			this->_size = obj._size;


		}

		~LinkedListBin() {
			if (this->_head == nullptr) {
				return;
			}

			while (this->_head->next != nullptr) {
				this->_head = this->_head->next;

				// delete 
				delete this->_head->prev;
				this->_head->prev = nullptr;
			}

			delete this->_head;
			this->_head = nullptr;
			this->_tail = nullptr;
			this->_size = 0;
		}

		inline bool empty() const {
			return (this->_head == nullptr);
		}

		inline std::uint32_t get_size() const {
			return this->_size;
		}

		inline void push_front(const Binary& data) {
			if (this->_head == nullptr) { // no data 
				this->_head = new NodeBinary(data);
				this->_tail = this->_head;
				this->_size++;
				return;
			}

			this->_head->prev = new NodeBinary(data, nullptr, this->_head);
			this->_head = this->_head->prev;
			this->_size++;
		}

		inline void push_back(const Binary& data) {
			if (this->_head == nullptr) {
				this->push_front(data);
				return;
			}

			this->_tail->next = new NodeBinary(data, this->_tail, nullptr);
			this->_tail = this->_tail->next;
			this->_size++;
		}

		// peek 

		inline Binary peek_front() const {
			if (this->_head == nullptr) {
				throw std::invalid_argument("the list is empty");
			}

			return this->_head->bin;
		}

		inline std::pair<Binary, bool> peek_front_with_have_pair() const {
			if (this->_head == nullptr) {
				throw std::invalid_argument("the list is empty");
			}

			return { this->_head->bin, this->_head->have_pair };
		}

		inline Binary peek_back() const {
			if (this->_head == nullptr) {
				throw std::invalid_argument("the list is empty");
			}

			return this->_tail->bin;
		}

		inline void pop_front() {
			if (this->_head == nullptr) {
				return;
			}

			if (this->_head->next == nullptr) {
				delete this->_head;
				this->_head = nullptr;
				this->_size--;
				return;
			}

			this->_head = this->_head->next;
			delete this->_head->prev;
			this->_head->prev = nullptr;
			this->_size--;
		}

		inline void pop_back() {
			if (this->_head == nullptr) {
				return;
			}

			if (this->_tail->prev == nullptr) {
				delete this->_tail;
				this->_tail = nullptr;
				this->_size--;
				return;
			}

			this->_tail = this->_tail->prev;
			delete this->_tail->next;
			this->_tail->next = nullptr;
			this->_size--;
		}

		inline std::string to_string() const {
			NodeBinary* curr = this->_head;

			if (this->_head == nullptr) {
				return std::string();
			}

			std::string res;

			for (; curr->next != nullptr; curr = curr->next) {
				res += curr->bin.to_string() + ", ";
			}

			return res + curr->bin.to_string();
		}

		// for k-map algorithm

		// get the ptr 
		// don't delete node and change the size 
		inline std::pair<NodeBinary*, const std::uint32_t> get_data() {
			return { this->_head, this->_size };
		}

		// true if it can pop 
		inline bool can_pop_it() const {
			return !(this->_head == nullptr || this->_newHead == nullptr);
		}

		// first is the res if can pop, second is the is_used 
		inline std::pair<Binary, bool> pop_it() {
			if (this->can_pop_it() == false) { // empty list or empty new list 
				return { Binary(), false };
			}

			std::pair<Binary, bool> res = { this->_head->bin,this->_head->have_pair };

			this->pop_front();
			if (this->_head == this->_newHead) { // to next round or finish the round 
				this->_newHead = nullptr;
			}

			return res;
		}

		// push in linked list after newHead node 
		inline void push_in(const Binary& obj) {
			if (this->_newHead == nullptr) { // init the new head node 
				this->_newHead = this->_tail;
				this->push_back(obj);
				this->_newHead = this->_newHead->next;

				return;
			}
			// TODO
			if (this->_newHead->bin == obj) { // same of the newHead
				return;
			}

			// is in // move to the last one
			for (NodeBinary* isInCurr = this->_newHead; isInCurr != nullptr; isInCurr = isInCurr->next) {
				if (obj == isInCurr->bin) { // is same to skip 
					return;
				}
			}

			// last one 
			this->push_back(obj);

		}

	private: // for k-map 
		NodeBinary* _newHead; // 

	private:
		NodeBinary* _head, * _tail;  // head tail 
		std::size_t _size;
	};


	////////////////////////////////////////////////////
	// algorithm 
	class Kmap {

	private:
		const std::string _displayStateStr[2] = { "Initial Grouping" , "Combination " };

	public:
		Kmap() {
			this->_bitsNumber = 0;
			this->_groupArray = nullptr;
		}
		~Kmap() {
			delete[] this->_groupArray;
		}

		inline void read_file(const std::string& fileName) {
			std::ifstream inFile;
			inFile.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

			try {
				inFile.open(fileName);
			}
			catch (const std::exception& e) {
				throw e;
			}

			// read file 
			std::stringstream ss;
			ss << inFile.rdbuf();
			ss >> this->_bitsNumber;

			// new a array and fill the array 
			this->_groupArray = new LinkedListBin[this->_bitsNumber + 1];
			std::fill(this->_groupArray, this->_groupArray + this->_bitsNumber + 1, LinkedListBin());

			std::int32_t numberBuff;
			char opBuff;

			while (!ss.eof()) {
				ss >> numberBuff >> opBuff;

				auto tmpBin = Binary(numberBuff, this->_bitsNumber);

				this->_groupArray[tmpBin.get_oneBitsNumber()].push_back(tmpBin);
			}

			inFile.close();

		}

		// success for the output to file 
		inline void output_Term_to_file(std::ofstream& outfile, const std::uint32_t& step, const std::int32_t& baseLine) const {
			std::int32_t printBitRange = baseLine;
			for (; printBitRange >= 0; printBitRange--) {
				if (!this->_groupArray[printBitRange].empty()) {
					break;
				}
			}

			if (printBitRange == -1) {
				return;
			}

			outfile << Kmap::_displayStateStr[(step > 0)];
			if (step > 0) {
				outfile << step;
			}
			outfile << '\n';

			for (std::size_t i(0); i <= printBitRange; i++) {
				outfile << i << ":";
				if (!this->_groupArray[i].empty()) {
					outfile << " " << this->_groupArray[i].to_string();
				}
				outfile << '\n';
			}

		}

		// algorithm 
		// Quine_McCluskey to file 
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
				if (this->_groupArray[baseLine].empty()) { // if the list is empty 
					step--;
					continue;
				}
				for (std::int32_t runLineIndex = 0; runLineIndex < baseLine; runLineIndex++) {
					// TODO 
					// check runLineIndex -> do continue if it is empty  
					if (this->_groupArray[runLineIndex].empty()) {
						continue;
					}

					// if runLineIndex + 1 is empty -> pop it or save it to prime list if it is not use  (runLineIndex)
					if (this->_groupArray[runLineIndex + 1].empty()) {// NOTE: check the runLineIndex is it out of range // for DEBUG 
						std::pair<Binary, bool> res;
						while (!this->_groupArray[runLineIndex].empty()) {
							res = this->_groupArray[runLineIndex].peek_front_with_have_pair();
							this->_groupArray[runLineIndex].pop_front();
							if (!res.second) {
								this->_primeBinList.push_back(res.first);
							}
						}
						continue;
					}

					// 1 runLineIndex combine runLineIndex +1 
					auto line1 = this->_groupArray[runLineIndex].get_data();
					auto line2 = this->_groupArray[runLineIndex + 1].get_data();

					NodeBinary* line1Curr = line1.first, * line2Curr = line2.first;

					for (std::uint32_t i = 0; i < line1.second; i++, line1Curr = line1Curr->next) {
						line2Curr = line2.first; // reset 

						for (std::uint32_t j = 0; j < line2.second; j++, line2Curr = line2Curr->next) {
							auto res = Binary::combine(line1Curr->bin, line2Curr->bin);
							if (res.first) {
								// 1.1add new in the runLineIndex 
								this->_groupArray[runLineIndex].push_in(res.second);
								line1Curr->have_pair = true;
								line2Curr->have_pair = true;
							}
						}

					}

					// 2 pop front of the runLineIndex 
					std::pair<Binary, bool> res;
					while (this->_groupArray[runLineIndex].can_pop_it()) {
						res = this->_groupArray[runLineIndex].pop_it();
						// 2.2 if the number is not use or combine put it in to prime List 
						if (!res.second) {
							this->_primeBinList.push_back(res.first);
						}
					}

				}
				// TODO 
				// 0 if it is empty to continue
				if (this->_groupArray[baseLine].empty()) {
					this->output_Term_to_file(outFile, step, baseLine);
					continue;
				}

				// here is end of the base line 
				// pop it or save it to prime list if it is not use 
				std::pair<Binary, bool> res;
				while (this->_groupArray[baseLine].empty() == false) {
					res = this->_groupArray[baseLine].peek_front_with_have_pair();
					this->_groupArray[baseLine].pop_front();

					// 2.2 if the number is not use or combine put it in to prime List 
					if (!res.second) {
						this->_primeBinList.push_back(res.first);
					}
				}

				// print it out (to file or cout)
				this->output_Term_to_file(outFile, step, baseLine);
			}
			outFile << "Prime Implicants\n";
			outFile << this->_primeBinList.to_string() << '\n';

			outFile.close();
		}

	private:
		uint32_t _bitsNumber;
		LinkedListBin* _groupArray;
		LinkedListBin _primeBinList;
	};

}

#endif // !__KMAP_V4_H__
