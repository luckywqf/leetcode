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

	vector<int> val = { 5,5,3,5,1,-5,1,-2 };
	auto v = s.fourSum(val, 4);

	ListNode l(1), *p = &l;
	for (int i = 2; i < 2; i++) {
		p->next = new ListNode(i);
		p = p->next;
	}
	auto s24 = s.swapPairs(&l);


	//auto s29 = s.divide(-1060849722, 99958928);

	vector<int> s46 = { 4,2 };
	//auto r46 = s.permute(s46);
	//for (auto v : r46) {
	//	for (auto i : v) {
	//		cout << i << " ";
	//	}
	//	cout << endl;
	//}

	s.nextPermutation(s46);
	return 0;
}
