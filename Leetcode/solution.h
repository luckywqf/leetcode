#pragma once

#include "common.h"

//-------------------------------------------------
// 155. https://leetcode.com/problems/min-stack/
//-------------------------------------------------
class MinStack {
public:
	void push(int x) {
		if (data.empty()) {
			data.push(make_pair(x, x));
		}
		else {
			if (data.top().second > x) {
				data.push(make_pair(x, x));
			}
			else {
				data.push(make_pair(x, data.top().second));
			}
		}
	}

	void pop() {
		if (!data.empty()) {
			data.pop();
		}
	}

	int top() {
		if (data.empty()) {
			throw runtime_error("Stack is empty.");
		}
		return data.top().first;
	}

	int getMin() {
		if (data.empty()) {
			throw runtime_error("Stack is empty.");
		}
		return data.top().second;
	}
private:
	stack<pair<int, int>> data;
};

class Solution {
public:
	//=================================================
	//                     Easy
	//=================================================

	//-------------------------------------------------
	// 1. https://leetcode.com/problems/two-sum/
	//-------------------------------------------------
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<pair<int, int>> number;
		for (int i = 0; i < nums.size(); ++i) {
			number.emplace_back(i, nums[i]);
		}
		sort(number.begin(), number.end(), [](pair<int, int> x, pair<int, int> y) { return x.second < y.second; });
		int maxAviliable = target - number[0].second;
		int value = 0;
		for (int i = 0; number[i].second <= maxAviliable; ++i) {
			for (int j = i + 1; j < number.size(); ++j) {
				value = number[i].second + number[j].second;
				if (value == target) {
					return{ std::min(number[i].first, number[j].first) + 1,
						std::max(number[i].first, number[j].first) + 1 };
				}
				else if (value > target) {
					break;
				}
			}
		}
	}

	//-------------------------------------------------
	// 2. https://leetcode.com/problems/add-two-numbers/
	//-------------------------------------------------
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == NULL) {
			return l2;
		}
		if (l2 == NULL) {
			return l1;
		}
		ListNode *head = new ListNode(0);
		ListNode *p = head;
		int carryBit = 0;
		int value = 0;
		while (l1 != NULL && l2 != NULL) {
			p->next = new ListNode(0);
			p = p->next;
			value = l1->val + l2->val + carryBit;
			p->val = value % 10;
			carryBit = value / 10;

			l1 = l1->next;
			l2 = l2->next;
		}

		while (l1 != NULL) {
			p->next = new ListNode(0);
			p = p->next;
			value = l1->val + carryBit;
			p->val = value % 10;
			carryBit = value / 10;
			l1 = l1->next;
		}
		while (l2 != NULL) {
			p->next = new ListNode(0);
			p = p->next;
			value = l2->val + carryBit;
			p->val = value % 10;
			carryBit = value / 10;
			l2 = l2->next;
		}

		if (carryBit != 0) {
			p->next = new ListNode(carryBit);
		}

		return head->next;
	}

	//-------------------------------------------------
	// 3. https://leetcode.com/problems/longest-substring-without-repeating-characters/
	//-------------------------------------------------
	int lengthOfLongestSubstring(string s) {
		if (s.empty()) {
			return 0;
		}
		uint8_t dic[256] = { 0 };
		int maxLen = 0;
		for (int i = 0; i < s.size(); ++i) {
			for (int j = i; ; ++j) {
				if (j == s.size() || dic[s[j]]) {
					if (j - i > maxLen) {
						maxLen = j - i;
					}
					memset(dic, 0, sizeof(dic));
					break;
				}
				dic[s[j]] = 1;
			}
		}
		return maxLen;
	}

	//-------------------------------------------------
	// 4. https://leetcode.com/problems/median-of-two-sorted-arrays/
	//-------------------------------------------------
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int N1 = nums1.size();
		int N2 = nums2.size();
		if (N1 < N2) return findMedianSortedArrays(nums2, nums1);   // Make sure A2 is the shorter one.

		if (N2 == 0) return (nums1[(N1 - 1) / 2] + nums1[N1 / 2]) / 2;  // If A2 is empty

		int lo = 0, hi = N2 * 2;
		while (lo <= hi) {
			int mid2 = (lo + hi) / 2;   // Try Cut 2 
			int mid1 = N1 + N2 - mid2;  // Calculate Cut 1 accordingly

			double L1 = (mid1 == 0) ? INT_MIN : nums1[(mid1 - 1) / 2];  // Get L1, R1, L2, R2 respectively
			double L2 = (mid2 == 0) ? INT_MIN : nums2[(mid2 - 1) / 2];
			double R1 = (mid1 == N1 * 2) ? INT_MAX : nums1[(mid1) / 2];
			double R2 = (mid2 == N2 * 2) ? INT_MAX : nums2[(mid2) / 2];

			if (L1 > R2) lo = mid2 + 1;     // A1's lower half is too big; need to move C1 left (C2 right)
			else if (L2 > R1) hi = mid2 - 1;    // A2's lower half too big; need to move C2 left.
			else return (max(L1, L2) + min(R1, R2)) / 2; // Otherwise, that's the right cut.
		}
		return -1;
	}

	//-------------------------------------------------
	// 5. https://leetcode.com/problems/longest-palindromic-substring/
	//-------------------------------------------------
	string longestPalindrome(string s) {
		if (s.size() <= 1) {
			return s;
		}
		int startPos = 0, len = 1;
		for (int i = 1; i < s.size(); ++i) {
			int j, tempLen = 0;
			for (j = 1; i - j >= 0 && i + j < s.size(); ++j) {
				if (s[i - j] != s[i + j]) {
					break;
				}
			}
			tempLen = (j - 1) * 2 + 1;
			if (tempLen > len) {
				len = tempLen;
				startPos = i - j + 1;
			}

			for (j = 1; i - j >= 0 && i + j - 1 < s.size(); ++j) {
				if (s[i - j] != s[i + j - 1]) {
					break;
				}
			}
			tempLen = (j - 1) * 2;
			if (tempLen > len) {
				len = (j - 1) * 2;
				startPos = i - j + 1;
			}
		}
		return s.substr(startPos, len);
	}

	//-------------------------------------------------
	// 6. https://leetcode.com/problems/zigzag-conversion/
	//-------------------------------------------------
	//?????????????????????????????????????????????????
	string convert(string s, int numRows) {
		if (s.empty() || numRows <= 1) {
			return s;
		}
		string result;
		int interval;
		for (int i = 0; i < numRows; ++i) {
			if (i == numRows - 1) {
				interval = numRows * 2 - 2;
			}
			else {
				interval = (numRows - i - 1) * 2;
			}
			for (int k = i; k < s.size(); k += interval) {
				result.push_back(s[k]);
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 7. https://leetcode.com/problems/reverse-integer/
	//-------------------------------------------------
	int reverse(int x) {
		int temp = x >= 0 ? x : -x;
		string str = to_string(temp);
		std::reverse(str.begin(), str.end());
		if (str.size() > 10 || (str.size() == 10 && str > "2147483647")) {
			return 0;
		}
		temp = atoi(str.c_str());
		return x < 0 ? -temp : temp;
	}

	//-------------------------------------------------
	// 8. https://leetcode.com/problems/string-to-integer-atoi/
	//-------------------------------------------------
	void trim(string& str) {
		int start = 0, end = str.size() - 1;
		if (str.empty())
			return;
		while (isspace(str[start])) {
			++start;
		}
		while (isspace(str[end])) {
			--end;
		}
		str = str.substr(start, end - start + 1);
	}
	int myAtoi(string str) {
		trim(str);
		if (str.empty()) {
			return 0;
		}
		bool isNegtive = false;
		if (str[0] == '-') {
			str.erase(str.begin());
			isNegtive = true;
		}
		else if (str[0] == '+') {
			str.erase(str.begin());
		}

		long long sum = 0;
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] > '9' || str[i] < '0') {
				break;
			}
			sum *= 10;
			sum += str[i] - '0';
			if (!isNegtive && sum >= INT_MAX) {
				return INT_MAX;
			}
			else if (isNegtive && sum >= (long long)(INT_MAX)+1) {
				return INT_MIN;
			}
		}
		return isNegtive ? -sum : sum;
	}

	//-------------------------------------------------
	// 9. https://leetcode.com/problems/palindrome-number/
	//-------------------------------------------------
	bool isPalindrome(int x) {
		if (x < 0) {
			return false;
		}
		int y = x;
		int bits = 1;
		while (x /= 10) {
			++bits;
		}
		int powx = pow(10, bits - 1);
		x = y;
		while (bits >= 2) {
			if (x / powx != y % 10) {
				return false;
			}
			x %= powx;
			y /= 10;
			powx /= 10;
			bits -= 2;
		}
		return true;
	}

	//-------------------------------------------------
	// 11. https://leetcode.com/problems/container-with-most-water/
	//-------------------------------------------------
	int maxArea(vector<int>& height) {
		int maxA = 0;
		for (int i = 1; i < height.size(); ++i) {
			int lowH = 0;
			for (int j = 0; j < i; ++j) {
				if (height[j] <= lowH) {
					continue;
				}
				int tempA = (i - j) * min(height[i], height[j]);
				if (tempA > maxA) {
					maxA = tempA;
					lowH = height[j];
				}
				if (height[i] < height[j]) {
					break;
				}
			}
		}
		return maxA;
	}

	//-------------------------------------------------
	// 12. https://leetcode.com/problems/integer-to-roman/
	//-------------------------------------------------
	string intToRoman(int num) {
		static map<int, char> romanDict = { { 1, 'I' },{ 5, 'V' },{ 10, 'X' },{ 50, 'L' },{ 100, 'C' },{ 500, 'D' },{ 1000, 'M' } };
		string result;

		if (num < 10) {
			if (num < 4) {
				result += string(num, romanDict[1]);
			}
			else if (num == 4) {
				result += romanDict[1];
				result += romanDict[5];
			}
			else if (num == 5) {
				result += romanDict[5];
			}
			else if (num < 9) {
				result += romanDict[5];
				result += string(num - 5, romanDict[1]);
			}
			else {
				result += romanDict[1];
				result += romanDict[10];
			}
			return result;
		}
		else if (num < 100)
		{
			int n10 = num / 10;
			if (n10 < 4) {
				result += string(n10, romanDict[10]);
			}
			else if (n10 == 4) {
				result += romanDict[10];
				result += romanDict[50];
			}
			else if (n10 == 5) {
				result += romanDict[50];
			}
			else if (n10 < 9) {
				result += romanDict[50];
				result += string(n10 - 5, romanDict[10]);
			}
			else {
				result += romanDict[10];
				result += romanDict[100];
			}
			return result + intToRoman(num % 10);
		}
		else if (num < 1000) {
			int n100 = num / 100;
			if (n100 < 4) {
				result += string(n100, romanDict[100]);
			}
			else if (n100 == 4) {
				result += romanDict[100];
				result += romanDict[500];
			}
			else if (n100 == 5) {
				result += romanDict[500];
			}
			else if (n100 < 9) {
				result += romanDict[500];
				result += string(n100 - 5, romanDict[100]);
			}
			else {
				result += romanDict[100];
				result += romanDict[1000];
			}
			return result + intToRoman(num % 100);
		}
		else {
			int n1000 = num / 1000;
			if (n1000 > 0) {
				result += string(n1000, romanDict[1000]);
				return result + intToRoman(num % 1000);
			}
		}
	}
	//-------------------------------------------------
	// 13. https://leetcode.com/problems/roman-to-integer/
	//-------------------------------------------------
	int romanToInt(string s) {
		int value[256];
		value['I'] = 1;    value['i'] = 1;
		value['V'] = 5;    value['v'] = 5;
		value['X'] = 10;   value['x'] = 10;
		value['L'] = 50;   value['l'] = 50;
		value['C'] = 100;  value['c'] = 100;
		value['D'] = 500;  value['d'] = 500;
		value['M'] = 1000; value['m'] = 1000;
		int result = 0, maxP = 0;
		for (int i = s.size() - 1; i >= 0; --i) {
			if (value[s[i]] >= maxP) {
				result += value[s[i]];
				maxP = value[s[i]];
			}
			else {
				result -= value[s[i]];
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 14. https://leetcode.com/problems/longest-common-prefix/
	//-------------------------------------------------
	string longestCommonPrefix(vector<string>& strs) {
		string result;
		if (strs.empty()) {
			return result;
		}
		else if (strs.size() == 1) {
			return strs[0];
		}
		for (int i = 0;;++i) {
			for (int j = 1; j < strs.size(); ++j) {
				if (i >= strs[j - 1].size() || i >= strs[j].size()) {
					goto over;
				}
				if (strs[j][i] != strs[j - 1][i]) {
					goto over;
				}
			}
			result.push_back(strs[0][i]);
		}
	over:
		return result;
	}

	//-------------------------------------------------
	// 19. https://leetcode.com/problems/remove-nth-node-from-end-of-list/
	//-------------------------------------------------
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode *p = head, *reverseN = head;
		int i = 1;
		while (i++ < n) {
			p = p->next;
		}
		if (p->next == NULL) { //remove first node
			return reverseN->next;
		}
		while (p->next != NULL && p->next->next != NULL) {
			p = p->next;
			reverseN = reverseN->next;
		}
		ListNode *temp = reverseN->next;
		if (temp) {
			reverseN->next = temp->next;
		}
		else {
			reverseN->next = NULL;
		}
		return head;
	}

	//-------------------------------------------------
	// 20. https://leetcode.com/problems/valid-parentheses/
	//-------------------------------------------------
	bool isValid(string s) {
		stack<char> st;
		std::map<char, char> matchMap = { { ')', '(' },{ ']', '[' },{ '}', '{' } };
		for (auto &c : s) {
			switch (c) {
			case '(':
			case '[':
			case '{':
				st.push(c);
				break;
			case ')':
			case ']':
			case '}':
				if (st.empty()) {
					return false;
				}
				if (st.top() == matchMap[c]) {
					st.pop();
				}
				else {
					return false;
				}
				break;
			default:
				return false;
			}
		}
		return st.empty();
	}

	//-------------------------------------------------
	// 21. https://leetcode.com/problems/merge-two-sorted-lists/
	//-------------------------------------------------
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode node(0), *p = &node;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				p->next = l1;
				l1 = l1->next;
			}
			else {
				p->next = l2;
				l2 = l2->next;
			}
			p = p->next;
		}
		if (l1) {
			p->next = l1;
		}
		if (l2) {
			p->next = l2;
		}
		return node.next;
	}

	//-------------------------------------------------
	// 26. https://leetcode.com/problems/remove-duplicates-from-sorted-array/
	//-------------------------------------------------
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() <= 1) {
			return nums.size();
		}
		for (int i = 1; i < nums.size(); ) {
			if (nums[i] == nums[i - 1]) {
				nums.erase(nums.begin() + i);
			}
			else {
				++i;
			}
		}
		return nums.size();
	}

	//-------------------------------------------------
	// 27. https://leetcode.com/problems/remove-element/
	//-------------------------------------------------
	int removeElement(vector<int>& nums, int val) {
		int result = nums.size();
		for (int i = 0; i < result; ++i) {
			int j = i;
			while (nums[j] == val && j < result) {
				++j;
			}
			if (i != j) {
				for (int des = i, src = j; src < result; ++src, ++des) {
					nums[des] = nums[src];
				}
				result -= (j - i);
			}
		}
		nums.resize(result);
		return result;
	}

	//-------------------------------------------------
	// 28. https://leetcode.com/problems/implement-strstr/
	//-------------------------------------------------
	int strStr(string haystack, string needle) {
		if (haystack.empty() || needle.empty()) {
			return -1;
		}
		int j;
		for (int i = 0; i < haystack.size(); ++i) {
			for (j = 0; j < needle.size() && i < haystack.size(); ++j, ++i) {
				if (needle[j] != haystack[i]) {
					break;
				}
			}
			i -= j;
			if (j >= needle.size()) {
				return i;
			}
		}
		return -1;
	}

	void getNext(const char *p, int next[]) {
		int i = 0, j = 1;
		next[0] = 0;
		while (p[j] != '\0') {
			if (p[j] == p[i]) {
				next[j] = next[j - 1] + 1;
				++i; ++j;
			}
			else {
				i = 0;
				next[j] = 0;
				++j;
			}
		}
	}
	int KmpStrStr(string haystack, string needle) {
		if (needle.empty()) {
			return 0;
		}
		if (haystack.empty()) {
			return -1;
		}
		//std::shared_ptr<int> next = std::shared_ptr<int>(new int[needle.size()], [](int *p) {delete []p;});
		int *next = new int[needle.size()];
		getNext(needle.c_str(), next);
		for (int i = 0, j = 0; i < haystack.size();) {
			for (; j < needle.size() && i < haystack.size(); ++j, ++i) {
				if (needle[j] != haystack[i]) {
					break;
				}
			}
			if (j >= needle.size()) {
				delete[]next;
				return i - j;
			}
			else if (j != 0) {
				j = next[j - 1];
			}
			else {
				++i;
			}
		}
		delete[]next;
		return -1;
	}

	//-------------------------------------------------
	// 38. https://leetcode.com/problems/valid-sudoku/
	//-------------------------------------------------
	bool isValidSudoku(vector<vector<char>>& board) {
		int row[9][10] = { 0 };
		int column[9][10] = { 0 };
		int box[9][10] = { 0 };
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[i].size(); ++j) {
				if (board[i][j] != '.') {
					char c = board[i][j] - '0';
					int boxP = i / 3 * 3 + j / 3;
					if (row[i][c] || column[j][c] || box[boxP][c]) {
						return false;
					}
					row[i][c] = 1;
					column[j][c] = 1;
					box[boxP][c] = 1;
				}
			}
		}
		return true;
	}

	//-------------------------------------------------
	// 39. https://leetcode.com/problems/count-and-say/
	//-------------------------------------------------
	string countAndSayString(string str) {
		string result;
		for (int i = 0; i < str.size(); ) {
			int j = i + 1;
			while (str[j] == str[i]) {
				++j;
			}
			result += to_string(j - i);
			result += str[i];
			i = j;
		}
		return result;
	}

	string countAndSay(int n) {
		string result = "1";
		for (int i = 1; i < n; ++i) {
			result = countAndSayString(result);
		}
		return result;
	}
	//-------------------------------------------------
	// 58. https://leetcode.com/problems/length-of-last-word/
	//-------------------------------------------------
	int lengthOfLastWord(string s) {
		int sum = 0;
		int i = s.size() - 1;
		while (i >= 0 && !isalpha(s[i])) {
			--i;
		}
		while (i >= 0 && isalpha(s[i])) {
			--i;
			++sum;
		}
		return sum;
	}

	//-------------------------------------------------
	// 66. https://leetcode.com/problems/plus-one/
	//-------------------------------------------------
	vector<int> plusOne(vector<int>& digits) {
		vector<int> result;
		int carryBit = 0, bit;
		for (int i = digits.size() - 1; i >= 0 || carryBit; --i) {
			if (i >= 0) {
				bit = digits[i];
			}
			else {
				bit = 0;
			}
			if (i == digits.size() - 1) {
				bit += 1;
			}
			else {
				bit += carryBit;
			}
			if (bit > 9) {
				bit -= 10;
				carryBit = 1;
			}
			else {
				carryBit = 0;
			}
			result.insert(result.begin(), bit);
		}
		return result;
	}

	//-------------------------------------------------
	// 67. https://leetcode.com/problems/add-binary/
	//-------------------------------------------------
	string addBinary(string a, string b) {
		string result;
		int pa = a.size() - 1;
		int pb = b.size() - 1;
		char ca, cb, bitSum;
		int carryBit = 0;
		while (pa >= 0 || pb >= 0 || carryBit) {
			if (pa < 0) {
				ca = 0;
			}
			else {
				ca = a[pa] - '0';
			}

			if (pb < 0) {
				cb = 0;
			}
			else {
				cb = b[pb] - '0';
			}

			bitSum = carryBit + ca + cb;
			if (bitSum > 1) {
				bitSum -= 2;
				carryBit = 1;
			}
			else {
				carryBit = 0;
			}
			bitSum += '0';
			result.insert(result.begin(), bitSum);
			--pa; --pb;
		}
		return result;
	}


	//-------------------------------------------------
	// 70. https://leetcode.com/problems/climbing-stairs/
	//-------------------------------------------------
	int climbStairs(int n) {
		int *ways = new int[n + 1];
		ways[0] = ways[1] = 1;
		for (int i = 2; i <= n; ++i) {
			ways[i] = ways[i - 1] + ways[i - 2];
		}
		int result = ways[n];
		delete[]ways;
		return result;
	}

	//-------------------------------------------------
	// 83. https://leetcode.com/problems/remove-duplicates-from-sorted-list/
	//-------------------------------------------------
	ListNode* deleteDuplicates(ListNode* head) {
		ListNode *p = head;
		ListNode *prev;
		while (p) {
			prev = p;
			p = p->next;
			if (p == NULL) {
				break;
			}
			if (p->val == prev->val) {
				prev->next = p->next;
				p = prev;
			}
		}
		return head;
	}

	//-------------------------------------------------
	// 88. https://leetcode.com/problems/merge-sorted-array/
	//-------------------------------------------------
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		for (int i = 0, j = 0; i < n; ++i) {
			while (j < m && nums1[j] < nums2[i]) {
				++j;
			}
			for (int x = m; x > j; --x) {
				nums1[x] = nums1[x - 1];
			}
			nums1[j] = nums2[i];
			++m;
			++j;
		}
	}

	//-------------------------------------------------
	// 100. https://leetcode.com/problems/same-tree/
	//-------------------------------------------------
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == NULL && q == NULL) {
			return true;
		}
		else if (p == NULL && q != NULL ||
			p != NULL && q == NULL) {
			return false;
		}
		else {
			if (p->val != q->val) {
				return false;
			}
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		}
	}

	//-------------------------------------------------
	// 101. https://leetcode.com/problems/symmetric-tree/
	//-------------------------------------------------
	bool treeLRTravse(TreeNode* left, TreeNode* right) {
		if (left == NULL && right == NULL) {
			return true;
		}
		else if (left == NULL && right != NULL ||
			left != NULL && right == NULL) {
			return false;
		}
		else {
			if (left->val != right->val) {
				return false;
			}
			return treeLRTravse(left->left, right->right) && treeLRTravse(left->right, right->left);
		}
	}
	bool isSymmetric(TreeNode* root) {
		if (root == NULL) {
			return true;
		}
		return treeLRTravse(root->left, root->right);
	}


	//-------------------------------------------------
	// 102. https://leetcode.com/problems/binary-tree-level-order-traversal/
	//-------------------------------------------------
	vector<vector<int>> levelOrder(TreeNode* root) {
		queue<TreeNode*> tq;
		vector<vector<int>> result;
		if (root == NULL) {
			return result;
		}
		tq.push(root);
		tq.push(NULL);
		while (!tq.empty() && tq.front()) {
			vector<int> level;
			while (!tq.empty()) {
				TreeNode* p = tq.front();
				if (p) {
					level.push_back(p->val);
					if (p->left) {
						tq.push(p->left);
					}
					if (p->right) {
						tq.push(p->right);
					}
					tq.pop();
				}
				else {
					tq.push(NULL);
					tq.pop();
					break;
				}
			}
			result.push_back(level);
		}
		return result;
	}

	//-------------------------------------------------
	// 104. https://leetcode.com/problems/maximum-depth-of-binary-tree/
	//-------------------------------------------------
	int maxDepth(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		if (root->left == NULL && root->right == NULL) {
			return 1;
		}
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}

	//-------------------------------------------------
	// 107. https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
	//-------------------------------------------------
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		queue<TreeNode*> tq;
		vector<vector<int>> result;
		if (root == NULL) {
			return result;
		}
		tq.push(root);
		tq.push(NULL);
		while (!tq.empty() && tq.front()) {
			vector<int> level;
			while (!tq.empty()) {
				TreeNode* p = tq.front();
				if (p) {
					level.push_back(p->val);
					if (p->left) {
						tq.push(p->left);
					}
					if (p->right) {
						tq.push(p->right);
					}
					tq.pop();
				}
				else {
					tq.push(NULL);
					tq.pop();
					break;
				}
			}
			result.push_back(level);
		}
		std::reverse(result.begin(), result.end());
		return result;
	}

	//-------------------------------------------------
	// 110. https://leetcode.com/problems/balanced-binary-tree/
	//-------------------------------------------------
	bool isBalanced(TreeNode* root) {
		if (root == NULL || (root->left == NULL && root->right == NULL)) {
			return true;
		}
		function<int(TreeNode*)> treeDepth = bind(&Solution::maxDepth, this, placeholders::_1);
		int ldepth = treeDepth(root->left);
		int rdepth = treeDepth(root->right);
		if (abs(ldepth - rdepth) > 1) {
			return false;
		}
		return isBalanced(root->left) && isBalanced(root->right);
	}

	//-------------------------------------------------
	// 111. https://leetcode.com/problems/minimum-depth-of-binary-tree/
	//-------------------------------------------------
	int minDepth(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		if (root->left == NULL && root->right == NULL) {
			return 1;
		}
		else if (root->left && root->right) {
			return min(minDepth(root->left), minDepth(root->right)) + 1;
		}
		else if (root->left) {
			return minDepth(root->left) + 1;
		}
		else {
			return minDepth(root->right) + 1;
		}
	}

	//-------------------------------------------------
	// 112. https://leetcode.com/problems/path-sum/
	//-------------------------------------------------
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == NULL) {
			return false;
		}
		if (root->left == NULL && root->right == NULL) {
			return sum == root->val;
		}
		return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
	}

	//-------------------------------------------------
	// 118. https://leetcode.com/problems/pascals-triangle/
	//-------------------------------------------------
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> result;
		for (int i = 0; i < numRows; ++i) {
			vector<int> line(i + 1, 1);
			for (int j = 1; j < i; ++j) {
				line[j] = result[i - 1][j - 1] + result[i - 1][j];
			}
			result.push_back(line);
		}
		return result;
	}

	//-------------------------------------------------
	// 119. https://leetcode.com/problems/pascals-triangle-ii/
	//-------------------------------------------------
	vector<int> getRow(int rowIndex) {
		rowIndex += 1;
		vector<int> result(rowIndex, 1);
		if (rowIndex <= 2) {
			return result;
		}
		rowIndex -= 2;
		for (int j = 0; j < rowIndex; ++j) {
			int tempP = 1, tempC;
			for (int i = 1; i <= j + 1; ++i) {
				tempC = result[i];
				result[i] = tempP + result[i];
				tempP = tempC;
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 125. https://leetcode.com/problems/valid-palindrome/
	//-------------------------------------------------
	bool isPalindrome(string s) {
		int start = 0;
		int end = s.size() - 1;
		while (start <= end) {
			while (start < s.size() && !isalnum(s[start]))
				++start;
			while (end >= 0 && !isalnum(s[end]))
				--end;
			if (start > end)
				break;
			if (tolower(s[start]) != tolower(s[end])) {
				return false;
			}
			++start;
			--end;
		}
		return true;
	}

	//-------------------------------------------------
	// 160. https://leetcode.com/problems/intersection-of-two-linked-lists/
	//-------------------------------------------------
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		int lenA = 0, lenB = 0;
		if (headA == NULL || headB == NULL) {
			return NULL;
		}
		ListNode *pa = headA, *pb = headB;
		while (pa) {
			++lenA;
			pa = pa->next;
		}
		while (pb) {
			++lenB;
			pb = pb->next;
		}

		int diff;
		pa = headA, pb = headB;
		if (lenA > lenB) {
			diff = lenA - lenB;
			while (diff--) {
				pa = pa->next;
			}
		}
		else {
			diff = lenB - lenA;
			while (diff--) {
				pb = pb->next;
			}
		}
		while (pa && pb) {
			if (pa == pb) {
				return pa;
			}
			pa = pa->next;
			pb = pb->next;
		}
		return NULL;
	}

	//-------------------------------------------------
	// 165. https://leetcode.com/problems/compare-version-numbers/
	//-------------------------------------------------
	int compareVersion(string version1, string version2) {
		size_t off1(0), off2(0), pos1, pos2;
		int v1, v2;
		while (off1 < version1.size() || off2 < version2.size()) {
			if (off1 >= version1.size()) {
				v1 = 0;
			}
			else {
				pos1 = version1.find('.', off1);
				if (pos1 == string::npos) {
					v1 = atoi(version1.substr(off1).c_str());
					off1 = version1.size();
				}
				else {
					v1 = atoi(version1.substr(off1, pos1 - off1).c_str());
					off1 = pos1 + 1;
				}
			}

			if (off2 >= version2.size()) {
				v2 = 0;
			}
			else {
				pos2 = version2.find('.', off2);
				if (pos2 == string::npos) {
					v2 = atoi(version2.substr(off2).c_str());
					off2 = version2.size();
				}
				else {
					v2 = atoi(version2.substr(off2, pos2 - off2).c_str());
					off2 = pos2 + 1;
				}
			}
			if (v1 < v2) {
				return -1;
			}
			else if (v1 > v2) {
				return 1;
			}
		}
		return 0;
	}

	//-------------------------------------------------
	// 168. https://leetcode.com/problems/excel-sheet-column-title/
	//-------------------------------------------------
	string convertToTitle(int n) {
		string str;
		char c;
		while (n >= 1) {
			c = (n - 1) % 26;
			str.insert(str.begin(), c + 'A');
			n -= c + 1;
			n /= 26;
		}
		return str;
	}

	//-------------------------------------------------
	// 169. https://leetcode.com/problems/majority-element/
	//-------------------------------------------------
	int majorityElement(vector<int> &num) {
		int majorityIndex = 0;
		int count = 1;
		for (int i = 1; i < num.size(); i++) {
			num[i] == num[majorityIndex] ? ++count : --count;
			if (count == 0) {
				majorityIndex = i;
				count = 1;
			}
		}

		return num[majorityIndex];
	}

	//-------------------------------------------------
	// 171. https://leetcode.com/problems/excel-sheet-column-number/
	//-------------------------------------------------
	int titleToNumber(string s) {
		int sum = 0;
		for (int i = 0; i < s.size(); ++i) {
			sum *= 26;
			sum += s[i] - 'A' + 1;
		}
		return sum;
	}

	//-------------------------------------------------
	// 172. https://leetcode.com/problems/factorial-trailing-zeroes/
	//-------------------------------------------------
	int trailingZeroes(int n) {
		int sum = 0;
		do {
			n /= 5;
			sum += n;
		} while (n > 0);
		return sum;
	}

	//-------------------------------------------------
	// 189. https://leetcode.com/problems/rotate-array/
	//-------------------------------------------------
	void rotate(vector<int>& nums, int k) {
		if (nums.size() <= 1 || k % nums.size() == 0) {
			return;
		}
		k = k % nums.size();
		if (k < 0) {
			k += nums.size();
		}
		std::reverse(nums.begin(), nums.begin() + (nums.size() - k));
		std::reverse(nums.begin() + (nums.size() - k), nums.end());
		std::reverse(nums.begin(), nums.end());
	}

	//-------------------------------------------------
	// 190. https://leetcode.com/problems/reverse-bits/
	//-------------------------------------------------
	uint32_t reverseBits(uint32_t n) {
		uint32_t result = 0;
		int i = 32;
		while (i--) {
			result <<= 1;
			if (n & 0x01) {
				result |= 0x01;
			}
			n >>= 1;
		}
		return result;
	}

	//-------------------------------------------------
	// 191. https://leetcode.com/problems/number-of-1-bits/
	//-------------------------------------------------
	int hammingWeight(uint32_t n) {
		int result = 0;
		int i = 32;
		while (i--) {
			if (n & 0x01) {
				result += 1;
			}
			n >>= 1;
		}
		return result;
	}

	//-------------------------------------------------
	// 198. https://leetcode.com/problems/house-robber/
	//-------------------------------------------------
	int rob(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		vector<int> bests;
		bests.push_back(0);
		bests.push_back(nums[0]);
		for (int i = 1; i < nums.size(); ++i) {
			int best = max(nums[i] + bests[i - 1], bests[i]);
			bests.push_back(best);
		}

		return bests[nums.size()];
	}

	//-------------------------------------------------
	// 202. https://leetcode.com/problems/happy-number/
	//-------------------------------------------------
	bool happyTest(int n, set<int>& intSet) {
		if (intSet.count(n)) {
			return false;
		}
		intSet.insert(n);
		string str = to_string(n);
		int sum = 0;
		for (auto &c : str) {
			sum += (c - '0') * (c - '0');
		}
		if (sum == 1) {
			return true;
		}
		else {
			return happyTest(sum, intSet);
		}
	}
	bool isHappy(int n) {
		set<int> intMap;
		return happyTest(n, intMap);
	}

	//-------------------------------------------------
	// 203. https://leetcode.com/problems/remove-linked-list-elements/
	//-------------------------------------------------
	ListNode* removeElements(ListNode* head, int val) {
		if (head == NULL) {
			return NULL;
		}
		ListNode *p = head;
		ListNode *last = NULL;
		while (p) {
			if (p->val == val) {
				if (last == NULL) {
					head = p->next;
				}
				else {
					last->next = p->next;
				}
			}
			else {
				last = p;
			}
			p = p->next;
		}
		return head;
	}


	//-------------------------------------------------
	// 204. https://leetcode.com/problems/count-primes/
	//-------------------------------------------------
	int countPrimes(int n) {
		char *isPrime = new char[n];
		for (int i = 2; i < n; i++) {
			isPrime[i] = 1;
		}
		for (int i = 2; i * i < n; i++) {
			if (!isPrime[i]) {
				continue;
			}
			for (int j = i * i; j < n; j += i) {
				isPrime[j] = 0;
			}
		}
		int count = 0;
		for (int i = 2; i < n; i++) {
			if (isPrime[i]) count++;
		}
		return count;
	}

	//-------------------------------------------------
	// 205. https://leetcode.com/problems/isomorphic-strings/
	//-------------------------------------------------
	bool isIsomorphic(string s, string t) {
		unordered_map<char, char> maps, mapt;
		for (int i = 0; i < s.size(); i++) {
			if (maps.count(s[i]) == 0) {
				maps[s[i]] = t[i];
				mapt[t[i]] = 0;
			}
			else {
				if (maps[s[i]] != t[i]) {
					return false;
				}
			}
		}
		return maps.size() == mapt.size();
	}

	//-------------------------------------------------
	// 206. https://leetcode.com/problems/reverse-linked-list/
	//-------------------------------------------------
	ListNode* reverseList(ListNode* head) {
		if (head == NULL) {
			return NULL;
		}
		ListNode *p = head;
		ListNode *last = NULL;
		while (p) {
			ListNode *temp = p->next;
			p->next = last;
			last = p;
			p = temp;
		}

		return last;
	}

	//-------------------------------------------------
	// 217. https://leetcode.com/problems/contains-duplicate/
	//-------------------------------------------------
	bool containsDuplicate(vector<int>& nums) {
		unordered_set<int> s;
		for (auto &n : nums) {
			if (s.count(n) != 0) {
				return true;
			}
			s.insert(n);
		}
		return false;
	}

	//-------------------------------------------------
	// 219. https://leetcode.com/problems/contains-duplicate-ii/
	//-------------------------------------------------
	bool containsNearbyDuplicate(const vector<int>& nums, int k) {
		if (nums.empty() || k <= 0) {
			return false;
		}
		unordered_set<int> s;
		for (int i = 0; i < nums.size(); ++i) {
			if (s.count(nums[i]) != 0) {
				return true;
			}
			if (i >= k) {
				s.erase(nums[i - k]);
			}
			s.insert(nums[i]);
		}
		return false;
	}

	//-------------------------------------------------
	// 223. https://leetcode.com/problems/rectangle-area/
	//-------------------------------------------------
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		int common;
		if (C <= E || A >= G || B >= H || D <= F) {
			common = 0;
		}
		else {
			int x[4] = { A, C, E, G };
			int y[4] = { B, D, F, H };
			sort(x, x + 4);
			sort(y, y + 4);
			common = (x[2] - x[1]) * (y[2] - y[1]);
		}

		return (C - A) * (D - B) + (G - E) * (H - F) - common;
	}

	//-------------------------------------------------
	// 226. https://leetcode.com/problems/invert-binary-tree/
	//-------------------------------------------------
	TreeNode* invertTree(TreeNode* root) {
		if (root == NULL) { //||(root->left == NULL && root->right == NULL)) {
			return root;
		}
		TreeNode* temp = root->left;
		root->left = invertTree(root->right);
		root->right = invertTree(temp);
		return root;
	}

};