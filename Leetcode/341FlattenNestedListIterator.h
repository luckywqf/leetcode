#pragma once
#include "common.h"

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
public:
	NestedInteger(const NestedInteger &ni) {
		_isInteger = ni._isInteger;
		_integer = ni._integer;
		_list = ni._list;
	}

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const {
		return _isInteger;
	}

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
	int getInteger() const {
		return _integer;
	}

	int setInteger(int val) {
		_isInteger = true;
		_integer = val;
	}

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
	const vector<NestedInteger> &getList() const {
		return _list;
	}

	void setList(vector<NestedInteger> list) {
		_isInteger = false;
		_list = list;
	}

private:
	bool _isInteger;
	int _integer;
	vector<NestedInteger> _list;
};

class NestedIterator {
public:
	NestedIterator(vector<NestedInteger> &nestedList) {
		for (int i = nestedList.size() - 1; i >= 0; i--) {
			_stack.push(nestedList[i]);
		}
	}

	int next() {
		int val = _stack.top().getInteger();
		_stack.pop();
		return val;
	}

	bool hasNext() {
		while (!_stack.empty()) {
			auto p = _stack.top();
			if (p.isInteger()) {
				return true;
			}
			_stack.pop();
			for (int i = p.getList().size() - 1; i >= 0; i--) {
				_stack.push(p.getList()[i]);
			}
		}
		return false;
	}

private:
	stack<NestedInteger> _stack;
};

/**
* Your NestedIterator object will be instantiated and called as such:
* NestedIterator i(nestedList);
* while (i.hasNext()) cout << i.next();
*/