#include "solution.h"

int main() {
	Solution s;
	assert(s.isMatch("aa", "a") == false);
	assert(s.isMatch("aa", "aa") == true);
	assert(s.isMatch("aaa", "aa") == false);
	assert(s.isMatch("aa", "a*") == true);
	assert(s.isMatch("aa", ".*") == true);
	assert(s.isMatch("ab", ".*") == true);
	assert(s.isMatch("aab", "c*a*b") == true);
	assert(s.isMatch("ab", ".*c") == false);
	assert(s.isMatch("aaa", "a.a") == true);
	assert(s.isMatch("aaa", "a*a") == true);
	assert(s.isMatch("aaa", "ab*a*c*a") == true);
	//auto s29 = s.divide(-1060849722, 99958928);

	vector<int> p = { -2,1,-3,4,-1,2,1,-5,4 };
	auto v = s.maxSubArray(p);
	//for (auto i : v) {
	//	for (auto j : i) {
	//		cout << j << " ";
	//	}
	//	cout << endl;
	//}
	vector<vector<int>> p0;
	vector<vector<int>> p1 = { { 1 } };
	vector<vector<int>> p2 = { {1, 2, 3} };
	vector<vector<int>> p3 = { {1}, {2}, {3} };
	vector<vector<int>> p4 = { { 1, 2, 3 }, { 4,5,6 } };
	vector<vector<int>> p5 = { { 1, 2, 3 }, { 4,5,6 }, { 7,8,9 }};
	auto vv = s.spiralOrder(p0);
	vv = s.spiralOrder(p1);
	vv = s.spiralOrder(p2);
	vv = s.spiralOrder(p3);
	vv = s.spiralOrder(p4);
	vv = s.spiralOrder(p5);
	return 0;
}
