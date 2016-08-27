#pragma once
#include "common.h"
#include<ctime>

class Solution_384 {
public:
	Solution_384(vector<int> nums) {
		_data = nums;
	}

	/** Resets the array to its original configuration and return it. */
	vector<int> reset() {
		return _data;
	}

	/** Returns a random shuffling of the array. */
	vector<int> shuffle() {
		srand(time(NULL));
		vector<int> result = _data;
		for (int i = 0; i < result.size() - 1; i++) {
			int index = rand() % result.size() - i;
			swap(result[i], result[index + i]);
		}
		return result;
	}

private:
	vector<int> _data;
};