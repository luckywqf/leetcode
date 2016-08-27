#pragma once
#include "common.h"

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
  public:
    // Constructor initializes an empty nested list.
	NestedInteger() {}

    // Constructor initializes a single integer.
	NestedInteger(int value) : _num(value) {	  
	}

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const {
		return _data.empty();
	}

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
	int getInteger() const {
		return _num;
	}

    // Set this NestedInteger to hold a single integer.
	void setInteger(int value) {
		_num = value;
	}

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
	void add(const NestedInteger &ni) {
		_data.push_back(ni);
	}

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
	const vector<NestedInteger> &getList() const {
		return _data;
	}

private:
	int _num;
	vector<NestedInteger> _data;
};

class Solution_385 {
public:
	NestedInteger deserialize(string s) {
		NestedInteger result;
		int num = 0;
		int sign = 1;
		bool needNum = false;
		for (int i = 0; i < s.size(); i++) {
			switch (s[i]) {
			case '[':
				if (i == 0) {
					continue;
				}
				result.add(deserialize(s.substr(i + 1)));
				return result;
			case ']':
				if (needNum) {
					result.setInteger(num * sign);
					needNum = false;
					num = 0;
					sign = 1;
				}
				break;
			case ',':
				if (needNum) {
					result.setInteger(num * sign);
					needNum = false;
					num = 0;
					sign = 1;
				}
				break;
			case '-':
				sign = -1;
				break;
			default:
				num *= 10;
				num += s[i] - '0';
				needNum = true;
			}
		}

		if (needNum) {
			result.setInteger(num * sign);
		}
		return result;
	}
};