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
	//A = [3, 2, 1, 0, 4], return false.
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

	auto out95_0 = s.generateTrees(3);

	TreeNode* in94_0 = nullptr;
	TreeNode* in94_1 = new TreeNode(1);
	TreeNode* in94_2 = new TreeNode(1); in94_2->left = new TreeNode(2);
	TreeNode* in94_3 = new TreeNode(1); in94_3->right = new TreeNode(3);
	TreeNode* in94_4 = new TreeNode(1); in94_4->left = new TreeNode(2);in94_4->right = new TreeNode(3);
	auto out94_0 = s.inorderTraversal(in94_0);
	auto out94_1 = s.inorderTraversal(in94_1);
	auto out94_2 = s.inorderTraversal(in94_2);
	auto out94_3 = s.inorderTraversal(in94_3);
	auto out94_4 = s.inorderTraversal(in94_4);

	TreeNode *in98_0 = nullptr;
	TreeNode *in98_1 = new TreeNode(0);
	in98_1->left = new TreeNode(-1);
	auto out98_0 = s.isValidBST(in98_0);
	auto out98_1 = s.isValidBST(in98_1);

	vector<int> in179_0 = { 66, 8, 33, 1, 72, 93, 51, 88, 59, 86, 66, 39, 71, 82, 95, 77, 44, 75, 91, 4, 52, 28, 
		20, 73, 74, 91, 87, 82, 94, 12, 69, 13, 22, 18, 45, 68, 97, 65, 4, 86, 44, 32, 36, 96, 88, 11, 21, 8, 14, 
		4, 67, 40, 57, 90, 84, 27, 42, 9, 39, 14, 11, 79, 68, 49, 1, 51, 91, 56, 35, 10, 22, 99, 23, 8, 76, 32, 46, 
		40, 37, 43, 89, 83, 91, 40, 94, 43, 62, 74, 8, 42, 99, 7, 34, 67, 39, 55, 22, 87, 73, 91};
	vector<int> in179_1 = { 121, 12 };
	vector<int> in179_2 = { 0, 0 };
	auto out179_0 = s.largestNumber(in179_0);
	auto out179_1 = s.largestNumber(in179_1);
	auto out179_2 = s.largestNumber(in179_2);

	TreeNode *in199_0 = nullptr;
	TreeNode *in199_1 = new TreeNode(1);
	auto out199_0 = s.rightSideView(in199_0);
	auto out199_1 = s.rightSideView(in199_1);

	auto out201_0 = s.rangeBitwiseAnd(5, 7);
	return 0;
}
