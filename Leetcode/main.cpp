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
	vector<vector<char>> in = { {'1','0','1','1','0','1','1'} };
	auto v = s.numIslands(in);
	cout << v << endl;

	//A = [2, 3, 1, 1, 4], return true.

	//	A = [3, 2, 1, 0, 4], return false.
	vector<int> in55_1 = { 2, 3, 1, 1, 4 };
	vector<int> in55_2 = { 3, 2, 1, 0, 4 };
	auto out55_1 = s.canJump(in55_1);
	auto out55_2 = s.canJump(in55_2);
	auto out59 = s.generateMatrix(3);

	auto out60 = s.getPermutation(4, 4);

	ListNode *head = new ListNode(1);
	head->next = new ListNode(2);
	auto out61 = s.rotateRight(nullptr, 0);

	auto out69 = s.mySqrt(2147395599);
	auto out71_0 = s.simplifyPath("/");
	auto out71_1 = s.simplifyPath("/..");
	auto out71_2 = s.simplifyPath("/...a/b");
	auto out71_3 = s.simplifyPath("/../");
	auto out71_4 = s.simplifyPath("/a/./b//d/../../c/");
	auto out71_5 = s.simplifyPath("/home/");
	auto out71_6 = s.simplifyPath("/.");

	auto out77_0 = s.combine(4, 5);

	vector<int> in78_0 = {1};
	auto out78_0 = s.subsets(in78_0);

	auto out93_0 = s.restoreIpAddresses("25525511135");
	auto out93_1 = s.restoreIpAddresses("0279245587303");
	auto out93_2 = s.restoreIpAddresses("0000");
	auto out93_3 = s.restoreIpAddresses("010010"); //["0.10.0.10","0.100.1.0"]

	auto out89_0 = s.grayCode(0);
	auto out89_1 = s.grayCode(1);
	auto out89_2 = s.grayCode(2);
	auto out89_3 = s.grayCode(3);

	TreeNode *in199_0 = nullptr;
	TreeNode *in199_1 = new TreeNode(1);
	auto out199_0 = s.rightSideView(in199_0);
	auto out199_1 = s.rightSideView(in199_1);

	auto out201_0 = s.rangeBitwiseAnd(5, 7);
	return 0;
}
