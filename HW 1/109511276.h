#pragma once

#ifndef __POLYDIV_H__
#define __POLYDIV_H__

/*
Title:Data Struct HW 1
Written By ½m¶v´­
This is a code for DS HW1
using std=c++14 version
Date: 29/9/2022
*/

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

#define all(c) c.begin(), c.end()

namespace tools {
	using ArrType = std::vector<int>;

	inline std::string ArrType_to_string(const ArrType& obj) {
		std::string res;

		for (const auto& elm : obj) {
			res += std::to_string(elm) + " ";
		}

		return res;
	}

	inline ArrType take_out_front_zero(const ArrType& obj) {
		size_t cnt(0);

		for (; cnt < obj.size(); cnt++) {
			if (obj[cnt] != 0) {
				break;
			}
		}

		return ArrType(obj.begin() + cnt, obj.end());

	}

	inline std::pair<ArrType, ArrType> div(const ArrType& obj1 , const ArrType& obj2) {
		if (obj2.size() == 1 && obj2.front() == 0) { // 
			throw std::invalid_argument("can't div 0");
		}

		if (obj1.empty()) { // 0 / n 
			return { ArrType(1, 0), ArrType(1, 0) };
		}

		if (obj1.size() < obj2.size()) { // case one 
			return { ArrType(1, 0), ArrType(obj2) };
		}

		ArrType copyObj1(obj1);
		auto _size = copyObj1.size();

		auto remItr = copyObj1.begin();

		for (; _size >= obj2.size(); _size--, remItr++) {
			*remItr /= obj2.front();

			if (*remItr != 0) {
				for (size_t i(1); i < obj2.size(); i++) {
					*(remItr + i) -= *remItr * obj2[i];
				}
			}

		}

		if (remItr == copyObj1.end()) {
			return { ArrType(copyObj1) , ArrType(1,0) };
		}

		std::pair<ArrType, ArrType> res = { ArrType(copyObj1.begin(), remItr)  ,ArrType(remItr, copyObj1.end()) };

		bool allZero = std::all_of(all(res.first),
			[](const int32_t& elm) {
				return elm == 0;
			}
		);

		if (res.first.size() != 1) {
			res.first = (allZero == 1 ? ArrType(1, 0) : take_out_front_zero(res.first));
		}

		allZero = std::all_of(all(res.second),
			[](const int32_t& elm) {
				return elm == 0; 
			}
		);

		if (res.second.size() != 1 ) {
			res.second = (allZero == 1 ? ArrType(1,0): take_out_front_zero(res.second));
		}
		
		return res;

	}

	

}

#endif // !__POLYDIV_H__