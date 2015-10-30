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

	//[1, 3, 5, 6], 5 ¡ú 2
	//[1, 3, 5, 6], 2 ¡ú 1
	//[1, 3, 5, 6], 7 ¡ú 4
	//[1, 3, 5, 6], 0 ¡ú 0
	vector<int> v = { 1, 3, 5, 6};
	auto r = s.searchInsert(v, 0);
	return 0;
}
