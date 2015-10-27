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
	return 0;
}
