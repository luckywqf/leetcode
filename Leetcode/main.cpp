#include "solution.h"
#include "384ShuffleArray.h"
#include "385MiniParser.h"


int main(int argc, char *argv[]) {
	Solution s;

	auto out6_0 = s.convert("PAYPALISHIRING", 3);
	auto out6_1 = s.convert("PAYPALISHIRING", 4);

	auto out10_0 = s.isMatch("aa", "a");    //false
	auto out10_1 = s.isMatch("aa", "aa");    //true
	auto out10_2 = s.isMatch("aaa", "aa");    //false
	auto out10_3 = s.isMatch("aa", "a*");    //true
	auto out10_4 = s.isMatch("aa", ".*");    //true
	auto out10_5 = s.isMatch("ab", ".*");    //true
	auto out10_6 = s.isMatch("aab", "c*a*b");    //true
	auto out10_7 = s.isMatch("ab", ".*c");    //false
	auto out10_8 = s.isMatch("aaa", "a.a");    //true
	auto out10_9 = s.isMatch("aaa", "a*a");    //true
	auto out10_10 = s.isMatch("aaa", "ab*a*c*a");    //true
	auto out10_11 = s.isMatch("aab", "a*c");    //false

	auto out29_0 = s.divide(-1060849722, 99958928);		//-10
	auto out29_1 = s.divide(INT_MIN, 265681027);		//-8 
	auto out29_2 = s.divide(INT_MIN, -1017100424);	//2
	auto out29_3 = s.divide(INT_MIN, -1);			//INT_MAX
	auto out29_4 = s.divide(1, -1);						//-1

	vector<string> in30_0 = { "foo", "bar" };
	auto out30_0 = s.findSubstring("barfoothefoobarman", in30_0);

	vector<int> in33_0 = { 1, 3 };
	vector<int> in33_1 = { 1 };
	auto out33_0 = s.search(in33_0, 1);
	auto out33_1 = s.search(in33_1, 1);
	auto out33_2 = s.search(in33_0, 3);

	vector<vector<char>> in37_0 = { 
		{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
		{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
		{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
		{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
		{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
		{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
		{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
		{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
		{ '.', '.', '.', '.', '8', '.', '.', '7', '9' },
	};
	s.solveSudoku(in37_0);


	vector<int> in45_0 = { 5,9,3,2,1,0,2,3,3,1,0,0 };
	auto out45_0 = s.jump(in45_0);

	//A = [2, 3, 1, 1, 4], return true.
	//A = [3, 2, 1, 0, 4], return false.
	vector<int> in55_1 = { 2, 3, 1, 1, 4 };
	vector<int> in55_2 = { 3, 2, 1, 0, 4 };
	auto out55_1 = s.canJump(in55_1);
	auto out55_2 = s.canJump(in55_2);

	auto out59 = s.generateMatrix(3);

	auto out60 = s.getPermutation(4, 4);

	auto out61 = s.rotateRight(nullptr, 0);
	
	vector<string> in68_0 = { "This", "is", "an", "example", "of", "text", "justification." };
	auto out68_0 = s.fullJustify(in68_0, 16);
	vector<string> in68_1 = { "a", "b", "c", "d", "e" };
	auto out68_1 = s.fullJustify(in68_1, 1);


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

	auto in82_0 = makeList({1, 2, 3});
	auto in82_1 = makeList({ 1, 2, 3, 3, 4, 4, 5 });
	auto in82_2 = makeList({ 1, 2, 2, 2, 3 });
	auto in82_3 = makeList({ 1, 1, 2, 3 });
	auto in82_4 = makeList({ 1, 2, 3, 3 });
	auto in82_5 = makeList({ 3, 3 });
	auto out82_0 = s.deleteDuplicatesii(in82_0);
	auto out82_1 = s.deleteDuplicatesii(in82_1);
	auto out82_2 = s.deleteDuplicatesii(in82_2);
	auto out82_3 = s.deleteDuplicatesii(in82_3);
	auto out82_4 = s.deleteDuplicatesii(in82_4);
	auto out82_5 = s.deleteDuplicatesii(in82_5);


	auto in86_0 = makeList({ 1 });
	auto out86_0 = s.partition(in86_0, 0);

	auto in92_0 = makeList({ 1,2,3,4,5 });
	auto out92_0 = s.reverseBetween(in92_0, 2, 4);

	auto out93_0 = s.restoreIpAddresses("25525511135");
	auto out93_1 = s.restoreIpAddresses("0279245587303");
	auto out93_2 = s.restoreIpAddresses("0000");
	auto out93_3 = s.restoreIpAddresses("010010"); //["0.10.0.10","0.100.1.0"]

	auto out89_0 = s.grayCode(0);
	auto out89_1 = s.grayCode(1);
	auto out89_2 = s.grayCode(2);
	auto out89_3 = s.grayCode(3);

	auto out91_0 = s.numDecodings("");
	auto out91_1 = s.numDecodings("0");
	auto out91_2 = s.numDecodings("12");
	auto out91_3 = s.numDecodings("012");
	auto out91_4 = s.numDecodings("012");

	TreeNode* in94_0 = nullptr;
	TreeNode* in94_1 = makeBinaryTree("1");
	TreeNode* in94_2 = makeBinaryTree("1,2");
	TreeNode* in94_3 = makeBinaryTree("1,null,3");
	TreeNode* in94_4 = makeBinaryTree("1,2,3");
	auto out94_0 = s.inorderTraversal(in94_0);
	auto out94_1 = s.inorderTraversal(in94_1);
	auto out94_2 = s.inorderTraversal(in94_2);
	auto out94_3 = s.inorderTraversal(in94_3);
	auto out94_4 = s.inorderTraversal(in94_4);

	auto out95_0 = s.generateTrees(3);

	TreeNode *in98_0 = nullptr;
	TreeNode *in98_1 = new TreeNode(1);
	in98_1->left = new TreeNode(-1);
	auto out98_0 = s.isValidBST(in98_0);
	auto out98_1 = s.isValidBST(in98_1);

	TreeNode *in113_0 = makeBinaryTree("1,-2,3");
	TreeNode *in113_1 = makeBinaryTree("5,4,8,11,null,13,4,7,2,null,null,5,1");
	auto out113_0 = s.pathSum(in113_0, 1);
	auto out113_1 = s.pathSum(in113_1, 22);

	TreeNode *in114_0 = makeBinaryTree("1,-2,3");
	TreeNode *in114_1 = makeBinaryTree("5,4,8,11,null,13,4,7,2,null,null,5,1");
	s.flatten(in114_0);
	s.flatten(in114_1);

	TreeLinkNode *in117_0 = makeBinaryLinkTree("7,-10,2,-4,3,-8,#,#,#,#,-1,11");
	TreeLinkNode *in117_1 = makeBinaryLinkTree("1,2,3,4,5,#,6,7,#,#,#,#,8");
	TreeLinkNode *in117_2 = makeBinaryLinkTree("2,1,3,0,7,9,1,2,#,1,0,#,#,8,8,#,#,#,#,7");
	TreeLinkNode *in117_3 = makeBinaryLinkTree("-2,-9,0,3,5,-1,9,5,2,#,#,-3,#,-7,6,-6,#,#,#,-1,#,#,#,-9,9,#,#,#,#,8,#,-2,5");
	s.connectii(in117_0);
	s.connectii(in117_1);
	s.connectii(in117_2);
	s.connectii(in117_3);

	vector<vector<int>> in120_0 = { {-1}, {-2,-3} };
	auto out120_0 = s.minimumTotal(in120_0);
	
	auto out131_0 = s.partition("ab");

	auto in142_0 = makeList({ 1 });
	auto in142_1 = makeList({ 3, 2, 0, 4 });
	auto in142_1_0 = in142_1;
	while (in142_1_0->next) {
		in142_1_0 = in142_1_0->next;
	}
	in142_1_0->next = in142_1->next;
	vector<int> in142_2_0;
	for (int i = 0; i < 200000; ++i) {
		in142_2_0.push_back(rand());
	}
	auto in142_2 = makeList({ 1 });
	auto out142_0 = s.detectCycle(in142_0);
	auto out142_1 = s.detectCycle(in142_1);
	auto out142_2 = s.detectCycle(in142_2);


	LRUCache cache(2);
	cache.set(2, 1); cache.set(1, 1); cache.set(2, 3); cache.set(4, 1); cache.get(1); cache.get(2);


	string in151_0 = "was isi iiis";
	string in151_1 = "was isi    iiis";
	string in151_2 = "wasiiis";
	string in151_3 = " was isi iiis ";
	s.reverseWords(in151_0);
	s.reverseWords(in151_1);
	s.reverseWords(in151_2);
	s.reverseWords(in151_3);

	auto out166_0 = s.fractionToDecimal(0, 3);
	auto out166_1 = s.fractionToDecimal(1, 3);
	auto out166_2 = s.fractionToDecimal(3, 3);
	auto out166_3 = s.fractionToDecimal(3, 1);
	auto out166_4 = s.fractionToDecimal(4, 3);
	auto out166_5 = s.fractionToDecimal(-1, -2147483648);

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

	vector<vector<char>> in200_0 = { { '1','0','1','1','0','1','1' } };
	auto out200_0 = s.numIslands(in200_0);

	auto out201_0 = s.rangeBitwiseAnd(5, 7);

	auto out214_0 = s.shortestPalindrome("aacecaaa");
	auto out214_1 = s.shortestPalindrome("abcd");

	vector<int> in215_0 = { 2, 1 };
	auto out215_0 = s.findKthLargest(in215_0, 1);

	WordDictionary in211;
	in211.addWord("a");
	in211.addWord("a");
	in211.search(".");
	in211.search("a");
	in211.search("aa");
	in211.search("a");
	in211.search(".a");
	in211.search("a.");

	vector<vector<char>> in221_0 = { { '0', '1' } };
	auto out221_0 = s.maximalSquare(in221_0);

	auto out227_0 = s.calculateii("3+2*2");

	auto out230_0 = s.kthSmallest(makeBinaryTree("3,1,4,null,2"), 2);
	auto out230_1 = s.kthSmallest(makeBinaryTree("3,2,4,1"), 3);

	auto out234_0 = s.isPalindrome(makeList({ 1, 1, 2, 1 }));

	vector<int> in239_0 = { 1,3,-1,-3,5,3,6,7 };
	auto out239_0 = s.maxSlidingWindow(in239_0, 3);


	auto out241_0 = s.diffWaysToCompute("2*3-4*5");

	vector<int> in275_0 = { 2, 3, 3, 3, 5, 5, 6, 8, 10, 10, 10 };
	auto out275_0 = s.hIndexii(in275_0);


	auto out278_0 = s.firstBadVersion(2126753390);

	auto out279_0 = s.numSquares(12);

	auto out283_0 = s.isUgly(-2147483648);

	auto out292_0 = s.wordPattern("abba", "dog dog dog dog");
	

	MedianFinder mf;
	mf.addNum(1);
	mf.addNum(2);
	auto out295_0 = mf.findMedian();
	mf.addNum(3);
	auto out295_1 = mf.findMedian();

	Codec codec;
	TreeNode *in297_0 = makeBinaryTree("7,-10,2,-4,3,-8,#,#,#,#,-1,11");
	TreeNode *in297_1 = makeBinaryTree("1,2,3,4,5,#,6,7,#,#,#,#,8");
	TreeNode *in297_2 = makeBinaryTree("2,1,3,0,7,9,1,2,#,1,0,#,#,8,8,#,#,#,#,7");
	TreeNode *in297_3 = makeBinaryTree("-2,-9,0,3,5,-1,9,5,2,#,#,-3,#,-7,6,-6,#,#,#,-1,#,#,#,-9,9,#,#,#,#,8,#,-2,5");
	TreeNode *in297_4 = makeBinaryTree("1,null,2");
	TreeNode *out297_0 = codec.deserialize(codec.serialize(in297_0));
	TreeNode *out297_1 = codec.deserialize(codec.serialize(in297_1));
	TreeNode *out297_2 = codec.deserialize(codec.serialize(in297_2));
	TreeNode *out297_3 = codec.deserialize(codec.serialize(in297_3));
	TreeNode *out297_4 = codec.deserialize(codec.serialize(in297_4));


	vector<vector<int>> matrix = {
		{3, 0, 1, 4, 2},
		{5, 6, 3, 2, 1}, 
		{1, 2, 0, 1, 5}, 
		{4, 1, 0, 1, 7}, 
		{1, 0, 3, 0, 5}
	};
	NumMatrix numMatrix(matrix);
	auto out304_0 = numMatrix.sumRegion(2, 1, 4, 3);
	auto out304_1 = numMatrix.sumRegion(1, 1, 2, 2);
	auto out304_2 = numMatrix.sumRegion(1, 2, 2, 4);

	auto out315_0 = s.removeDuplicateLetters("bcabc");
	auto out315_1 = s.removeDuplicateLetters("cbacdcbc");

	vector<int> in324_0 = { 5, 6, 4, 3, 2, 6, 7, 9, 3 };
	s.wiggleSort(in324_0);

	auto out326_0 = s.isPowerOfThree(2);
	auto out326_1 = s.isPowerOfThree(59049);


	vector<pair<string, string>> in332_0 = { {"MUC", "LHR"},{"JFK", "MUC"},{"SFO", "SJC"},{"LHR", "SFO"} };
	vector<pair<string, string>> in332_1 = { {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"} };
	auto out332_0 = s.findItinerary(in332_0);
	auto out332_1 = s.findItinerary(in332_1);

	auto out345_0 = s.reverseVowels("hello");

	auto out347_0 = s.topKFrequent({ 1, 1, 1, 2, 2, 3 }, 2);
	auto out347_1 = s.topKFrequent({ 3, 0, 1, 0 }, 1);

	auto out349_0 = s.intersection({ 9, 3, 7 }, { 6, 4, 1, 0, 0, 4, 4, 8, 7 });

	auto out367_1 = s.isPerfectSquare(1);
	auto out367_2 = s.isPerfectSquare(2);
	auto out367_3 = s.isPerfectSquare(3);
	auto out367_4 = s.isPerfectSquare(4);
	auto out367_5 = s.isPerfectSquare(16);
	auto out367_6 = s.isPerfectSquare(808201);
	auto out367_7 = s.isPerfectSquare(2147395600);

	Solution_384 s384({ 1,2,3 });
	for (int i = 0; i < 100; i++) {
		auto out384 = s384.shuffle();
	}

	Solution_385 s385;
	auto out385_0 = s385.deserialize("324");
	auto out385_1 = s385.deserialize("[324]");
	auto out385_2 = s385.deserialize("[324,[123]]");
	auto out385_3 = s385.deserialize("[123,[456,[789]]]");
	auto out385_4 = s385.deserialize("[]");
	auto out385_5 = s385.deserialize("[[]]");

	return 0;
}
