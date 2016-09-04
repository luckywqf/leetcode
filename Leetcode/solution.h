#pragma once

#include "common.h"

class Solution {
public:
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

		if (N2 == 0) return ((double)nums1[(N1-1)/2] + (double)nums1[N1/2])/2;  // If A2 is empty

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
	string convert(string s, int numRows) {
		if (s.empty() || numRows <= 1) {
			return s;
		}
		string result;
		int interval;
		int interval1 = (numRows - 1) * 2;
		for (int i = 0; i < numRows; ++i) {
			if (i == numRows - 1) {
				interval = interval1;
			}
			else {
				interval = i * 2;
			}
			for (int k = i; k < s.size(); k += interval) {
				result.push_back(s[k]);
				if (interval != interval1) {
					interval = interval1 - interval;
				}
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
	// 10. https://leetcode.com/problems/regular-expression-matching/
	//-------------------------------------------------
	bool matchFirst(const char *s, const char *p) {
		return (*p == *s || (*p == '.' && *s != '\0'));
	}
	bool isMatch(const char *s, const char *p) {
		if (*p == '\0') return *s == '\0';  //empty

		if (*(p + 1) != '*') {//without *
			if (!matchFirst(s, p)) return false;
			return isMatch(s + 1, p + 1);
		}
		else { //next: with a *
			if (isMatch(s, p + 2)) return true;    //try the length of 0
			while (matchFirst(s, p))       //try all possible lengths 
				if (isMatch(++s, p + 2))return true;
		}
		return false;
	}
	bool isMatch(string s, string p) {
		return isMatch(s.c_str(), p.c_str());
	}

	//-------------------------------------------------
	// 11. https://leetcode.com/problems/container-with-most-water/
	//-------------------------------------------------
	int maxArea(vector<int>& height) {
		int water = 0;
		int i = 0, j = height.size() - 1;
		while (i < j) {
			int h = min(height[i], height[j]);
			water = max(water, (j - i) * h);
			while (height[i] <= h && i < j) {
				++i;
			}
			while (height[j] <= h && i < j) {
				--j;
			}
		}
		return water;
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
	// 15. https://leetcode.com/problems/3sum/
	//-------------------------------------------------
	vector<vector<int> > threeSum(vector<int> &num) {
		vector<vector<int> > res;
		std::sort(num.begin(), num.end());
		for (int i = 0; i < num.size();) {
			int target = -num[i];
			int front = i + 1;
			int back = num.size() - 1;

			while (front < back) {
				int sum = num[front] + num[back];
				// Finding answer which start from number num[i]
				if (sum < target)
					front++;
				else if (sum > target)
					back--;
				else {
					vector<int> triplet(3, 0);
					triplet[0] = num[i];
					triplet[1] = num[front];
					triplet[2] = num[back];
					res.push_back(triplet);

					while (front < back && num[front] == triplet[1]) front++;
					while (front < back && num[back] == triplet[2]) back--;
				}
			}
			// Processing duplicates of Number 1
			while (++i < num.size() && num[i] == num[i - 1]);
		}
		return res;
	}


	//-------------------------------------------------
	// 16. https://leetcode.com/problems/3sum-closest/
	//-------------------------------------------------
	int threeSumClosest(vector<int>& nums, int target) {
		int res = INT_MAX;
		std::sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size();) {
			int left = target - nums[i];
			int front = i + 1;
			int back = nums.size() - 1;

			while (front < back) {
				int delta = nums[front] + nums[back] - left;

				if (delta < 0) {
					front++;
				}
				else if (delta > 0) {
					back--;
				}
				else {
					return target;
				}
				if (myabs(delta) < myabs(res)) {
					res = delta;
				}
			}
			// Processing duplicates of Number 1
			while (++i < nums.size() && nums[i] == nums[i - 1]);
		}
		return res + target;
	}

	//-------------------------------------------------
	// 17. https://leetcode.com/problems/letter-combinations-of-a-phone-number/
	//-------------------------------------------------
	vector<string> letterCombinations(string digits) {
		vector<string> code = {"", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
		vector<string> result;
		if (digits.empty()) {
			return result;
		}
		else if (digits.size() == 1) {
			int index = digits[0] - '1';
			for (int i = 0; i < code[index].size(); ++i) {
				result.push_back(string(1, code[index][i]));
			}
			return result;
		}
		else {
			int index = digits.back() - '1';
			digits.pop_back();
			auto pre = letterCombinations(digits);
			for (int i = 0; i < code[index].size(); ++i) {
				for (int j = 0; j < pre.size(); ++j) {
					result.push_back(pre[j] + code[index][i]);
				}
			}
			return result;
		}
	}

	//-------------------------------------------------
	// 18. https://leetcode.com/problems/4sum/
	//-------------------------------------------------
	vector<vector<int> > threeSortedSum(vector<int> &num, int target) {
		vector<vector<int> > res;
		for (int i = 0; i < num.size();) {
			int left = target - num[i];
			int front = i + 1;
			int back = num.size() - 1;

			while (front < back) {
				int sum = num[front] + num[back];
				// Finding answer which start from number num[i]
				if (sum < left)
					front++;
				else if (sum > left)
					back--;
				else {
					vector<int> triplet(3, 0);
					triplet[0] = num[i];
					triplet[1] = num[front];
					triplet[2] = num[back];
					res.push_back(triplet);

					while (front < back && num[front] == triplet[1]) front++;
					while (front < back && num[back] == triplet[2]) back--;
				}
			}
			// Processing duplicates of Number 1
			while (++i < num.size() && num[i] == num[i - 1]);
		}
		return res;
	}
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int> > res;
		std::sort(nums.begin(), nums.end());
		for (int i = nums.size() - 1; i >= 0;) {
			int left = target - nums[i];
			int last = nums[i];
			nums.pop_back();
			auto val = threeSortedSum(nums, left);
			for (auto v : val) {
				v.push_back(last);
				res.push_back(v);
			}
			while (--i >= 0 && nums[i] == last)
				nums.pop_back();
		}
		return res;
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
	// 22. https://leetcode.com/problems/generate-parentheses/
	//-------------------------------------------------
	vector<string> generateP(string s, int sum, int left) {
		vector<string> result;
		if (left == 0) {
			result.push_back(s);
			return result;
		}
		if (sum == left) {
			return generateP(s + string(left, ')'), 0, 0);
		}
		else if (sum > 0) {
			auto r = generateP(s + ')', sum - 1, left - 1);
			auto l = generateP(s + '(', sum + 1, left - 1);
			l.insert(l.end(), r.begin(), r.end());
			return l;
		}
		else {
			return generateP(s + '(', sum + 1, left - 1);
		}
	}

	vector<string> generateParenthesis(int n) {
		return generateP("", 0, n * 2);
	}

	//-------------------------------------------------
	// 23. https://leetcode.com/problems/merge-k-sorted-lists/
	//-------------------------------------------------
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		return mergeKLists(lists, 0, lists.size());
	}

	ListNode* mergeKLists(vector<ListNode*>& lists, int start, int len) {
		if (len == 0) {
			return nullptr;
		} else if (len == 1) {
			return lists[start];
		} else {
			return mergeTwoLists(mergeKLists(lists, start, len / 2), 
				mergeKLists(lists, start + len / 2, len - len / 2));
		}
	}

	//-------------------------------------------------
	// 24. https://leetcode.com/problems/swap-nodes-in-pairs/
	//-------------------------------------------------
	ListNode* swapPairs(ListNode* head) {
		if (head == nullptr) {
			return nullptr;
		}
		ListNode* p1 = head;
		if (p1->next == nullptr) {
			return p1;
		}
		ListNode* result = p1->next;
		ListNode* next = nullptr, *last = nullptr;

		while (p1 && p1->next != nullptr) {
			ListNode* p2 = p1->next;
			next = p2->next;
			p2->next = p1;
			if (last != nullptr) {
				last->next = p2;
			}
			last = p1;
			p1 = next;
		}
		last->next = next;

		return result;
	}

	//-------------------------------------------------
	// 25. https://leetcode.com/problems/remove-duplicates-from-sorted-array/
	//-------------------------------------------------
	ListNode *reverseKGroup(ListNode *head, int k) {
		if (head == NULL || k == 1) {
			return head;
		}
		int num = 0;
		ListNode preheader(-1);
		preheader.next = head;
		ListNode *cur = &preheader, *nex, *pre = &preheader;
		while (cur = cur->next)
			num++;
		while (num >= k) {
			cur = pre->next;
			nex = cur->next;
			for (int i = 1; i < k; ++i) {
				cur->next = nex->next;
				nex->next = pre->next;
				pre->next = nex;
				nex = cur->next;
			}
			pre = cur;
			num -= k;
		}
		return preheader.next;
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
	// 29. https://leetcode.com/problems/divide-two-integers/
	//-------------------------------------------------
	int divide(int dividend, int divisor) {
		if (divisor == 0) {
			return INT_MAX;
		}
		int64_t i1 = myabs((int64_t)dividend);
		int64_t i2 = myabs((int64_t)divisor);
		if (i1 < i2) {
			return 0;
		}

		string result;
		if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)) {
			result = "-";
		}
		string d1 = to_string(i1);
		string d2 = to_string(i2);

		int len1 = d1.size();
		int len2 = d2.size();
		string minuend = d1.substr(0, len2);
		int divIndex = len2 - 1;
		while (divIndex < len1) {
			int64_t step = stoll(minuend);
			while (step < i2 && divIndex + 1 < len1) {
				minuend.push_back(d1[++divIndex]);
				step = stoll(minuend);
				result.push_back('0');
			}
			if (step < i2) {
				result.push_back('0');
				break;
			}

			int bit = 0;
			while (step >= i2) {
				step -= i2;
				++bit;
			}
			result += bit + '0';
			if (++divIndex >= len1) {
				break;
			}
			minuend = to_string(step) + d1[divIndex];
		}
		int64_t v = stoll(result);
		if (v > INT_MAX || v < INT_MIN)
			return INT_MAX;
		return v;
	}

	//-------------------------------------------------
	// 30. https://leetcode.com/problems/substring-with-concatenation-of-all-words/
	//-------------------------------------------------
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> result;
		if (s.empty() || words.empty()) {
			return result;
		}
		unordered_map<string, int> wmap;
		for (auto w : words) {
			wmap[w]++;
		}
		int wc = words[0].size();
		int len = wc * words.size();
		int compares = s.size() - len;
		for (int i = 0; i <= compares; ++i) {
			unordered_map<string, int> smap;
			for (int count = 0; count < words.size(); count++) {
				string sone = s.substr(i + count * wc, wc);
				if (wmap.count(sone)) {
					smap[sone]++;
				}
				else {
					break;
				}
			}
			if (smap == wmap) {
				result.push_back(i);
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 31. https://leetcode.com/problems/next-permutation/
	//-------------------------------------------------
	void nextPermutation(vector<int>& nums) {
		if (nums.size() <= 1) {
			return;
		}
		int i;
		for (i = nums.size() - 2; i >= 0; --i) {
			if (nums[i] < nums[i + 1]) {
				break;
			}
		}
		if (i < 0) {
			sort(nums.begin(), nums.end());
		}
		else {
			int candicate = INT_MAX;
			int index = 0;
			for (int j = i + 1; j < nums.size(); ++j) {
				if (nums[j] > nums[i]) {
					if (nums[j] < candicate) {
						index = j;
						candicate = nums[j];
					}
				}
			}
			swap(nums[i], nums[index]);
			sort(nums.begin() + i + 1, nums.end());
		}
	}


	//-------------------------------------------------
	// 32. https://leetcode.com/problems/longest-valid-parentheses/
	//-------------------------------------------------
	int longestValidParentheses(string s) {
		int n = s.length(), longest = 0;
		stack<int> st;
		for (int i = 0; i < n; i++) {
			if (s[i] == '(') st.push(i);
			else {
				if (!st.empty()) {
					if (s[st.top()] == '(') st.pop();
					else st.push(i);
				}
				else st.push(i);
			}
		}
		if (st.empty()) longest = n;
		else {
			int a = n, b = 0;
			while (!st.empty()) {
				b = st.top(); st.pop();
				longest = max(longest, a - b - 1);
				a = b;
			}
			longest = max(longest, a);
		}
		return longest;
	}

	//-------------------------------------------------
	// 33. https://leetcode.com/problems/search-in-rotated-sorted-array/
	//-------------------------------------------------
	int search(vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1;
		// find the index of the smallest value using binary search.
		while (low < high ) {
			int mid = (low + high) / 2;
			if (nums[mid] > nums[high]) {
				low = mid + 1;
			} else {
				high = mid;
			}
		}

		// lo==hi is the index of the smallest value and also the number of places rotated.
		int rot = low;
		int len = nums.size();
		low = 0; 
		high = len - 1;
		
		// The usual binary search and accounting for rotation.
		while (low <= high) {
			int mid = (low + high) / 2;
			int realmid = (mid + rot) % len;
			if (nums[realmid] == target) {
				return realmid;
			}
			if (nums[realmid] < target) {
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}
		return -1;
	}

	//-------------------------------------------------
	// 34. https://leetcode.com/problems/search-for-a-range/
	//-------------------------------------------------
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> result = { -1, -1 };
		if (nums.empty()) {
			return result;
		}
		int low = 0, high = nums.size() - 1;
		int mid;
		while (low <= high) {
			mid = (low + high) / 2;
			if (nums[mid] == target) {
				break;
			} else if(nums[mid] > target) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		if (low > high) {
			return { -1, -1 };
		}
		auto mid1 = mid;
		while (low <= mid1) {
			result[0] = (low + mid1) / 2;
			if (nums[result[0]] == target) {
				if (result[0] == 0 || nums[result[0] - 1] != target) {
					break;
				}
				else {
					mid1 = result[0] - 1;
				}
			} else {
				low = result[0] + 1;
			}
		}

		while (mid <= high) {
			result[1] = (high + mid) / 2;
			if (nums[result[1]] == target) {
				if (result[1] == nums.size() - 1 || nums[result[1] + 1] != target) {
					break;
				}
				else {
					mid = result[1] + 1;
				}
			}
			else {
				high = result[1] - 1;
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 35. https://leetcode.com/problems/search-insert-position/
	//-------------------------------------------------
	int searchInsert(vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1;
		int mid;
		while (low <= high) {
			mid = (low + high) / 2;
			if (nums[mid] == target) {
				return mid;
			}
			else if (nums[mid] > target) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		if (low > high) {
			return low;
		}
	}

	//-------------------------------------------------
	// 36. https://leetcode.com/problems/valid-sudoku/
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
	// 37. https://leetcode.com/problems/sudoku-solver/
	//-------------------------------------------------
	set<int> getCandidate(int r, int c, int row[9][10], int column[9][10], int box[9][10]) {
		set<int> candidate = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		for (int i = 1; i < 10; ++i) {
			if (row[r][i]) {
				candidate.erase(i);
			}
		}
		for (int i = 1; i < 10; ++i) {
			if (column[c][i]) {
				candidate.erase(i);
			}
		}
		int boxP = r / 3 * 3 + c / 3;
		for (int i = 1; i < 10; ++i) {
			if (box[boxP][i]) {
				candidate.erase(i);
			}
		}
		return candidate;
	}

	bool solveSudokuRecursion(vector<vector<char>>& board, int i, int j, int row[9][10], int column[9][10], int box[9][10]) {
		if (i == 9) {
			return true;
		}
		if (board[i][j] == '.') {
			auto candidate = getCandidate(i, j, row, column, box);
			if (candidate.size() == 0) {
				return false;
			}
			int boxP = i / 3 * 3 + j / 3;
			for (auto k : candidate) {
				board[i][j] = k + '0';
				row[i][k] = 1;
				column[j][k] = 1;
				box[boxP][k] = 1;
				int r = (j == 8) ? i + 1 : i;
				int c = (j == 8) ? 0 : j + 1;
				if (solveSudokuRecursion(board, r, c, row, column, box)) {
					return true;
				}
				board[i][j] = '.';
				row[i][k] = 0;
				column[j][k] = 0;
				box[boxP][k] = 0;
			}
			return false;
		} else {
			if (j == 8) {
				++i; j = 0;
			}
			else {
				++j;
			}
			return solveSudokuRecursion(board, i, j, row, column, box);
		}
	}

	void solveSudoku(vector<vector<char>>& board) {
		int row[9][10] = { 0 };
		int column[9][10] = { 0 };
		int box[9][10] = { 0 };
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[i].size(); ++j) {
				if (board[i][j] != '.') {
					char c = board[i][j] - '0';
					int boxP = i / 3 * 3 + j / 3;
					row[i][c] = 1;
					column[j][c] = 1;
					box[boxP][c] = 1;
				}
			}
		}

		solveSudokuRecursion(board, 0, 0, row, column, box);
	}

	//-------------------------------------------------
	// 38. https://leetcode.com/problems/count-and-say/
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
	// 39. https://leetcode.com/problems/combination-sum/
	//-------------------------------------------------
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>> result;
		set<vector<int>> resultSet;
		sort(candidates.begin(), candidates.end());
		if (candidates.empty() || target < candidates[0]) {
			return result;
		}
		
		vector<int> one;
		int i = 0;
		for (; i < candidates.size(); ++i) {
			if (candidates[i] == target) {
				one.push_back(target);
				break;
			}
		}
		if (!one.empty()) {
			resultSet.insert(one);
		}

		for (auto v : candidates) {
			auto solution = combinationSum(candidates, target - v);
			if (solution.empty()) {
				continue;
			}
			for (auto &s : solution) {
				bool found = false;
				for (vector<int>::iterator it = s.begin(); it != s.end(); ++it) {
					if (*it > v) {
						s.insert(it, v);
						found = true;
						break;
					}
				}
				if (!found) {
					s.push_back(v);
				}
			}
			resultSet.insert(solution.begin(), solution.end());
		}
		for (auto v : resultSet) {
			result.push_back(v);
		}
		return result;
	}

	//-------------------------------------------------
	// 40. https://leetcode.com/problems/combination-sum-ii/
	//-------------------------------------------------
	vector<vector<int> > combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		vector<vector<int>> result;
		vector<int> current;
		int order = 0;
		combinationSum2P(candidates, target, order, result, current);
		return result;
	}

	void combinationSum2P(vector<int> candidates, int target, int order, vector<vector<int>> &result, vector<int> &current) {

		if (target == 0) {
			result.push_back(current);
			return ;
		}
		if (target < 0) {
			return ;
		}
	
		for (int i = order; i < candidates.size(); ++i) {
			if (i > order && candidates[i] == candidates[i - 1]) {
				continue;
			}
			current.push_back(candidates[i]);
			combinationSum2P(candidates, target - candidates[i], i + 1, result, current);
			current.pop_back();
		}

		return;
	}

	//-------------------------------------------------
	// 41. https://leetcode.com/problems/first-missing-positive/
	//-------------------------------------------------
	int firstMissingPositive(vector<int>& nums) {
		for (int i = 0; i < nums.size(); ++i) {
			while (nums[i] > 0 && nums[i] <= nums.size() && nums[nums[i] - 1] != nums[i]) {
				swap(nums[i], nums[nums[i] - 1]);
			}
		}

		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] != i + 1) {
				return i + 1;
			}
		}

		return nums.size() + 1;
	}


	//-------------------------------------------------
	// 42. https://leetcode.com/problems/trapping-rain-water/
	//-------------------------------------------------
	int trap(vector<int>& height) {
		int left = 0; 
		int right = height.size() - 1;
		int res = 0;
		int maxleft = 0, maxright = 0;
		while (left <= right) {
			if (height[left] <= height[right]) {
				if (height[left] >= maxleft) {
					maxleft = height[left];
				} else {
					res += maxleft - height[left];
				}
				left++;
			} else {
				if (height[right] >= maxright) {
					maxright = height[right];
				} else {
					res += maxright - height[right];
				}
				right--;
			}
		}
		return res;
	}


	//-------------------------------------------------
	// 43. https://leetcode.com/problems/multiply-strings/
	//-------------------------------------------------
	const unsigned char ANSII_CHAR_0 = '0';
	inline int AnsiiToNumber(char c) {
		return c - ANSII_CHAR_0;
	}
	inline char NumberToAnsii(unsigned char n) {
		return n + ANSII_CHAR_0;
	}
	string MultiplyOneBit(const string &base, unsigned int number) {
		if (number == 0)
			return "0";
		if (number == 1)
			return base;

		string result;
		result.resize(base.length() + 1);
		unsigned int carryBit = 0; //进位
		unsigned int oneBit; //当前位
		for (int i = base.length() - 1, j = base.length(); i >= 0; i--, j--) {
			oneBit = number * AnsiiToNumber(base[i]);
			oneBit += carryBit;
			result[j] = NumberToAnsii(oneBit % 10);
			carryBit = oneBit / 10;
		}
		if (carryBit == 0) {
			return result.substr(1);
		}
		else {
			result[0] = NumberToAnsii(carryBit);
			return result;
		}
	}

	//第一个数与第二个数左移leftbits位的和
	string ShiftAdd(const string &first, const string& second, unsigned int leftbits) {
		string result;
		result.resize(max(first.length(), second.length() + leftbits) + 1);
		int vindex = result.size() - 1;
		int findex = first.length() - 1;
		int sindex = second.length() - 1;
		for (unsigned int i = 0; i < leftbits; i++) {
			result[vindex--] = first[findex--];
		}
		unsigned int carryBit = 0;
		unsigned int oneBit;
		while (findex >= 0 && sindex >= 0) {
			oneBit = AnsiiToNumber(first[findex--]) + AnsiiToNumber(second[sindex--]) + carryBit;
			result[vindex--] = NumberToAnsii(oneBit % 10);
			carryBit = oneBit / 10;
		}
		while (findex >= 0) {
			oneBit = AnsiiToNumber(first[findex--]) + carryBit;
			result[vindex--] = NumberToAnsii(oneBit % 10);
			carryBit = oneBit / 10;
		}
		while (sindex >= 0) {
			oneBit = AnsiiToNumber(second[sindex--]) + carryBit;
			result[vindex--] = NumberToAnsii(oneBit % 10);
			carryBit = oneBit / 10;
		}
		if (carryBit == 0) {
			return result.substr(1);
		}
		else {
			result[0] = NumberToAnsii(carryBit);
			return result;
		}
	}
	string multiply(string num1, string num2) {
		string result("0");
		vector<string> base10(10); //为计算方便把乘数的0-9倍计算出来
		for (int i = 0; i < 10; i++) {
			base10[i] = MultiplyOneBit(num1, i);
		}
		for (int i = num2.length() - 1, j = 0; i >= 0; i--, j++) {
			result = ShiftAdd(result, base10[AnsiiToNumber(num2[i])], j);
		}
		int i = 0;
		while (result[i] == '0' && i < result.size() - 1) {
			++i;
		}
		result = result.substr(i);
		return result;
	}

	//-------------------------------------------------
	// 44. https://leetcode.com/problems/wildcard-matching/
	//-------------------------------------------------
	bool isMatchii(string s, string p) {
		const char *str = s.c_str();
		const char *pattern = p.c_str();
		const char* star = NULL;
		const char* ss = str;
		while (*str) {
			//advancing both pointers when (both characters match) or ('?' found in pattern)
			//note that *p will not advance beyond its length 
			if ((*pattern == '?') || (*pattern == *str)) { str++; pattern++; continue; }

			// * found in pattern, track index of *, only advancing pattern pointer 
			if (*pattern == '*') { star = pattern++; ss = str; continue; }

			//current characters didn't match, last pattern pointer was *, current pattern pointer is not *
			//only advancing pattern pointer
			if (star) { pattern = star + 1; str = ++ss; continue; }

			//current pattern pointer is not star, last patter pointer was not *
			//characters do not match
			return false;
		}

		//check for remaining characters in pattern
		while (*pattern == '*') { pattern++; }

		return !*pattern;
	}
	
	
	//-------------------------------------------------
	// 45. https://leetcode.com/problems/jump-game-ii/
	//-------------------------------------------------
	int jump(vector<int>& nums) {
		int maxReach = nums[0];
		int edge = 0;
		int minstep = 0;

		for (int i = 1; i < nums.size(); i++) {
			if (i > edge) {
				minstep += 1;
				edge = maxReach;
				if (edge > nums.size() - 1)
					return minstep;
			}
			maxReach = std::max(maxReach, nums[i] + i);
			if (maxReach == i && i < nums.size() - 1)
				return -1;
		}

		return minstep;
	}
	
	
	// 46. https://leetcode.com/problems/permutations/
	//-------------------------------------------------
	template <class T> 
	vector<vector<T>> permute(vector<T>& nums) {
		vector<vector<T>> result;
		if (nums.empty()) {
			return result;
		}
		if (nums.size() == 1) {
			result.push_back(nums);
			return result;
		}
		else {
			auto last = nums.back();
			nums.pop_back();
			auto lefts = permute(nums);
			for (auto v : lefts) {
				for (int i = 0; i <= v.size(); ++i) {
					auto temp = v;
					temp.insert(temp.begin() + i, last);
					result.push_back(temp);
				}
			}
			return result;
		}
	}

	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> result;
		if (nums.empty()) {
			return result;
		}
		if (nums.size() == 1) {
			result.push_back(nums);
			return result;
		} else {
			int last = nums.back();
			nums.pop_back();
			auto lefts = permute(nums);
			for (auto v : lefts) {
				for (int i = 0; i <= v.size(); ++i) {
					auto temp = v;
					temp.insert(temp.begin() + i, last);
					result.push_back(temp);
				}
			}
			return result;
		}
	}

	//-------------------------------------------------
	// 47. https://leetcode.com/problems/permutations-ii/
	//-------------------------------------------------
	void recursion(vector<int> num, int i, int j, vector<vector<int> > &res) {
		if (i == j - 1) {
			res.push_back(num);
			return;
		}
		for (int k = i; k < j; k++) {
			if (i != k && num[i] == num[k]) continue;
			swap(num[i], num[k]);
			recursion(num, i + 1, j, res);
		}
	}
	vector<vector<int> > permuteUnique(vector<int> &num) {
		sort(num.begin(), num.end());
		vector<vector<int> >res;
		recursion(num, 0, num.size(), res);
		return res;
	}

	//-------------------------------------------------
	// 48. https://leetcode.com/problems/rotate-image/
	//-------------------------------------------------
	void rotate(vector<vector<int>>& matrix) {
		for (int i = 0, j = matrix.size() - 1; i < j; ++i, --j) {
			swap(matrix[i], matrix[j]);
		}
		int n = matrix.size();
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				swap(matrix[i][j], matrix[j][i]);
			}
		}
	}


	//-------------------------------------------------
	// 49. https://leetcode.com/problems/anagrams/
	//-------------------------------------------------
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		unordered_map<string, vector<string>> result;
		for (auto str : strs) {
			auto copy = str;
			sort(copy.begin(), copy.end());
			result[copy].push_back(str);
		}
		vector<vector<string>> value;
		for (auto x : result) {
			sort(x.second.begin(), x.second.end());
			value.push_back(x.second); 
		}
		return value;
	}

	//-------------------------------------------------
	// 50. https://leetcode.com/problems/powx-n/
	//-------------------------------------------------
	double myPow(double x, int n) {
		if (n == 0) {
			return 1;
		}
		else if (n < 0) {
			x = 1 / x;
			n = -n;
		}
		return myPowPos(x, n);
	}

	double myPowPos(double x, int n) {
		if (n == 1) {
			return x;
		}
		double result = x;

		const int maxRange = INT_MAX / 2;
		int maxi = min(n / 2, maxRange);
		int i = 1;
		for (; i < maxi; i *= 2) {
			result *= result;
		}
		return result * myPowPos(x, n - i);
	}



	//-------------------------------------------------
	// 51. https://leetcode.com/problems/n-queens/
	//-------------------------------------------------
	vector<vector<string> > solveNQueens(int n) {
		vector<vector<string>> res;
		vector<string> nQueens(n, string(n, '.'));
		solveNQueens(res, nQueens, 0, n);
		return res;
	}
	void solveNQueens(vector<vector<string>> &res, vector<string> &nQueens, int row, int &n) {
		if (row == n) {
			res.push_back(nQueens);
			return;
		}
		for (int col = 0; col != n; ++col) {
			if (isValid(nQueens, row, col, n)) {
				nQueens[row][col] = 'Q';
				solveNQueens(res, nQueens, row + 1, n);
				nQueens[row][col] = '.';
			}
		}
	}
	bool isValid(vector<string> &nQueens, int row, int col, int &n) {
		//check if the column had a queen before.
		for (int i = 0; i != row; ++i) {
			if (nQueens[i][col] == 'Q')
				return false;
		}
		//check if the 45° diagonal had a queen before.
		for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
			if (nQueens[i][j] == 'Q')
				return false;
		}
		//check if the 135° diagonal had a queen before.
		for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
			if (nQueens[i][j] == 'Q')
				return false;
		}
		return true;
	}


	//-------------------------------------------------
	// 52. https://leetcode.com/problems/n-queens-ii/
	//-------------------------------------------------
	int totalNQueens(int n) {
		return solveNQueens(n).size();
	}


	//-------------------------------------------------
	// 53. https://leetcode.com/problems/maximum-subarray/
	//-------------------------------------------------
	int maxSubArray(vector<int>& nums) {
		int max = nums[0];
		vector<int> sum(nums.size());
		sum[0] = nums[0];
		for (int i = 1; i < nums.size(); ++i) {
			if (sum[i - 1] < 0) {
				sum[i] = nums[i];
			}
			else {
				sum[i] = sum[i - 1] + nums[i];
			}
			if (max < sum[i]) {
				max = sum[i];
			}
		}
		return max;
	}

	//-------------------------------------------------
	// 54. https://leetcode.com/problems/spiral-matrix/
	//-------------------------------------------------
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> result;
		if (matrix.empty()) {
			return result;
		}
		int rowIndex = 0, columnIndex = 0;
		int rowMin = 0, columnMin = 0;
		int rowMax = matrix.size() - 1;
		int columnMax = matrix[0].size() - 1;
		while (rowMin <= rowMax && columnMin <= columnMax) {
			for (columnIndex = columnMin; columnIndex <= columnMax; ++columnIndex) {
				result.push_back(matrix[rowIndex][columnIndex]);
			}
			--columnIndex;
			--columnMax;

			++rowMin;
			for (rowIndex = rowMin; rowIndex <= rowMax; ++rowIndex) {
				result.push_back(matrix[rowIndex][columnIndex]);
			}
			--rowIndex;
			--rowMax;

			if (rowIndex >= rowMin) {
				for (columnIndex = columnMax; columnIndex >= columnMin; --columnIndex) {
					result.push_back(matrix[rowIndex][columnIndex]);
				}
				++columnIndex;
			}
			++columnMin;

			if (columnIndex <= columnMax) {
				for (rowIndex = rowMax; rowIndex >= rowMin; --rowIndex) {
					result.push_back(matrix[rowIndex][columnIndex]);
				}
				++rowIndex;
			}
		}
		return result;
	}


	//-------------------------------------------------
	// 55. https://leetcode.com/problems/jump-game/
	//-------------------------------------------------
	bool canJump(vector<int>& nums) {
		int i = 0;
		for (int reach = 0; i < nums.size() && i <= reach; ++i)
			reach = max(i + nums[i], reach);
		return i == nums.size();
	}


	//-------------------------------------------------
	// 56. https://leetcode.com/problems/merge-intervals/
	//-------------------------------------------------
	vector<Interval> merge(vector<Interval>& intervals) {
		if (intervals.size() <= 1) {
			return intervals;
		}
		sort(intervals.begin(), intervals.end(), 
			[](const Interval &f, const Interval &s) {
			return f.start < s.start;
		});
		vector<Interval> result;
		Interval interval = intervals[0];
		for (int i = 1; i < intervals.size(); ++i) {
			if (intervals[i].start > interval.end) {
				result.push_back(interval);
				interval = intervals[i];
			} else if (intervals[i].end > interval.end) {
				interval.end = intervals[i].end;
			}
		}
		result.push_back(interval);
		return result;
	}


	//-------------------------------------------------
	// 57. https://leetcode.com/problems/insert-interval/
	//-------------------------------------------------
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		intervals.push_back(newInterval);
		return merge(intervals);
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
	// 59. https://leetcode.com/problems/spiral-matrix-ii/
	//-------------------------------------------------
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> result;
		for (int i = 0; i < n; ++i) {
			result.emplace_back(n, 0);
		}
		int num = 1;
		int rowIndex = 0, columnIndex = 0;
		int rowMin = 0, columnMin = 0;
		int rowMax = n - 1;
		int columnMax = n - 1;
		while (rowMin <= rowMax && columnMin <= columnMax) {
			for (columnIndex = columnMin; columnIndex <= columnMax; ++columnIndex) {
				result[rowIndex][columnIndex] = num++;
			}
			--columnIndex;
			--columnMax;

			++rowMin;
			for (rowIndex = rowMin; rowIndex <= rowMax; ++rowIndex) {
				result[rowIndex][columnIndex] = num++;
			}
			--rowIndex;
			--rowMax;

			if (rowIndex >= rowMin) {
				for (columnIndex = columnMax; columnIndex >= columnMin; --columnIndex) {
					result[rowIndex][columnIndex] = num++;
				}
				++columnIndex;
			}
			++columnMin;

			if (columnIndex <= columnMax) {
				for (rowIndex = rowMax; rowIndex >= rowMin; --rowIndex) {
					result[rowIndex][columnIndex] = num++;
				}
				++rowIndex;
			}
		}
		return result;
	}


	//-------------------------------------------------
	// 60. https://leetcode.com/problems/permutation-sequence/
	//-------------------------------------------------
	string getPermutation(int n, int k) {
		string desOrder;
		for (int i = 1; i <= n; ++i) {
			desOrder.push_back('0' + i);
		}

		string result;
		int nextp = 1, p = n - 1;
		for (int i = 2; i < n; ++i) {
			nextp *= i;
		}

		while (p > 0) {
			int index = (k - 1) / nextp;
			k = (k - 1) % nextp + 1;
			nextp /= p;
			--p;
			result.push_back(desOrder[index]);
			desOrder.erase(desOrder.begin() + index);
		}
		result.push_back(desOrder[0]);
		return result;
	}

	//-------------------------------------------------
	// 61. https://leetcode.com/problems/rotate-list/
	//-------------------------------------------------
	ListNode* rotateRight(ListNode* head, int k) {
		if (head == nullptr) {
			return head;
		}
		int len = GetListLength(head);
		k = k % len;
		if (k == 0) {
			return head;
		}

		ListNode *end = head;
		int index = 1;
		while (index < k) {
			++index;
			end = end->next;
		}
		ListNode *result = head;
		ListNode *last = nullptr;
		while (end->next) {
			end = end->next;
			last = result;
			result = result->next;
		}
		last->next = nullptr;
		ListNode *p = result;
		while (p->next) {
			p = p->next;
		}
		p->next = head;
		return result;
	}


	//-------------------------------------------------
	// 62. https://leetcode.com/problems/unique-paths/
	//-------------------------------------------------
	int uniquePaths(int m, int n) {
		vector<vector<int>> paths;
		for (int i = 0; i < m; ++i) {
			paths.emplace_back(n, 1);
		}
		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				paths[i][j] = paths[i - 1][j] + paths[i][j - 1];
			}
		}
		return paths[m - 1][n - 1];
	}

	//-------------------------------------------------
	// 63. https://leetcode.com/problems/unique-paths-ii/
	//-------------------------------------------------
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		vector<vector<int>> paths = obstacleGrid;
		if (obstacleGrid.empty()) {
			return 0;
		}
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (obstacleGrid[i][j] == 1) {
					paths[i][j] = 0;
				}
				else {
					if (i == 0 && j == 0) {
						paths[i][j] = 1;
					}
					else if (i == 0) {
						paths[i][j] = paths[i][j - 1];
					}
					else if (j == 0) {
						paths[i][j] = paths[i - 1][j];
					}
					else {
						paths[i][j] = paths[i - 1][j] + paths[i][j - 1];
					}
				}
			}
		}
		return paths[m - 1][n - 1];
	}


	//-------------------------------------------------
	// 64. https://leetcode.com/problems/minimum-path-sum/
	//-------------------------------------------------
	int minPathSum(vector<vector<int>>& grid) {
		if (grid.empty()) {
			return 0;
		}
		int m = grid.size();
		int n = grid[0].size();
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == 0 && j != 0) {
					grid[i][j] += grid[i][j - 1];
				}
				else if (j == 0 && i != 0) {
					grid[i][j] += grid[i - 1][j];
				}
				else if (i != 0 && j != 0) {
					grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
				}
			}
		}
		return grid[m - 1][n - 1];
	}

	//-------------------------------------------------
	// 65. https://leetcode.com/problems/valid-number/
	//-------------------------------------------------
	bool isNumber(string s) {
		int i = 0;
		// skip the whilespaces
		while (isspace(s[i]))i++;

		// check the significand
		if (s[i] == '+' || s[i] == '-') i++; // skip the sign if exist

		int n_nm, n_pt;
		for (n_nm = 0, n_pt = 0; (s[i] <= '9' && s[i] >= '0') || s[i] == '.'; i++)
			s[i] == '.' ? n_pt++ : n_nm++;
		if (n_pt > 1 || n_nm < 1) // no more than one point, at least one digit
			return false;

		// check the exponent if exist
		if (s[i] == 'e') {
			i++;
			if (s[i] == '+' || s[i] == '-') i++; // skip the sign

			int n_nm = 0;
			for (; s[i] >= '0' && s[i] <= '9'; i++, n_nm++);
			if (n_nm < 1)
				return false;
		}

		// skip the trailing whitespaces
		while (isspace(s[i]))i++;

		return s[i] == 0;  // must reach the ending 0 of the string
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
	// 68. https://leetcode.com/problems/text-justification/
	//-------------------------------------------------
	vector<int> evenSpaces(int spaces, int block, bool lastLine) {
		vector<int> result;
		int space;
		for (int i = block - 1; i > 0; --i) {
			space = lastLine ? 1 : spaces / i;
			result.insert(result.begin(), space);
			spaces -= space;
		}
		result.push_back(spaces);
		return result;
	}

	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> result;
		int index = 0;
		while (index < words.size()) {
			string line;
			int lineWords(0), lineLeft(maxWidth), lineSpaces(maxWidth);
			while (index < words.size() && (int)words[index].size() <= lineLeft) {
				lineLeft -= words[index].size() + 1;
				lineSpaces -= words[index].size();
				lineWords++;
				index++;
			}
			auto spaces = evenSpaces(lineSpaces, lineWords, index >= words.size());
			for (int i = 0; i < lineWords; i++) {
				line += words[index - lineWords + i];
				line += string(spaces[i], ' ');
			}
			result.push_back(line);
		}
		return result;
	}


	//-------------------------------------------------
	// 69. https://leetcode.com/problems/sqrtx/
	//-------------------------------------------------
	int mySqrt(int x) {
		int low = 0, high = x;
		int64_t mid, mid2;
		while (low <= high) {
			mid = (low + high) / 2;
			mid2 = mid * mid;
			if (mid2 == x) {
				return mid;
			}
			else if (mid2 < x) {
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}
		return high;
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
	// 71. https://leetcode.com/problems/simplify-path/
	//-------------------------------------------------
	string simplifyPath(string path) {
		vector<string> spath;
		string dirName;
		for (int i = 0; i < path.size(); ++i) {
			if (path[i] == '/') {
				if (!dirName.empty()) {
					spath.push_back(dirName);
					dirName.clear();
				}
			}
			else if (path[i] == '.') {
				++i;
				if (path[i] == '.' && (i + 1 == path.size() || path[i + 1] == '/')) {
					if (!spath.empty()) {
						spath.pop_back();
					}
				}
				else if (path[i] != '/' && path[i] != '\0') {
					dirName.push_back('.');
					while (i < path.size() && path[i] != '/') {
						dirName.push_back(path[i]);
						++i;
					}
					--i;
				}
			}
			else {
				dirName.push_back(path[i]);
			}
		}
		if (!dirName.empty()) {
			spath.push_back(dirName);
		}
		string result = "/";
		for (int i = 0; i < spath.size(); ++i) {
			if (i != 0) {
				result += '/';
			}
			result += spath[i];
		}
		return result;
	}

	//-------------------------------------------------
	// 72. https://leetcode.com/problems/edit-distance/
	//-------------------------------------------------
	int minDistance(string word1, string word2) {
		int m = word1.length(), n = word2.length();
		vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
		for (int i = 1; i <= m; i++)
			dp[i][0] = i;
		for (int j = 1; j <= n; j++)
			dp[0][j] = j;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (word1[i - 1] == word2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				} else {
					dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
				}
			}
		}
		return dp[m][n];
	}


	//-------------------------------------------------
	// 73. https://leetcode.com/problems/set-matrix-zeroes/
	//-------------------------------------------------
	void setZeroes(vector<vector<int> > &matrix) {
		//把信息保存在首行和首列，他们只影响所在行和所在列，行影响行，列影响列
		int col0 = 1, rows = matrix.size(), cols = matrix[0].size();

		for (int i = 0; i < rows; i++) {
			if (matrix[i][0] == 0) col0 = 0;
			for (int j = 1; j < cols; j++) {
				if (matrix[i][j] == 0) {
					matrix[i][0] = matrix[0][j] = 0;
				}
			}
		}

		for (int i = rows - 1; i >= 0; i--) {
			for (int j = cols - 1; j >= 1; j--) {
				if (matrix[i][0] == 0 || matrix[0][j] == 0)
					matrix[i][j] = 0;
			}
			if (col0 == 0) matrix[i][0] = 0;
		}
	}


	//-------------------------------------------------
	// 74. https://leetcode.com/problems/search-a-2d-matrix/
	//-------------------------------------------------
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty()) {
			return false;
		}
		int m = matrix.size();
		int n = matrix[0].size();
		int low = 0, high = m * n - 1;
		int mid, row, column;
		while (low <= high) {
			mid = (low + high) / 2;
			row = mid / n;
			column = mid % n;
			if (matrix[row][column] == target) {
				return true;
			}
			else if(matrix[row][column] > target) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		return false;
	}

	//-------------------------------------------------
	// 75. https://leetcode.com/problems/sort-colors/
	//-------------------------------------------------
	void sortColors(vector<int>& nums) {
		int red0 = 0, white1 = 0, blue2 = 0;
		for (auto n : nums) {
			switch (n)
			{
			case 0:
				++red0;
				break;
			case 1:
				++white1;
				break;
			case 2:
				++blue2;
				break;
			}
		}
		int i = 0;
		for (; i < red0; ++i) {
			nums[i] = 0;
		}
		white1 += red0;
		for (; i < white1; ++i) {
			nums[i] = 1;
		}
		for (; i < nums.size(); ++i) {
			nums[i] = 2;
		}
	}

	//-------------------------------------------------
	// 76. https://leetcode.com/problems/minimum-window-substring/
	//-------------------------------------------------
	string minWindow(string s, string t) {
		vector<int> map(128, 0);
		for (auto c : t) map[c]++;
		int counter = t.size();
		int begin = 0, end = 0;
		int winLen = INT_MAX, head = 0;
		while (end < s.size()) {
			if (map[s[end++]]-- > 0) {
				counter--; //in t
			}
			while (counter == 0) { //valid
				if (end - begin < winLen) {
					winLen = end - (head = begin);
				}
				if (map[s[begin++]]++ == 0) {
					counter++;  //make it invalid
				}
			}
		}
		return winLen == INT_MAX ? "" : s.substr(head, winLen);
	}

	//-------------------------------------------------
	// 77. https://leetcode.com/problems/combinations/
	//-------------------------------------------------
	vector<vector<int>> combineP(const vector<int>& nums, int start, int k) {
		vector<vector<int>> out;
		if (start >= nums.size() || k == 0) {
			return out;
		}
		if (k == 1) {
			for (int i = start; i < nums.size(); ++i) {
				out.emplace_back(1, nums[i]);
			}
		}
		else {
			out = combineP(nums, start + 1, k - 1);
			for (auto &o : out) {
				o.insert(o.begin(), nums[start]);
			}
			auto left = combineP(nums, start + 1, k);
			out.insert(out.end(), left.begin(), left.end());
		}
		return out;
	}

	vector<vector<int>> combine(int n, int k) {
		if (k > n) {
			k = n;
		}
		vector<int> nums;
		for (int i = 1; i <= n; ++i) {
			nums.push_back(i);
		}
		return combineP(nums, 0, k);
	}

	//-------------------------------------------------
	// 78. https://leetcode.com/problems/subsets/
	//-------------------------------------------------
	vector<vector<int>> subsets(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> result;
		vector<int> one;
		int maxN = pow(2, nums.size());
		for (int i = 0; i < maxN; ++i) {
			int oneV = i;
			one.clear();
			for (int j = 0; j < nums.size(); ++j) {
				if (oneV & 0x01) {
					one.push_back(nums[j]);
				}
				oneV >>= 1;
			}
			result.push_back(one);
		}
		return result;
	}

	//-------------------------------------------------
	// 79. https://leetcode.com/problems/word-search/
	//-------------------------------------------------
	bool exist(vector<vector<char>> &board, string word) {
		int m = board.size();
		int n = board[0].size();
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				if (isFoundBoard(board, m, n, word.c_str(), x, y))
					return true;
			}
		}
		return false;
	}
	bool isFoundBoard(vector<vector<char>> &board, int m, int n, const char* w, int x, int y)
	{
		if (x < 0 || y<0 || x >= m || y >= n || board[x][y] == '\0' || *w != board[x][y])
			return false;
		if (*(w + 1) == '\0')
			return true;
		char t = board[x][y];
		board[x][y] = '\0';
		if (isFoundBoard(board, m, n, w + 1, x - 1, y) || isFoundBoard(board, m, n, w + 1, x + 1, y) ||
			isFoundBoard(board, m, n, w + 1, x, y - 1) || isFoundBoard(board, m, n, w + 1, x, y + 1))
			return true;
		board[x][y] = t;
		return false;
	}

	//-------------------------------------------------
	// 80. https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
	//-------------------------------------------------
	int removeDuplicatesii(vector<int>& nums) {
		int index = 0;
		for (int old = 0; old < nums.size(); ++old) {
			if (index > 1 && nums[old] == nums[index - 2]) {
				continue;
			}
			nums[index++] = nums[old];
		}
		return index;
	}


	//-------------------------------------------------
	// 81. https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
	//-------------------------------------------------
	bool searchii(vector<int>& nums, int target) {
		for (auto n : nums) {
			if (target == n) {
				return true;
			}
		}
		return false;
	}

	//-------------------------------------------------
	// 82. https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
	//-------------------------------------------------
	ListNode* deleteDuplicatesii(ListNode* head) {
		if (head == nullptr) {
			return head;
		}
		ListNode result(0);
		result.next = head;
		ListNode* last = &result;
		ListNode *p = head->next;
		while (p) {
			bool lastDup = false;
			while (p && p->val == last->next->val) {
				p = p->next;
				lastDup = true;
			}
			if (lastDup) {
				last->next = p;
				if (p) {
					p = p->next;
				}
				continue;
			}
			last = last->next;
			last->next = p;
			p = p->next;
		}
		return result.next;
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
	// 84. https://leetcode.com/problems/largest-rectangle-in-histogram/
	//-------------------------------------------------
	int largestRectangleArea(vector<int>& heights) {
		int ret = 0;
		heights.push_back(0);
		vector<int> index;

		for (int i = 0; i < heights.size(); i++) {
			while (index.size() > 0 && heights[index.back()] >= heights[i]) {
				int h = heights[index.back()];
				index.pop_back();

				int sidx = index.size() > 0 ? index.back() : -1;
				if (h * (i - sidx - 1) > ret) {
					ret = h * (i - sidx - 1);
				}
			}
			index.push_back(i);
		}

		return ret;
	}
	
	//-------------------------------------------------
	// 85. https://leetcode.com/problems/maximal-rectangle/
	//-------------------------------------------------
	int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.empty()) {
			return 0;
		}
		int m = matrix.size();
		int n = matrix[0].size();
		vector<int> left(n, 0), right(n, n), height(n, 0);
		int maxA = 0;
		for (int i = 0; i < m; i++) {
			int cur_left = 0, cur_right = n;
			for (int j = 0; j < n; j++) { // compute height (can do this from either side)
				if (matrix[i][j] == '1') height[j]++;
				else height[j] = 0;
			}
			for (int j = 0; j < n; j++) { // compute left (from left to right)
				if (matrix[i][j] == '1') left[j] = std::max(left[j], cur_left);
				else { 
					left[j] = 0; 
					cur_left = j + 1; 
				}
			}
			// compute right (from right to left)
			for (int j = n - 1; j >= 0; j--) {
				if (matrix[i][j] == '1') right[j] = std::min(right[j], cur_right);
				else { 
					right[j] = n; 
					cur_right = j; 
				}
			}
			// compute the area of rectangle (can do this from either side)
			for (int j = 0; j < n; j++) {
				maxA = std::max(maxA, (right[j] - left[j]) * height[j]);
			}
		}
		return maxA;
	}


	//-------------------------------------------------
	// 86. https://leetcode.com/problems/partition-list/
	//-------------------------------------------------
	ListNode* partition(ListNode* head, int x) {
		if (head == nullptr) {
			return head;
		}

		ListNode result(0);
		ListNode *p = &result;
		ListNode *h = head;
		while (h) {
			if (h->val < x) {
				p->next = new ListNode(h->val);
				p = p->next;
			}
			h = h->next;
		}
		h = head;
		while (h) {
			if (h->val >= x) {
				p->next = new ListNode(h->val);
				p = p->next;
			}
			h = h->next;
		}
		return result.next;
	}

	//-------------------------------------------------
	// 87. https://leetcode.com/problems/scramble-string/
	//-------------------------------------------------
	bool isScramble(string s1, string s2) {
		if (s1 == s2)
			return true;

		int len = s1.length();
		int count[26] = { 0 };
		for (int i = 0; i < len; i++) {
			count[s1[i] - 'a']++;
			count[s2[i] - 'a']--;
		}

		for (int i = 0; i < 26; i++) {
			if (count[i] != 0)
				return false;
		}

		for (int i = 1; i <= len - 1; i++) {
			if (isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i)))
				return true;
			if (isScramble(s1.substr(0, i), s2.substr(len - i)) && isScramble(s1.substr(i), s2.substr(0, len - i)))
				return true;
		}
		return false;
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
	// 89. https://leetcode.com/problems/gray-code/
	//-------------------------------------------------
	vector<int> grayCode(int n) {
		vector<int> result = {0};
		int pow2 = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = result.size() - 1; j >= 0; --j) {
				result.push_back(result[j] + pow2);
			}
			pow2 <<= 1;
		}
		return result;
	}


	//-------------------------------------------------
	// 90. https://leetcode.com/problems/subsets-ii/
	//-------------------------------------------------
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		vector<vector<int>> totalset = { {} };
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size();) {
			int count = 0; // num of elements are the same
			while (count + i < nums.size() && nums[count + i] == nums[i])  
				count++;
			int previousN = totalset.size();
			for (int k = 0; k < previousN; k++) {
				vector<int> instance = totalset[k];
				for (int j = 0; j < count; j++) {
					instance.push_back(nums[i]);
					totalset.push_back(instance);
				}
			}
			i += count;
		}
		return totalset;
	}

	//-------------------------------------------------
	// 91. https://leetcode.com/problems/decode-ways/
	//-------------------------------------------------
	int numDecodings(string s) {
		if (s.empty()) {
			return 0;
		}
		vector<int> decodeArray(s.size() + 1, 0);
		decodeArray[0] = 1;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] > '0') {
				decodeArray[i + 1] = decodeArray[i];
			}
			if (i > 0) {
				if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] < '7')) {
					decodeArray[i + 1] += decodeArray[i - 1];
				}
			}
		}
		return decodeArray[s.size()];
	}


	//-------------------------------------------------
	// 92. https://leetcode.com/problems/reverse-linked-list-ii/
	//-------------------------------------------------
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		if (head == nullptr || m == n) {
			return head;
		}
		ListNode result(0);
		result.next = head;
		ListNode *p = &result;
		int i = 1;
		for (; i < m; ++i) {
			p = p->next;
		}
		ListNode *end = p->next;
		ListNode *rend = end;
		ListNode *rc = end->next;
		ListNode *temp;
		for (; rc && i < n; ++i) {
			p->next = rc;
			temp = rc->next;
			rc->next = end;
			end = rc;
			rc = temp;
		}
		if (rend) {
			rend->next = rc;
		}
		return result.next;
	}

	//-------------------------------------------------
	// 93. https://leetcode.com/problems/restore-ip-addresses/
	//-------------------------------------------------
	void restoreIpSecursion(string s, int start, int num, string& ip, vector<string>& out) {
		if (num == 1) {
			string subIp = s.substr(start);
			if ((subIp.size() > 1 && subIp[0] == '0')
				|| subIp.size() > 3 || subIp.size() < 0) {
				return;
			}
			int iip = stoi(subIp);
			if (iip >= 0 && iip <= 255) {
				ip += ".";
				ip += subIp;
				out.push_back(ip);
			}
			return;
		}

		int maxLen = s.size() - start - num + 1;
		maxLen = min(3, maxLen);
		for (int i = 1; i <= maxLen; ++i) {
			string subIp = s.substr(start, i);

			int iip = stoi(subIp);
			if ((subIp.size() > 1 && subIp[0] == '0')
				||iip > 255 || iip < 0) {
				continue;
			}
			int ipLen = ip.size();
			if (!ip.empty()) {
				ip.push_back('.');
			}
			ip += subIp;
			restoreIpSecursion(s, start + i, num - 1, ip, out);
			ip.resize(ipLen);
		}
	}

	vector<string> restoreIpAddresses(string s) {
		vector<string> result;
		string ip;
		restoreIpSecursion(s, 0, 4, ip, result);
		return result;
	}


	//-------------------------------------------------
	// 94. https://leetcode.com/problems/binary-tree-inorder-traversal/
	//-------------------------------------------------
	vector<int> inorderTraversal(TreeNode *root) {
		vector<int> result;
		stack<TreeNode *> stack;
		TreeNode *pCurrent = root;

		while (!stack.empty() || pCurrent)
		{
			if (pCurrent)
			{
				stack.push(pCurrent);
				pCurrent = pCurrent->left;
			}
			else
			{
				TreeNode *pNode = stack.top();
				result.push_back(pNode->val);
				stack.pop();
				pCurrent = pNode->right;
			}
		}
		return result;
	}


	//-------------------------------------------------
	// 95. https://leetcode.com/problems/unique-binary-search-trees-ii/
	//-------------------------------------------------
	vector<TreeNode*> generateTrees(int start, int end) {
		vector<TreeNode*> result;
		if (start > end) {
			result.push_back(nullptr);
			return result;
		}
		for (int i = start; i <= end; ++i) {
			vector<TreeNode*> left, right;
			left = generateTrees(start, i - 1);
			right = generateTrees(i + 1, end);
			for (auto l : left) {
				for (auto r : right) {
					TreeNode *root = new TreeNode(i);
					root->left = l;
					root->right = r;
					result.push_back(root);
				}
			}
		}
		return result;
	}

	vector<TreeNode*> generateTrees(int n) {
		return generateTrees(1, n);
	}


	//-------------------------------------------------
	// 96. https://leetcode.com/problems/unique-binary-search-trees/
	//-------------------------------------------------
	int numTrees(int n) {
		static int treeDic[4] = { 0, 1, 2, 5 };
		if (n <= 3) {
			return treeDic[n];
		}
		int sum = 0;
		int maxRange = n / 2;
		int i = 1;
		for (i = 1; i <= maxRange; ++i) {
			int left = i - 1 > 0 ? numTrees(i - 1) : 1;
			int right = numTrees(n - i);
			sum += left * right;
		}
		sum *= 2;
		if (n % 2 == 1) {
			int left = i - 1 > 0 ? numTrees(i - 1) : 1;
			int right = numTrees(n - i);
			sum += left * right;
		}
		return sum;
	}


	//-------------------------------------------------
	// 97. https://leetcode.com/problems/interleaving-string/
	//-------------------------------------------------
	bool isInterleave(string s1, string s2, string s3) {
		if (s3.length() != s1.length() + s2.length())
			return false;

		vector<vector<bool>> table(s1.length() + 1, vector<bool>(s2.length() + 1));

		for (int i = 0; i < s1.length() + 1; i++)
			for (int j = 0; j < s2.length() + 1; j++) {
				if (i == 0 && j == 0)
					table[i][j] = true;
				else if (i == 0)
					table[i][j] = (table[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
				else if (j == 0)
					table[i][j] = (table[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
				else
					table[i][j] = (table[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (table[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
			}

		return table[s1.length()][s2.length()];
	}


	//-------------------------------------------------
	// 98. https://leetcode.com/problems/validate-binary-search-tree/
	//-------------------------------------------------
	bool validAndGetBST(TreeNode* root, int& minE, int& maxE) {
		minE = maxE = root->val;
		if (root->left == nullptr && root->right == nullptr) {
			return true;
		}
		int leftMax, leftMin, rightMax, rightMin;
		if (root->left) {
			if (!validAndGetBST(root->left, leftMin, leftMax)) {
				return false;
			}
			if (leftMax >= root->val) {
				return false;
			}
			minE = leftMin;
		}

		if (root->right) {
			if (!validAndGetBST(root->right, rightMin, rightMax)) {
				return false;
			}
			if (rightMin <= root->val) {
				return false;
			}
			maxE = rightMax;
		}
		return true;
	}
	bool isValidBST(TreeNode* root) {
		if (root == nullptr) {
			return true;
		}
		int m, n;
		return validAndGetBST(root, m, n);
	}


	//-------------------------------------------------
	// 99. https://leetcode.com/problems/recover-binary-search-tree/
	//-------------------------------------------------
	void recoverTree(TreeNode* root) {
		TreeNode *first = nullptr, *second = nullptr;
		TreeNode *pre = new TreeNode(INT_MIN);
		travelTree(root, &first, &second, &pre);
		swap(first->val, second->val);
	}
	void travelTree(TreeNode *root, TreeNode **first, TreeNode **second, TreeNode **pre) {
		if (root == nullptr) {
			return;
		}
		
		travelTree(root->left, first, second, pre);

		if (*first == nullptr && (*pre)->val >= root->val) {
			*first = *pre;
		}
		if (*first != nullptr && (*pre)->val >= root->val) {
			*second = root;
		}
		*pre = root;

		travelTree(root->right, first, second, pre);
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
	// 103. https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
	//-------------------------------------------------
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> result;
		if (root == nullptr) {
			return result;
		}
		bool direction = true;
		vector<int> level;
		queue<TreeNode*> treeQueue;
		treeQueue.push(root);
		treeQueue.push(nullptr);
		while (!treeQueue.empty()) {
			auto elem = treeQueue.front();
			treeQueue.pop();
			if (elem == nullptr) {
				if (!treeQueue.empty()) {
					treeQueue.push(nullptr);
				}
				if (!direction) {
					std::reverse(level.begin(), level.end());
				}
				result.push_back(level);
				level.clear();
				direction = !direction;
				continue;
			}
			level.push_back(elem->val);
			if (elem->left) {
				treeQueue.push(elem->left);
			}
			if (elem->right) {
				treeQueue.push(elem->right);
			}
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
	// 105. https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
	//-------------------------------------------------
	TreeNode* buildTreeRecursion(vector<int>& preorder, int pbegin, int pend, 
								vector<int>& inorder, int ibegin, int iend) {
		if (pbegin >= pend) {
			return nullptr;
		}
		TreeNode *root = new TreeNode(preorder[pbegin]);
		int index = ibegin;
		for (; index < iend; ++index) {
			if (inorder[index] == preorder[pbegin]) {
				break;
			}
		}
		index -= ibegin;
		root->left = buildTreeRecursion(preorder, pbegin + 1, pbegin + 1 + index, 
										inorder, ibegin, ibegin + index);
		root->right = buildTreeRecursion(preorder, pbegin + 1 + index, pend,
										inorder, ibegin + index + 1, iend);
		return root;
	}

	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		return buildTreeRecursion(preorder, 0, preorder.size(), inorder, 0, inorder.size());
	}


	//-------------------------------------------------
	// 106. https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
	//-------------------------------------------------
	TreeNode* buildTreeRecursionii(vector<int>& postorder, int pbegin, int pend,
		vector<int>& inorder, int ibegin, int iend) {
		if (pbegin >= pend) {
			return nullptr;
		}
		TreeNode *root = new TreeNode(postorder[pend - 1]);
		int index = ibegin;
		for (; index < iend; ++index) {
			if (inorder[index] == root->val) {
				break;
			}
		}
		index -= ibegin;
		root->left = buildTreeRecursionii(postorder, pbegin, pbegin + index,
			inorder, ibegin, ibegin + index);
		root->right = buildTreeRecursionii(postorder, pbegin + index, pend - 1,
			inorder, ibegin + index + 1, iend);
		return root;
	}
	TreeNode* buildTreeii(vector<int>& inorder, vector<int>& postorder) {
		return buildTreeRecursionii(postorder, 0, postorder.size(), inorder, 0, inorder.size());
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
	// 108. https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
	//-------------------------------------------------
	TreeNode* sortedArrayToBSTRecursion(vector<int>& nums, int begin, int end) {
		if (begin >= end) {
			return nullptr;
		}
		int mid = (begin + end) / 2;
		TreeNode *root = new TreeNode(nums[mid]);
		root->left = sortedArrayToBSTRecursion(nums, begin, mid);
		root->right = sortedArrayToBSTRecursion(nums, mid + 1, end);
		return root;
	}

	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return sortedArrayToBSTRecursion(nums, 0, nums.size());
	}

	//-------------------------------------------------
	// 109. https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
	//-------------------------------------------------
	TreeNode* sortedListToBST(ListNode* head) {
		int len = GetListLength(head);
		if (len == 0) {
			return nullptr;
		}
		ListNode pre(0); 
		pre.next = head;
		ListNode *p = &pre;
		int mid = (len + 1) / 2;
		for (int i = 1; i < mid; ++i) {
			p = p->next;
		}
		ListNode *mp = p->next;
		p->next = nullptr;
		TreeNode *root = new TreeNode(mp->val);
		root->left = sortedListToBST(pre.next);
		root->right = sortedListToBST(mp->next);
		return root;
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
	// 113. https://leetcode.com/problems/path-sum-ii/
	//-------------------------------------------------
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> result;
		if (root == nullptr) {
			return result;
		}
		list<TreeNode*> treeStack;
		treeStack.push_back(root);
		sum -= root->val;
		while (!treeStack.empty()) {
			auto elem = treeStack.back();
			while (elem->left || elem->right) {
				if (elem->left) {
					treeStack.push_back(elem->left);
					elem = elem->left;
				}
				else if (elem->right) {
					treeStack.push_back(elem->right);
					elem = elem->right;
				}
				sum -= elem->val;
			}
			if (sum == 0) {
				vector<int> path;
				for (auto e : treeStack) {
					path.push_back(e->val);
				}
				result.push_back(path);
			}
			
			TreeNode* e = nullptr;
			do {
				e = treeStack.back();
				sum += e->val;
				treeStack.pop_back();
				if (!treeStack.empty()) {
					e = treeStack.back();
					if (e->left) {
						e->left = nullptr;
					}
					else if (e->right) {
						e->right = nullptr;
					}
				}
			} while (!treeStack.empty() && !e->left && !e->right);
		}
		return result;
	}


	//-------------------------------------------------
	// 114. https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
	//-------------------------------------------------
	void flatten(TreeNode* root) {
		if (root == nullptr) {
			return;
		}
		flattenTree(root);
	}
	TreeNode* flattenTree(TreeNode* root) {
		if (root->left == nullptr && root->right == nullptr) {
			return root;
		}
		TreeNode *rightEnd;
		if (root->left) {
			auto right = root->right;
			root->right = root->left;
			rightEnd = flattenTree(root->left);
			if (right) {
				rightEnd->right = right;
				rightEnd = flattenTree(right);
			}
			root->left = nullptr;
		}
		else if (root->right) {
			rightEnd = flattenTree(root->right);
		}
		return rightEnd;
	}

	//-------------------------------------------------
	// 115. https://leetcode.com/problems/distinct-subsequences/
	//-------------------------------------------------
	int numDistinct(string s, string t) {
		vector<vector<int>> value(t.size() + 1, vector<int>(s.size() + 1, 0));
		for (int i = 0; i <= s.size(); i++) {
			value[0][i] = 1;
		}
		for (int i = 1; i <= t.size(); i++) {
			for (int j = 1; j <= s.size(); j++) {
				if (s[j - 1] == t[i - 1]) {
					value[i][j] = value[i - 1][j - 1] + value[i][j - 1];
				} else {
					value[i][j] = value[i][j - 1];
				}
			}
		}
		return value[t.size()][s.size()];
	}


	//-------------------------------------------------
	// 116. https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
	//-------------------------------------------------
	void connect(TreeLinkNode *root) {
		if (root == nullptr) {
			return;
		}
		TreeLinkNode *p = root;
		while (p->left) {
			auto pre = p;
			auto follow = pre->next;
			pre->left->next = pre->right;
			while (follow) {
				pre->right->next = follow->left;
				pre = follow;
				pre->left->next = pre->right;
				follow = pre->next;
			}
			p = p->left;
		}
	}

	//-------------------------------------------------
	// 117. https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
	//-------------------------------------------------
	void connectii(TreeLinkNode *root) {
		TreeLinkNode *p = root;
		while (true) {
			while (p && !p->left && !p->right) p = p->next;
			if (!p) {
				break;
			}
			auto pre = p;
			auto follow = pre->next;
			while (follow && !follow->left && !follow->right) {
				follow = follow->next;
			}
			if (pre->left) {
				pre->left->next = pre->right ? pre->right : (follow == nullptr ? nullptr : 
					(follow->left ? follow->left : follow->right));
			}
			while (follow) {
				if (pre->right) {
					pre->right->next = follow->left ? follow->left : follow->right;
				}
				pre = follow;
				follow = pre->next;
				while (follow && !follow->left && !follow->right) {
					follow = follow->next;
				}
				if (pre->left) {
					pre->left->next = pre->right ? pre->right : (follow == nullptr ?
						nullptr : (follow->left ? follow->left : follow->right));
				}
			}
			p = p->left ? p->left : p->right;
		}
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
	// 120. https://leetcode.com/problems/triangle/
	//-------------------------------------------------
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty()) {
			return 0;
		}
		vector<int> path(triangle.size(), INT_MAX);
		path[0] = triangle[0][0];
		for (int row = 1; row < triangle.size(); row++) {
			for (int i = row; i > 0; --i) {
				path[i] = std::min(path[i - 1], path[i]) + triangle[row][i];
			}
			path[0] += triangle[row][0];
		}
		return *std::min_element(path.begin(), path.end());
	}


	//-------------------------------------------------
	// 121. https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
	//-------------------------------------------------
	int maxProfit(vector<int>& prices) {
		if (prices.size() <= 1) {
			return 0;
		}
		int high(prices[0]), low(prices[0]), maxPro(0);
		for (int i = 1; i < prices.size(); ++i) {
			if (prices[i] > high) {
				high = prices[i];
				maxPro = max(high - low, maxPro);
			} 
			else if (prices[i] < low) {
				high = low = prices[i];
			}
		}
		return maxPro;
	}


	//-------------------------------------------------
	// 122. https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
	//-------------------------------------------------
	int maxProfitii(vector<int>& prices) {
		if (prices.size() <= 1) {
			return 0;
		}
		int high(prices[0]), low(prices[0]), maxPro(0), sum(0);
		for (int i = 1; i < prices.size(); ++i) {
			if (prices[i] > high) {
				high = prices[i];
				maxPro = max(high - low, maxPro);
			}
			else if (prices[i] < high) {
				high = low = prices[i];
				sum += maxPro;
				maxPro = 0;
			}
		}

		return maxPro + sum;
	}


	//-------------------------------------------------
	// 123. https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
	//-------------------------------------------------
	int maxProfitiii(vector<int>& prices) {
		if (prices.size() <= 1) {
			return 0;
		}
		int maxTwo[2] = { 0, 0 };
		int high(prices[0]), low(prices[0]), maxPro(0);
		for (int i = 1; i < prices.size(); ++i) {
			if (prices[i] > high) {
				high = prices[i];
				maxPro = max(high - low, maxPro);
				maxTwo[0] = maxPro;
			}
			else if (prices[i] < high) {
				high = low = prices[i];
				maxPro = 0;
				maxTwo[1] = maxTwo[0];
			}
		}
		return maxPro;
	}

	//-------------------------------------------------
	// 124. https://leetcode.com/problems/binary-tree-maximum-path-sum/
	//-------------------------------------------------
	int maxPathSum(TreeNode* root) {
		int maxSum = INT_MIN;
		maxPathSumDFS(root, maxSum);
		return maxSum;
	}
	int maxPathSumDFS(TreeNode* root, int& maxSum) {
		if (root == nullptr) {
			return 0;
		}
		int left = maxPathSumDFS(root->left, maxSum);
		int right = maxPathSumDFS(root->right, maxSum);
		left = std::max(0, left);
		right = std::max(0, right);
		maxSum = std::max(maxSum, left + right + root->val);
		return std::max(left, right) + root->val;
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
	// 126. https://leetcode.com/problems/word-ladder-ii/
	//-------------------------------------------------
	vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {

	}

	//-------------------------------------------------
	// 127. https://leetcode.com/problems/word-ladder/
	//-------------------------------------------------
	int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
		wordList.insert(endWord);
		queue<string> toVisit;
		addNextWords(beginWord, wordList, toVisit);
		int dist = 2;
		while (!toVisit.empty()) {
			int num = toVisit.size();
			for (int i = 0; i < num; i++) {
				string word = toVisit.front();
				toVisit.pop();
				if (word == endWord) return dist;
				addNextWords(word, wordList, toVisit);
			}
			dist++;
		}
		return 0;
	}

	void addNextWords(string word, unordered_set<string>& wordDict, queue<string>& toVisit) {
		wordDict.erase(word);
		for (int p = 0; p < (int)word.length(); p++) {
			char letter = word[p];
			for (int k = 0; k < 26; k++) {
				word[p] = 'a' + k;
				if (wordDict.find(word) != wordDict.end()) {
					toVisit.push(word);
					wordDict.erase(word);
				}
			}
			word[p] = letter;
		}
	}

	//-------------------------------------------------
	// 128. https://leetcode.com/problems/longest-consecutive-sequence/
	//-------------------------------------------------
	int longestConsecutive(vector<int>& nums) {
		unordered_map<int, int> ranges;
		int result = 0;
		for (auto n : nums) {
			if (ranges.count(n) == 0) {
				int left = ranges.count(n - 1) > 0 ? ranges[n - 1] : 0;
				int right = ranges.count(n + 1) > 0 ? ranges[n + 1] : 0;
				int sum = left + right + 1;
				ranges[n] = sum;
				result = std::max(result, sum);

				ranges[n - left] = sum;
				ranges[n + right] = sum;
			}
		}
		return result;
	}


	//-------------------------------------------------
	// 129. https://leetcode.com/problems/sum-root-to-leaf-numbers/
	//-------------------------------------------------
	int sumNumbers(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		int sum = 0;
		list<TreeNode*> treeStack;
		treeStack.push_back(root);
		while (!treeStack.empty()) {
			auto e = treeStack.back();
			while (e->left || e->right) {
				if (e->left) {
					treeStack.push_back(e->left);
					e = e->left;
				} else {
					treeStack.push_back(e->right);
					e = e->right;
				}
			}
			string path;
			for (auto t : treeStack) {
				path += t->val + '0';
			}
			sum += stoi(path);

			do {
				e = treeStack.back();
				treeStack.pop_back();
				if (!treeStack.empty()) {
					e = treeStack.back();
					if (e->left) {
						e->left = nullptr;
					}
					else if (e->right) {
						e->right = nullptr;
					}
				}
			} while (!treeStack.empty() && !e->left && !e->right);
		}
		return sum;
	}


	//-------------------------------------------------
	// 130. https://leetcode.com/problems/surrounded-regions/
	//-------------------------------------------------
	void bfsBoundary(vector<vector<char> >& board, int w, int l) {
		int width = board.size();
		int length = board[0].size();
		queue<pair<int, int>> q;
		q.push(make_pair(w, l));
		board[w][l] = 'B';
		while (!q.empty()) {
			pair<int, int> cur = q.front();  q.pop();
			pair<int, int> adjs[4] = { 
				{ cur.first - 1, cur.second },
				{ cur.first + 1, cur.second },
				{ cur.first, cur.second - 1 },
				{ cur.first, cur.second + 1 } };
			for (int i = 0; i < 4; ++i) {
				int adjW = adjs[i].first;
				int adjL = adjs[i].second;
				if (adjW >= 0 && adjW < width && 
					adjL >= 0 && adjL < length && 
					board[adjW][adjL] == 'O') {
					q.push(make_pair(adjW, adjL));
					board[adjW][adjL] = 'B';
				}
			}
		}
	}

	void solve(vector<vector<char> > &board) {
		int width = board.size();
		if (width == 0) //Add this to prevent run-time error!
			return;
		int length = board[0].size();
		if (length == 0) // Add this to prevent run-time error!
			return;

		for (int i = 0; i < length; ++i) {
			if (board[0][i] == 'O')
				bfsBoundary(board, 0, i);

			if (board[width - 1][i] == 'O')
				bfsBoundary(board, width - 1, i);
		}

		for (int i = 0; i < width; ++i) {
			if (board[i][0] == 'O')
				bfsBoundary(board, i, 0);
			if (board[i][length - 1] == 'O')
				bfsBoundary(board, i, length - 1);
		}

		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < length; ++j) {
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				else if (board[i][j] == 'B')
					board[i][j] = 'O';
			}
		}
	}

	//-------------------------------------------------
	// 131. https://leetcode.com/problems/palindrome-partitioning/
	//-------------------------------------------------
	vector<vector<string>> partition(string s) {
		vector<vector<string>> res;
		vector<string> tmp;
		getPartition(s, 0, tmp, res);
		return res;
	}
	void getPartition(string& s, int idx, vector<string>& tmp, vector<vector<string>>& res) {
		if (idx == s.length()) {
			res.push_back(tmp);
			return;
		}
		for (int i = idx, n = s.length(); i < n; i++) {
			int l = idx, r = i;
			while (l < r && s[l] == s[r]) l++, r--;
			if (l >= r) {
				tmp.push_back(s.substr(idx, i - idx + 1));
				getPartition(s, i + 1, tmp, res);
				tmp.pop_back();
			}
		}
	}


	//-------------------------------------------------
	// 133. https://leetcode.com/problems/clone-graph/
	//-------------------------------------------------
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == nullptr) {
			return nullptr;
		}
		unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> srcDes;
		return cloneGraphDFS(node, srcDes);
	}
	UndirectedGraphNode *cloneGraphDFS(UndirectedGraphNode *node, unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> &srcDes) {
		auto it = srcDes.find(node);
		if (it == srcDes.end()) {
			UndirectedGraphNode *result = new UndirectedGraphNode(node->label);
			srcDes[node] = result;
			for (auto ne : node->neighbors) {
				result->neighbors.push_back(cloneGraphDFS(ne, srcDes));
			}
			return result;
		}
		else {
			return it->second;
		}
	}

	//-------------------------------------------------
	// 134. https://leetcode.com/problems/gas-station/
	//-------------------------------------------------
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int start(0), total(0), tank(0);
		//if car fails at 'start', record the next station
		for (int i = 0; i < gas.size(); i++) {
			tank += gas[i] - cost[i];
			if (tank < 0) {
				start = i + 1; 
				total += tank; 
				tank = 0;
			}
		}
		return (total + tank < 0) ? -1 : start;
	}

	//-------------------------------------------------
	// 135. https://leetcode.com/problems/candy/
	//-------------------------------------------------
	int candy(vector<int>& ratings) {
		int size = ratings.size();
		if (size <= 1)
			return size;
		vector<int> num(size, 1);
		for (int i = 1; i < size; i++) {
			if (ratings[i] > ratings[i - 1])
				num[i] = num[i - 1] + 1;
		}
		for (int i = size - 1; i > 0; i--) {
			if (ratings[i - 1] > ratings[i])
				num[i - 1] = max(num[i] + 1, num[i - 1]);
		}

		return std::accumulate(num.begin(), num.end(), 0);
	}


	//-------------------------------------------------
	// 136. https://leetcode.com/problems/single-number/
	//-------------------------------------------------
	int singleNumber(vector<int>& nums) {
		int result = 0;
		for (int i = 0; i < nums.size(); ++i) {
			result ^= nums[i];
		}
		return result;
	}


	//-------------------------------------------------
	// 137. https://leetcode.com/problems/single-number-ii/
	//-------------------------------------------------
	int singleNumberii(vector<int>& nums) {
		int ones = 0, twos = 0;
		for (int i = 0; i < nums.size(); i++) {
			ones = (ones ^ nums[i]) & ~twos;
			twos = (twos ^ nums[i]) & ~ones;
		}
		return ones;
	}


	//-------------------------------------------------
	// 139. https://leetcode.com/problems/word-break/
	//-------------------------------------------------
	bool wordBreak(string s, unordered_set<string> &dict) {
		if (dict.empty()) {
			return false;
		}

		vector<bool> dp(s.size() + 1, false);
		dp[0] = true;

		for (int i = 1; i <= s.size(); ++i) {
			for (int j = i - 1; j >= 0; --j) {
				if (dp[j]) {
					string word = s.substr(j, i - j);
					if (dict.find(word) != dict.end()) {
						dp[i] = true;
						break; 
					}
				}
			}
		}

		return dp[s.size()];
	}

	//-------------------------------------------------
	// 141. https://leetcode.com/problems/linked-list-cycle/
	//-------------------------------------------------
	bool hasCycle(ListNode *head) {
		ListNode *one = head;
		ListNode *two = head;
		while (two) {
			one = one->next;
			two = two->next;
			if (two == nullptr) {
				break;
			}
			two = two->next;
			if (one == two) {
				return true;
			}
		}
		return false;
	}


	//-------------------------------------------------
	// 142. https://leetcode.com/problems/linked-list-cycle-ii/
	//-------------------------------------------------
	ListNode *detectCycle(ListNode *head) {
		if (head == NULL || head->next == NULL)
			return NULL;

		ListNode* firstp = head;
		ListNode* secondp = head;
		bool isCycle = false;

		while (firstp != NULL && secondp != NULL) {
			firstp = firstp->next;
			if (secondp->next == NULL) {
				return NULL;
			}
			secondp = secondp->next->next;
			if (firstp == secondp) {
				isCycle = true;
				break;
			}
		}

		if (!isCycle) return NULL;
		firstp = head;
		while (firstp != secondp) {
			firstp = firstp->next;
			secondp = secondp->next;
		}

		return firstp;
	}


	//-------------------------------------------------
	// 143. https://leetcode.com/problems/reorder-list/
	//-------------------------------------------------
	void reorderList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return;
		}
		ListNode *p1 = head;
		ListNode *p2 = head->next;
		while (p2 && p2->next) {
			p1 = p1->next;
			p2 = p2->next->next;
		}
		auto l2 = reverseList(p1->next);
		p1->next = nullptr;
		auto l1 = head;
		while (l1 && l2) {
			auto temp = l2->next;
			l2->next = l1->next;
			l1->next = l2;
			l1 = l2->next;
			l2 = temp;
		}
	}

	//-------------------------------------------------
	// 144. https://leetcode.com/problems/binary-tree-preorder-traversal/
	//-------------------------------------------------
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		auto p = root;
		stack<TreeNode*> rightStack;
		while (p) {
			result.push_back(p->val);
			if (p->right) {
				rightStack.push(p->right);
			}
			p = p->left;

			if (p == nullptr && !rightStack.empty()) {
				p = rightStack.top();
				rightStack.pop();
			}
		}
		return result;
	}


	//-------------------------------------------------
	// 145. https://leetcode.com/problems/binary-tree-postorder-traversal/
	//-------------------------------------------------
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> result;
		if (root == nullptr) {
			return result;
		}
		TreeNode *p = root;
		stack<TreeNode*> trees;
		trees.push(p);
		while (!trees.empty()) {
			TreeNode* node = trees.top();
			result.push_back(node->val);
			trees.pop();
			if (node->left)
				trees.push(node->left);
			if (node->right)
				trees.push(node->right);
		}
		std::reverse(result.begin(), result.end());
		return result;
	}


	//-------------------------------------------------
	// 147. https://leetcode.com/problems/insertion-sort-list/
	//-------------------------------------------------
	ListNode* insertionSortList(ListNode* head) {
		if (head == nullptr) {
			return head;
		}
		ListNode preHead(0);
		preHead.next = head;
		ListNode *pre = head, *p = head->next, *rightPos;
		while (p) {
			if (p->val >= pre->val) {
				pre = p;
				p = p->next;
				continue;
			}
			rightPos = &preHead;
			while (rightPos->next && p->val > rightPos->next->val) {
				rightPos = rightPos->next;
			}
			auto temp = rightPos->next;
			rightPos->next = p;
			pre->next = p->next;
			p->next = temp;
			p = pre->next;
		}
		return preHead.next;
	}

	//-------------------------------------------------
	// 148. https://leetcode.com/problems/sort-list/
	//-------------------------------------------------
	ListNode* sortList(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode* p1 = head;
		ListNode* p2 = head->next->next;
		while (p2 != nullptr && p2->next != nullptr) {
			p1 = p1->next;
			p2 = p2->next->next;
		}
		ListNode *l2 = sortList(p1->next);
		p1->next = nullptr;
		return mergeSortedList(sortList(head), l2);
	}
	ListNode* mergeSortedList(ListNode *l1, ListNode *l2) {
		ListNode head(0);
		ListNode *p = &head;
		while (l1 != nullptr && l2 != nullptr) {
			if (l1->val < l2->val) {
				p->next = l1;
				l1 = l1->next;
			} else {
				p->next = l2;
				l2 = l2->next;
			}
			p = p->next;
		}
		if (l1 != nullptr)
			p->next = l1;
		if (l2 != nullptr)
			p->next = l2;
		return head.next;
	}

	//-------------------------------------------------
	// 150. https://leetcode.com/problems/evaluate-reverse-polish-notation/
	//-------------------------------------------------
	int evalRPN(vector<string>& tokens) {
		stack<int> nums;
		int result, t1, t2;
		for (auto t : tokens) {
			if (t == "+") {
				t1 = nums.top(); nums.pop();
				t2 = nums.top(); nums.pop();
				nums.push(t2 + t1);
			} else if (t == "-") {
				t1 = nums.top(); nums.pop();
				t2 = nums.top(); nums.pop();
				nums.push(t2 - t1);
			} else if (t == "*") {
				t1 = nums.top(); nums.pop();
				t2 = nums.top(); nums.pop();
				nums.push(t2 * t1);
			} else if (t == "/") {
				t1 = nums.top(); nums.pop();
				t2 = nums.top(); nums.pop();
				nums.push(t2 / t1);
			} else {
				nums.push(stoi(t));
			}
		}
		return nums.top();
	}

	int evalRPNii(vector<string>& tokens) {
		stack<int> nums;
		unordered_map<string, function<int(int, int)>> operators = {
			{"+", std::plus<int>() },
			{ "-", std::minus<int>() },
			{ "*", std::multiplies<int>() },
			{ "/", std::divides<int>() }
		};

		int result, t1, t2;
		for (auto t : tokens) {
			if (operators.count(t)) {
				t1 = nums.top(); nums.pop();
				t2 = nums.top(); nums.pop();
				nums.push(operators[t](t2, t1));
			} else {
				nums.push(stoi(t));
			}
		}
		return nums.top();
	}

	//-------------------------------------------------
	// 151. https://leetcode.com/problems/reverse-words-in-a-string/
	//-------------------------------------------------
	void reverseWords(string &s) {
		int src = 0, des = 0;
		while (src < s.size() && isspace(s[src])) {
			++src;
		}
		while (src < s.size()) {
			while (src < s.size() && !isspace(s[src])) {
				s[des++] = s[src++];
			}
			if (src < s.size() && isspace(s[src])) {
				s[des++] = s[src++];
			}
			while (src < s.size() && isspace(s[src])) {
				++src;
			}
		}
		--des;
		while (des >= 0 && isspace(s[des])) {
			--des;
		}
		s.resize(des + 1);
		
		std::reverse(s.begin(), s.end());
		auto itStart = s.begin();
		auto itEnd = s.begin();
		while (itStart != s.end()) {
			while (itEnd != s.end() && !isspace(*itEnd)) {
				++itEnd;
			}
			std::reverse(itStart, itEnd);
			if (itEnd == s.end()) {
				break;
			}
			itStart = ++itEnd;
		}
	}

	//-------------------------------------------------
	// 152. https://leetcode.com/problems/maximum-product-subarray/
	//-------------------------------------------------
	int maxProduct(vector<int>& nums) {
		vector<int> productMax(nums.size());
		vector<int> productMin(nums.size());
		productMax[0] = productMin[0] = nums[0];

		int len = nums.size();
		int result = nums[0];
		for (int i = 1; i < len; ++i) {
			productMax[i] = std::max(nums[i], 
				std::max(productMax[i - 1] * nums[i], productMin[i - 1] * nums[i]));
			productMin[i] = std::min(nums[i], 
				std::min(productMax[i - 1] * nums[i], productMin[i - 1] * nums[i]));
			if (result < productMax[i]) {
				result = productMax[i];
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 153. https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
	//-------------------------------------------------
	int findMin(vector<int>& nums) {
		int low = 0;
		int high = nums.size() - 1;
		while (low < high) {
			if (nums[low] < nums[high]) {
				break;
			}
			int mid = (low + high) / 2;
			if (nums[mid] >= nums[low]) {
				low = mid + 1;
			} else {
				high = mid;
			}
		}
		return nums[low];
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
	// 162. https://leetcode.com/problems/find-peak-element/
	//-------------------------------------------------
	int findPeakElement(vector<int> &num) {
		int low = 0;
		int high = num.size() - 1;

		while (low < high) {
			int mid1 = (low + high) / 2;
			int mid2 = mid1 + 1;
			if (num[mid1] < num[mid2]) {
				low = mid2;
			} else {
				high = mid1;
			}
		}
		return low;
	}


	//-------------------------------------------------
	// 164. https://leetcode.com/problems/maximum-gap/
	//-------------------------------------------------
	int maximumGap(vector<int>& nums) {

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
	// 166. https://leetcode.com/problems/fraction-to-recurring-decimal/
	//-------------------------------------------------
	string fractionToDecimal(int numerator, int denominator) {
		int64_t num = numerator;
		int64_t den = denominator;
		string result;
		if (num < 0 && den > 0 || num > 0 && den < 0) {
			result = "-";
		}
		if (num < 0) {
			num = -num;
		}
		if(den < 0) {
			den = -den;
		}
		result += to_string(num / den);
		uint64_t remainder = num % den;
		if (remainder == 0) {
			return result;
		}
		result += ".";
		unordered_map<uint64_t, int> remainderMap;
		int index = result.size();//小数位数
		while (remainder != 0) {
			if (remainderMap.count(remainder)) {
				result.insert(remainderMap[remainder], "(");
				result.push_back(')');
				break;
			}
			remainderMap[remainder] = index++;
			remainder *= 10;
			result += to_string(remainder / den);
			remainder = remainder % den;
		}

		return result;
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
	// 174. https://leetcode.com/problems/dungeon-game/
	//-------------------------------------------------


	//-------------------------------------------------
	// 179. https://leetcode.com/problems/largest-number/
	//-------------------------------------------------
	static bool compareStringNumber(const string& left, const string& right) {
		if (left.size() > right.size()) {
			return !compareStringNumber(right, left);
		}
		int i = 0, j = 0;
		do {
			if (i == left.size()) {
				i = 0;
			} else if (j == right.size()) {
				j = 0;
			}

			for (; i < left.size() && j < right.size(); ++i, ++j) {
				if (left[i] == right[j]) {
					continue;
				}
				return left[i] > right[j];
			}
		} while (i != left.size() || j != right.size());

		return false;
	}
	string largestNumber(vector<int>& nums) {
		vector<string> snums;
		for (auto n : nums) {
			snums.push_back(to_string(n));
		}
		sort(snums.begin(), snums.end(), Solution::compareStringNumber);
		string result;
		for (auto s : snums) {
			result += s;
		}
		int start = 0;
		for (; start < result.size() - 1; ++start) {
			if (result[start] != '0') {
				break;
			}
		}
		return result.substr(start);
	}

	//-------------------------------------------------
	// 187. https://leetcode.com/problems/repeated-dna-sequences/
	//-------------------------------------------------
	vector<string> findRepeatedDnaSequences(string s) {
		unordered_map<string, int> sequeences;
		for (int i = 0; i + 10 <= s.size(); ++i) {
			sequeences[s.substr(i, 10)]++;
		}
		vector<string> result;
		for (auto v : sequeences) {
			if (v.second > 1) {
				result.push_back(v.first);
			}
		}
		return result;
	}


	//-------------------------------------------------
	// 188. https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
	//-------------------------------------------------
	int maxProfit(int k, vector<int>& prices) {

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
	// 199. https://leetcode.com/problems/binary-tree-right-side-view/
	//-------------------------------------------------
	vector<int> rightSideView(TreeNode* root) {
		vector<int> result;
		if (root == nullptr) {
			return result;
		}
		queue<TreeNode*> traverseQueue;
		traverseQueue.push(root);
		traverseQueue.push(nullptr);
		int last;
		while (!traverseQueue.empty()) {
			auto elem = traverseQueue.front();
			traverseQueue.pop();
			if (elem == nullptr) {
				result.push_back(last);
				if (!traverseQueue.empty()) {
					traverseQueue.push(nullptr);
				}
				continue;
			}
			last = elem->val;
			if (elem->left) {
				traverseQueue.push(elem->left);
			}
			if (elem->right) {
				traverseQueue.push(elem->right);
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 200. https://leetcode.com/problems/number-of-islands/
	//-------------------------------------------------
	int numIslands(vector<vector<char>>& grid) {
		int result = 0;
		if (grid.empty()) {
			return result;
		}
		for (int i = 0; i < grid.size(); ++i) {
			grid[i].insert(grid[i].begin(), '0');
		}
		grid.insert(grid.begin(), vector<char>(grid[0].size(), '0'));

		for (int i = 1; i < grid.size(); ++i) {
			for (int j = 1; j < grid[i].size(); ++j) {
				if (grid[i][j] == '1') {
					if (grid[i - 1][j] == '0' && grid[i][j - 1] == '0'){
						result++;
					}
				}
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 201. https://leetcode.com/problems/bitwise-and-of-numbers-range/
	//-------------------------------------------------
	int rangeBitwiseAnd(int m, int n) {
		int result = 0;
		uint32_t bitAnd = 0x80000000;
		for (int i = 0; i < 32; ++i) {
			if ((m & bitAnd) == (n & bitAnd)) {
				result |= m & bitAnd;
			}
			else {
				break;
			}
			bitAnd >>= 1;
		}
		return result;
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
	// 207. https://leetcode.com/problems/course-schedule/
	//-------------------------------------------------
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> graph(numCourses);
		for (auto pre : prerequisites) {
			graph[pre.second].insert(pre.first);
		}

		vector<int> degrees(graph.size(), 0);
		for (auto neighbors : graph) {
			for (int neigh : neighbors) {
				degrees[neigh]++;
			}
		}

		for (int i = 0; i < numCourses; i++) {
			int j = 0;
			for (; j < numCourses; j++)
				if (!degrees[j]) break;
			if (j == numCourses) return false;
			degrees[j] = -1;
			for (int neigh : graph[j])
				degrees[neigh]--;
		}
		return true;
	}


	//-------------------------------------------------
	// 209. https://leetcode.com/problems/minimum-size-subarray-sum/
	//-------------------------------------------------
	int minSubArrayLen(int s, vector<int>& nums) {
		if (nums.empty())
			return 0;

		int i = 0, j = 0;
		int sum = 0, min = INT_MAX;

		while (j < nums.size()) {
			sum += nums[j++];

			while (sum >= s) {
				min = std::min(min, j - i);
				sum -= nums[i++];
			}
		}

		return min == INT_MAX ? 0 : min;
	}

	//-------------------------------------------------
	// 210. https://leetcode.com/problems/course-schedule-ii/
	//-------------------------------------------------
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<unordered_set<int>> graph(numCourses);
		for (auto pre : prerequisites) {
			graph[pre.second].insert(pre.first);
		}
		vector<int> toposort;
		vector<bool> onpath(numCourses, false), visited(numCourses, false);
		for (int i = 0; i < numCourses; i++) {
			if (!visited[i] && dfs(graph, i, onpath, visited, toposort))
				return{};
		}
		std::reverse(toposort.begin(), toposort.end());
		return toposort;
	}
	bool dfs(vector<unordered_set<int>>& graph, int node, vector<bool>& onpath, vector<bool>& visited, vector<int>& toposort) {
		if (visited[node]) return false;
		onpath[node] = visited[node] = true;
		for (int neigh : graph[node])
			if (onpath[neigh] || dfs(graph, neigh, onpath, visited, toposort))
				return true;
		toposort.push_back(node);
		return onpath[node] = false;
	}

	//-------------------------------------------------
	// 213. https://leetcode.com/problems/house-robber-ii/
	//-------------------------------------------------
	int robii(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}

		vector<int> bests1 = { 0, 0 }; //without first
		vector<int> bests2 = { 0, nums[0] }; // with first
		for (int i = 1; i < nums.size(); ++i) {
			int best = max(nums[i] + bests1[i - 1], bests1[i]);
			bests1.push_back(best);
		}
		for (int i = 1; i < nums.size() - 1; ++i) {
			int best = max(nums[i] + bests2[i - 1], bests2[i]);
			bests2.push_back(best);
		}
		return std::max(bests1.back(), bests2.back());
	}
	
	//-------------------------------------------------
	// 214. https://leetcode.com/problems/shortest-palindrome/
	//-------------------------------------------------
	string shortestPalindrome(string s) {
		int len = s.size();
		if (len <= 1) {
			return s;
		}
		for (int i = (len - 1) / 2; i >= 0; --i) {
			bool found = true;
			int j;
			for (j = 1; i - j >= 0; j++) {
				if (s[i - j] != s[i + j]) {
					found = false;
					break;
				}
			}
			if (found) {
				while (i + j < s.size()) {
					s.insert(s.begin(), s[i + j]);
					j++; i++;
				}
				break;
			}
		}
		return s;
	}


	//-------------------------------------------------
	// 215. https://leetcode.com/problems/kth-largest-element-in-an-array/
	//-------------------------------------------------
	void max_heapify(vector<int>& nums, int idx, int len) {
		int largest = idx;
		int l = idx * 2 + 1;
		int r = idx * 2 + 2;
		if (l < len && nums[l] > nums[largest]) largest = l;
		if (r < len && nums[r] > nums[largest]) largest = r;
		if (largest != idx) {
			swap(nums[idx], nums[largest]);
			max_heapify(nums, largest, len);
		}
	}

	int findKthLargest(vector<int>& nums, int k) {
		int heap_size = nums.size();
		for (int i = (heap_size / 2) - 1; i >= 0; i--) {
			max_heapify(nums, i, heap_size);
		}
		for (int i = 0; i < k; i++) {
			swap(nums[0], nums[heap_size - 1]);
			heap_size--;
			max_heapify(nums, 0, heap_size);
		}
		return nums[heap_size];
	}

	//-------------------------------------------------
	// 216. https://leetcode.com/problems/combination-sum-iii/
	//-------------------------------------------------
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> result;
		vector<int> curr;
		combinationSum3(n, k, 0, curr, result);
		return result;
	}

	bool combinationSum3(int n, int k, int start, vector<int>& curr, vector<vector<int>>& all) {
		const static vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		if (k == 0) {
			if (n == 0 && !curr.empty()) {
				all.push_back(curr);
				return true;
			}
			return false;
		}
		int end = 10 - k;
		for (int i = start; i < end; ++i) {
			curr.push_back(nums[i]);
			combinationSum3(n - nums[i], k - 1, i + 1, curr, all);
			curr.pop_back();
		}
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
	// 220. https://leetcode.com/problems/contains-duplicate-iii/
	//-------------------------------------------------
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		set<int> window; // set is ordered automatically 
		for (int i = 0; i < nums.size(); i++) {
			if (i > k) window.erase(nums[i - k - 1]); // keep the set contains nums i j at most k
													  // |x - nums[i]| <= t  ==> -t <= x - nums[i] <= t;
			auto pos = window.lower_bound(nums[i] - t); // x-nums[i] >= -t ==> x >= nums[i]-t 
														// x - nums[i] <= t ==> |x - nums[i]| <= t    
			if (pos != window.end() && *pos - nums[i] <= t) {
				return true;
			}
			window.insert(nums[i]);
		}
		return false;
	}


	//-------------------------------------------------
	// 221. https://leetcode.com/problems/maximal-square/
	//-------------------------------------------------
	int maximalSquare(vector<vector<char>>& matrix) {
		int m = matrix.size();
		if (m == 0) {
			return 0;
		}
		int n = matrix[0].size();
		vector<vector<int>> size(m, vector<int>(n, 0));
		int maxsize = 0;
		for (int j = 0; j < n; j++) {
			size[0][j] = matrix[0][j] - '0';
			maxsize = max(maxsize, size[0][j]);
		}
		for (int i = 1; i < m; i++) {
			size[i][0] = matrix[i][0] - '0';
			maxsize = max(maxsize, size[i][0]);
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (matrix[i][j] == '1') {
					size[i][j] = min(size[i - 1][j - 1], min(size[i - 1][j], size[i][j - 1])) + 1;
					maxsize = max(maxsize, size[i][j]);
				}
			}
		}
		return maxsize * maxsize;
	}


	//-------------------------------------------------
	// 222. https://leetcode.com/problems/count-complete-tree-nodes/
	//-------------------------------------------------
	int countNodes(TreeNode* root) {
		if (!root) {
			return 0;
		}
		int hl = 0, hr = 0;
		TreeNode *l = root, *r = root;
		while (l) { 
			hl++; l = l->left; 
		}
		while (r) { 
			hr++; r = r->right; 
		}
		if (hl == hr) {
			return pow(2, hl) - 1;
		}
		return 1 + countNodes(root->left) + countNodes(root->right);
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
	// 224. https://leetcode.com/problems/basic-calculator/
	//-------------------------------------------------
	int calculate(string s) {
		stack<int> expressions;
		int result = 0;
		int number = 0;
		int sign = 1;
		for (int i = 0; i < s.length(); i++) {
			if (isdigit(s[i])) {
				number = 10 * number + (int)(s[i] - '0');
			}
			else if (s[i] == '+') {
				result += sign * number;
				number = 0;
				sign = 1;
			}
			else if (s[i] == '-') {
				result += sign * number;
				number = 0;
				sign = -1;
			}
			else if (s[i] == '(') {
				expressions.push(result);
				expressions.push(sign);
				sign = 1;
				result = 0;
			}
			else if (s[i] == ')') {
				result += sign * number;
				number = 0;
				result *= expressions.top();    //stack.pop() is the sign before the parenthesis
				expressions.pop();
				result += expressions.top();   //stack.pop() now is the result calculated before the parenthesis
				expressions.pop();
			}
		}
		if (number != 0) 
			result += sign * number;
		return result;
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

	//-------------------------------------------------
	// 227. https://leetcode.com/problems/basic-calculator-ii/
	//-------------------------------------------------
	int calculateii(string s) {
		int n = 0;
		vector<int> nums;
		vector<function<int(int, int)>> opers;
		for (auto c : s) {
			if (isdigit(c)) {
				n *= 10; n += c - '0';
			}
			else if (isspace(c)) {
				continue;
			}
			else {
				nums.push_back(n);
				n = 0;

				switch (c) {
				case '+':
					opers.push_back(std::plus<int>());
					break;
				case '-':
					opers.push_back(std::minus<int>());
					break;
				case '*':
					opers.push_back(std::multiplies<int>());
					break;
				case '/':
					opers.push_back(std::divides<int>());
					break;
				}
			}
		}
		nums.push_back(n);
		return calculateii(nums, opers);
	}
	int calculateii(vector<int> &nums, vector<function<int(int, int)>> &opers) {
		int result = 0;
		if (opers.size() == 0) {
			return nums[0];
		}
		if (opers.size() == 1) {
			return opers[0](nums[0], nums[1]);
		}
		for (int i = 0; i < opers.size(); ++i) {
			if (opers[i](3, 1) == 3) { // * or /
				nums[i] = opers[i](nums[i], nums[i + 1]);
				opers.erase(opers.begin() + i);
				nums.erase(nums.begin() + i + 1);
				--i;
			}
		}
		result = nums[0];
		for (int i = 0; i < opers.size(); ++i) {
			result = opers[i](result, nums[i + 1]);
		}
		return result;
	}


	//-------------------------------------------------
	// 228. https://leetcode.com/problems/summary-ranges/
	//-------------------------------------------------
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> result;
		if (nums.empty()) {
			return result;
		}
		int start(0), end(0);
		for (int i = 1; i < nums.size(); ++i) {
			if (nums[i] != nums[i - 1] + 1) {
				end = i - 1;
				if (start == end) {
					result.push_back( to_string(nums[start]) );
				} else {
					string str = to_string(nums[start]);
					str += "->";
					str += to_string(nums[end]);
					result.push_back(str);
				}
				start = end = i;
			}
		}
		end = nums.size() - 1;
		if (start == end) {
			result.push_back(to_string(nums[start]));
		} else {
			string str = to_string(nums[start]);
			str += "->";
			str += to_string(nums[end]);
			result.push_back(str);
		}
		return result;
	}

	//-------------------------------------------------
	// 229. https://leetcode.com/problems/majority-element-ii/
	//-------------------------------------------------
	vector<int> majorityElementii(vector<int>& nums) {
		int y = 0, z = 1, cy = 0, cz = 0;
		for (auto x : nums) {
			if (x == y) {
				cy++;
			} else if (x == z) {
				cz++;
			} else if (!cy) {
				y = x, cy = 1;
			} else if (!cz) {
				z = x, cz = 1;
			} else {
				cy--, cz--;
			}
		}
		cy = cz = 0;
		for (auto x : nums) {
			if (x == y) cy++;
			else if (x == z) cz++;
		}

		vector<int> r;
		if (cy > nums.size() / 3) {
			r.push_back(y);
		}
		if (cz > nums.size() / 3) {
			r.push_back(z);
		}
		return r;
	}

	//-------------------------------------------------
	// 230. https://leetcode.com/problems/power-of-two/
	//-------------------------------------------------
	int kthSmallest(TreeNode* root, int k) {
		int count(0);
		return kthSmallestRecursion(root, k, count);
	}

	int kthSmallestRecursion(TreeNode* root, int k, int &count) {
		int val = 0;
		count = 0;
		if (root->left) {
			val = kthSmallestRecursion(root->left, k, count);
		}
		if (k <= count) {
			count = count + 1;
			return val;
		}
		else if (k == count + 1) {
			count = count + 1;
			return root->val;
		}
		else if (root->right) {
			int right;
			val = kthSmallestRecursion(root->right, k - count - 1, right);
			count += 1 + right;
			return val;
		}
		else {
			count += 1;
			return 0;
		}
	}

	//-------------------------------------------------
	// 231. https://leetcode.com/problems/power-of-two/
	//-------------------------------------------------
	bool isPowerOfTwo(int n) {
		if (n <= 0) {
			return false;
		}
		while (n != 1) {
			if (n % 2 != 0) {
				return false;
			}
			n /= 2;
		}
		return true;
	}

	//-------------------------------------------------
	// 233. https://leetcode.com/problems/number-of-digit-one/
	//-------------------------------------------------
	int countDigitOne(int n) {
		int ones = 0;
		for (int64_t i = 1; i <= n; i *= 10) {
			int bit = n / i;
			int left = n % i;
			ones += (bit + 8) / 10 * i;
			if (bit % 10 == 1) {
				ones += left + 1;
			}
		}
		return ones;
	}

	//-------------------------------------------------
	// 234. https://leetcode.com/problems/palindrome-linked-list/
	//-------------------------------------------------
	bool isPalindrome(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return true;
		}
		ListNode *p1 = head;
		ListNode *p2 = head->next;
		while (p2 && p2->next) {
			p1 = p1->next;
			p2 = p2->next->next;
		}
		auto l2 = reverseList(p1->next);
		p1->next = nullptr;

		auto l1 = head;
		while (l1 && l2) {
			if (l1->val != l2->val) {
				return false;
			}
			l1 = l1->next;
			l2 = l2->next;
		}
		return true;
	}


	//-------------------------------------------------
	// 235. https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
	//-------------------------------------------------
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root || root == p || root == q) {
			return root;
		}
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);
		if (left == nullptr) {
			return right;
		}
		else if (right == nullptr) {
			return left;
		}
		else {
			return root;
		}
	}

	//-------------------------------------------------
	// 236. https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
	//-------------------------------------------------
	TreeNode* lowestCommonAncestorii(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root || root == p || root == q) {
			return root;
		}
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);
		if (left == nullptr) {
			return right;
		}
		else if (right == nullptr) {
			return left;
		}
		else {
			return root;
		}
	}

	//-------------------------------------------------
	// 237. https://leetcode.com/problems/delete-node-in-a-linked-list/
	//-------------------------------------------------
	void deleteNode(ListNode* node) {
		auto p = node->next;
		node->val = p->val;
		node->next = p->next;
	}

	//-------------------------------------------------
	// 238. https://leetcode.com/problems/product-of-array-except-self/
	//-------------------------------------------------
	vector<int> productExceptSelf(vector<int>& nums) {
		int zeros = 0;
		int64_t products = 1;
		vector<int> result(nums.size(), 0);
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] == 0) {
				++zeros;
				result[i] = 1;
			}
			else {
				products *= nums[i];
			}
		}
		for (int i = 0; i < nums.size(); ++i) {
			if (result[i] == 1) {
				if (zeros > 1) {
					result[i] = 0;
				}
				else {
					result[i] = products;
				}
			}
			else {
				if (zeros > 0) {
					result[i] = 0;
				}
				else {
					result[i] = products / nums[i];
				}
			}
		}
		return result;
	}


	//-------------------------------------------------
	// 239. https://leetcode.com/problems/sliding-window-maximum/
	//-------------------------------------------------
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		deque<int> dq;
		vector<int> result;
		for (int i = 0; i < nums.size(); i++) {
			if (!dq.empty() && dq.front() == i - k) {
				dq.pop_front();
			}
			while (!dq.empty() && nums[dq.back()] < nums[i]) {
				dq.pop_back();
			}
			dq.push_back(i);
			if (i >= k - 1) {
				result.push_back(nums[dq.front()]);
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 240. https://leetcode.com/problems/search-a-2d-matrix-ii/
	//-------------------------------------------------
	bool searchMatrixii(vector<vector<int>>& matrix, int target) {
		for (auto &row : matrix) {
			int low = 0, high = row.size() - 1;
			while (low <= high) {
				int mid = (low + high) / 2;
				if (row[mid] == target) {
					return true;
				} else if (row[mid] < target) {
					low = mid + 1;
				} else {
					high = mid - 1;
				}
			}
		}
		return false;
	}

	//-------------------------------------------------
	// 241. https://leetcode.com/problems/different-ways-to-add-parentheses/
	//-------------------------------------------------
	vector<int> diffWaysToCompute(vector<int> nums, vector<function<int(int,int)>> opers) {
		vector<int> result;
		if (opers.size() == 0) {
			result.push_back(nums[0]);
			return result;
		}
		if (opers.size() == 1) {
			result.push_back(opers[0](nums[0], nums[1]));
			return result;
		}
		for (int i = 0; i < opers.size(); ++i) {
			vector<int> num1(nums.begin(), nums.begin() + i + 1);
			vector<int> num2(nums.begin() + i + 1, nums.end());
			vector<function<int(int, int)>> opers1(opers.begin(), opers.begin() + i);
			vector<function<int(int, int)>> opers2(opers.begin() + i + 1, opers.end());
			auto left = diffWaysToCompute(num1, opers1);
			auto right = diffWaysToCompute(num2, opers2);
			for (auto l : left) {
				for (auto r : right) {
					result.push_back(opers[i](l, r));
				}
			}
		}
		return result;
	}

	vector<int> diffWaysToCompute(string input) {
		int n = 0;
		vector<int> nums;
		vector<function<int(int, int)>> opers;
		for (auto c : input) {
			if (isdigit(c)) {
				n *= 10; n += c - '0';
			}
			else {
				nums.push_back(n);
				n = 0;

				switch (c) {
				case '+':
					opers.push_back(std::plus<int>());
					break;
				case '-':
					opers.push_back(std::minus<int>());
					break;
				case '*':
					opers.push_back(std::multiplies<int>());
					break;
				case '/':
					opers.push_back(std::divides<int>());
					break;
				}
			}
		}
		nums.push_back(n);
		return diffWaysToCompute(nums, opers);
	}


	//-------------------------------------------------
	// 242. https://leetcode.com/problems/valid-anagram/
	//-------------------------------------------------
	bool isAnagram(string s, string t) {
		unordered_map<char, int> smap, tmap;
		for (auto v : s) {
			smap[v]++;
		}
		for (auto v : t) {
			tmap[v]++;
		}
		return smap == tmap;
	}


	//-------------------------------------------------
	// 257. https://leetcode.com/problems/binary-tree-paths/
	//-------------------------------------------------
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> result;
		if (root == nullptr) {
			return result;
		}
		vector<string> curr;
		binaryTreePaths(root, curr, result);
	}

	void binaryTreePaths(TreeNode* root, vector<string> &curr, vector<string> &vs) {
		curr.push_back(to_string(root->val));
		if (root->left == nullptr && root->right == nullptr) {
			string temp;
			for (int i = 0; i < curr.size(); ++i) {
				if (i != 0) {
					temp += "->";
				}
				temp += curr[i];
			}
			vs.push_back(temp);
		}
		if (root->left) {
			binaryTreePaths(root->left, curr, vs);
		}
		if (root->right) {
			binaryTreePaths(root->right, curr, vs);
		}
		curr.pop_back();
	}

	//-------------------------------------------------
	// 258. https://leetcode.com/problems/add-digits/
	//-------------------------------------------------
	int addDigits(int num) {
		if (num < 10) {
			return num;
		} else {
			return num % 9 == 0 ? 9 : num % 9;
		}
	}

	//-------------------------------------------------
	// 260. https://leetcode.com/problems/single-number-iii/
	//-------------------------------------------------
	vector<int> singleNumberiii(vector<int>& nums) {
		// Pass 1 : 
		// Get the XOR of the two numbers we need to find
		int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
		// Get its last set bit
		diff &= -diff;

		// Pass 2 :
		vector<int> rets = { 0, 0 }; // this vector stores the two numbers we will return
		for (int num : nums) {
			if ((num & diff) == 0) { // the bit is not set
				rets[0] ^= num;
			} else {                 // the bit is set
				rets[1] ^= num;
			}
		}
		return rets;
	}

	//-------------------------------------------------
	// 263. https://leetcode.com/problems/ugly-number/
	//-------------------------------------------------
	bool isUgly(int num) {
		if (num == 0) {
			return false;
		}
		vector<int> factors = { 2, 3, 4, 5, 6, 8, 9 };
		while (num != 1) {
			bool hasFactor = false;
			for (auto v : factors) {
				if (num % v == 0) {
					num /= v;
					hasFactor = true;
				}
			}
			if (num != 1 && !hasFactor) {
				return false;
			}
		}
		return true;
	}

	//-------------------------------------------------
	// 264. https://leetcode.com/problems/ugly-number-ii/
	//-------------------------------------------------
	int nthUglyNumber(int n) {
		int t2 = 0, t3 = 0, t5 = 0; //pointers for 2, 3, 5
		vector<int> k(n, 1);
		for (int i = 1; i < n; i++)	{
			k[i] = min(k[t2] * 2, min(k[t3] * 3, k[t5] * 5));
			if (k[i] == k[t2] * 2) t2++;
			if (k[i] == k[t3] * 3) t3++;
			if (k[i] == k[t5] * 5) t5++;
		}
		return k[n - 1];
	}


	//-------------------------------------------------
	// 268. https://leetcode.com/problems/missing-number/
	//-------------------------------------------------
	int missingNumber(vector<int>& nums) {
		int sum = 0;
		for (auto v : nums) {
			sum += v;
		}

		int guess = nums.size() * (nums.size() + 1) / 2;
		return guess - sum;
	}


	//-------------------------------------------------
	// 273. https://leetcode.com/problems/integer-to-english-words/
	//-------------------------------------------------
	string numberToWords(int n) {
		if (n == 0) {
			return "Zero";
		} else {
			return int_string(n).substr(1);
		}
	}
	string int_string(int n) {
		const char * const below_20[] = { "One", "Two", "Three", "Four","Five","Six","Seven","Eight","Nine","Ten", 
			"Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
		const char * const below_100[] = { "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
		if (n >= 1000000000) {
			return int_string(n / 1000000000) + " Billion" + int_string(n - 1000000000 * (n / 1000000000));
		} else if (n >= 1000000) {
			return int_string(n / 1000000) + " Million" + int_string(n - 1000000 * (n / 1000000));
		} else if (n >= 1000) {
			return int_string(n / 1000) + " Thousand" + int_string(n - 1000 * (n / 1000));
		} else if (n >= 100) {
			return int_string(n / 100) + " Hundred" + int_string(n - 100 * (n / 100));
		} else if (n >= 20) {
			return string(" ") + below_100[n / 10 - 2] + int_string(n - 10 * (n / 10));
		} else if (n >= 1) {
			return string(" ") + below_20[n - 1];
		} else {
			return "";
		}
	}


	//-------------------------------------------------
	// 274. https://leetcode.com/problems/h-index/
	//-------------------------------------------------
	int hIndex(vector<int>& citations) {
		int hindex = 0;
		std::sort(citations.begin(), citations.end(), std::greater<int>());
		for (int i = 0; i < citations.size(); ++i) {
			int h = min(i + 1, citations[i]);
			if (h > hindex) {
				hindex = h;
			} else {
				break;
			}
		}
		return hindex;
	}


	//-------------------------------------------------
	// 275. https://leetcode.com/problems/h-index-ii/
	//-------------------------------------------------
	int hIndexii(vector<int>& citations) {
		if (citations.empty()) {
			return 0;
		}
		int hindex = 0;
		int len = citations.size();
		int low = 0, high = len - 1;
		while (low < high) {
			int mid1 = (low + high) / 2;
			int h1 = std::min(len - mid1, citations[mid1]);
			int mid2 = mid1;
			int h2;
			do {
				++mid2;
				h2 = std::min(len - mid2, citations[mid2]);
			} while (h1 == h2);
			if (h1 < h2) {
				low = mid2;
			} else {
				high = mid1;
			}
		}
		return std::min(len - low, citations[low]);
	}

	//-------------------------------------------------
	// 278. https://leetcode.com/problems/add-digits/
	//-------------------------------------------------
	int firstBadVersion(int n) {
		int64_t low = 1, high = n;
		while (low < high) {
			int64_t mid = (low + high) / 2;
			if (isBadVersion(mid)) {
				high = mid;
			}
			else {
				low = mid + 1;
			}
		}
		return low;
	}
	//for test, 2126753390 versions, 1702766719 is the first bad version.
	bool isBadVersion(int version) {
		if (version >= 1702766719) {
			return true;
		}
		return false;
	}

	//-------------------------------------------------
	// 279. https://leetcode.com/problems/perfect-squares/
	//-------------------------------------------------
	int numSquares(int n) {
		if (n <= 0)	{
			return 0;
		}

		// cntPerfectSquares[i] = the least number of perfect square numbers 
		// which sum to i. Since cntPerfectSquares is a static vector, if 
		// cntPerfectSquares.size() > n, we have already calculated the result 
		// during previous function calls and we can just return the result now.
		static vector<int> cntPerfectSquares({ 0 });

		// While cntPerfectSquares.size() <= n, we need to incrementally 
		// calculate the next result until we get the result for n.
		while (cntPerfectSquares.size() <= n) {
			int m = cntPerfectSquares.size();
			int cntSquares = INT_MAX;
			for (int i = 1; i*i <= m; i++) {
				cntSquares = min(cntSquares, cntPerfectSquares[m - i*i] + 1);
			}
			cntPerfectSquares.push_back(cntSquares);
		}

		return cntPerfectSquares[n];
	}


	//-------------------------------------------------
	// 283. https://leetcode.com/problems/move-zeroes/
	//-------------------------------------------------
	void moveZeroes(vector<int>& nums) {
		int j = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] == 0) {
				continue;
			}
			nums[j++] = nums[i];
		}
		while (j < nums.size()) {
			nums[j++] = 0;
		}
	}

	//-------------------------------------------------
	// 287. https://leetcode.com/problems/find-the-duplicate-number/
	//-------------------------------------------------
	int findDuplicate(vector<int>& nums) {
		int low = 1, high = nums.size() - 1;
		while (low < high) {
			int mid = (high + low) / 2;
			int count = 0;
			for (auto n : nums) {
				if (n <= mid) {
					count++;
				}
			}
			if (count <= mid) {
				low = mid + 1;
			} else {
				high = mid;
			}
		}
		return low;
	}



	//-------------------------------------------------
	// 289. https://leetcode.com/problems/game-of-life/
	//-------------------------------------------------
	void gameOfLife(vector<vector<int>>& board) {
		int m = board.size(), n = m ? board[0].size() : 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int count = 0;
				for (int x = max(i - 1, 0); x < min(i + 2, m); ++x) {
					for (int y = max(j - 1, 0); y < min(j + 2, n); ++y) {
						count += board[x][y] & 1;
					}
				}
				if (count == 3 || count - board[i][j] == 3) {
					board[i][j] |= 2;
				}
			}
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				board[i][j] >>= 1;
			}
		}
	}


	//-------------------------------------------------
	// 292. https://leetcode.com/problems/word-pattern/
	//-------------------------------------------------
	bool wordPattern(string pattern, string str) {
		unordered_map<char, int> pmap;
		unordered_map<string, int> strMap;
		for (int i = 0; i < pattern.size(); ++i) {
			if (pmap.count(pattern[i])) {
				continue;
			}
			pmap[pattern[i]] = i;
		}

		size_t p(0), start(0);
		string sub;
		int index = 0;
		while (start != -1) {
			p = str.find(' ', start);
			if (p != string::npos) {
				sub = str.substr(start, p - start);
				start = p + 1;
			} else {
				sub = str.substr(start);
				start = -1;
			}

			if (strMap.count(sub)) {
				if (strMap[sub] != pmap[pattern[index]]) {
					return false;
				}
			} else {
				if (pmap[pattern[index]] != index) {
					return false;
				}
				strMap[sub] = index;
			}
			index++;
			if (start != -1 && index >= pattern.size()) {
				return false;
			}
		}
		return index == pattern.size();
	}

	//-------------------------------------------------
	// 292. https://leetcode.com/problems/nim-game/
	//-------------------------------------------------
	bool canWinNim(int n) {
		if (n <= 3 || n % 4 != 0) {
			return true;
		} else {
			return false;
		}
	}


	//-------------------------------------------------
	// 299. https://leetcode.com/problems/bulls-and-cows/
	//-------------------------------------------------
	string getHint(string secret, string guess) {
		int  bull = 0, cows = 0;
		int secretDic[256] = {0};
		for (int i = 0; i < secret.size(); ++i) {
			if (secret[i] == guess[i]) {
				++bull;
				guess[i] = 0;
			}
			else {
				secretDic[secret[i]] += 1;
			}
		}
		for (int i = 0; i < guess.size(); ++i) {
			if (secretDic[guess[i]] > 0) {
				++cows;
				secretDic[guess[i]] -= 1;
			}
		}
		return to_string(bull) + "A" + to_string(cows) + "B";
	}

	//-------------------------------------------------
	// 300. https://leetcode.com/problems/longest-increasing-subsequence/
	//-------------------------------------------------
	int lengthOfLIS(vector<int>& nums) {
		vector<int> res;
		for (int i = 0; i < nums.size(); i++) {
			auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
			if (it == res.end()) {
				res.push_back(nums[i]);
			}
			else {
				*it = nums[i];
			}
		}
		return res.size();
	}
	//-------------------------------------------------
	// 306. https://leetcode.com/problems/additive-number/
	//-------------------------------------------------
	bool isAdditiveNumber(string num) {
		for (int i = 1; i <= num.size() / 2; i++) {
			for (int j = 1; j <= (num.size() - i) / 2; j++) {
				if (check(num.substr(0, i), num.substr(i, j), num.substr(i + j))) {
					return true;
				}
			}
		}
		return false;
	}
	bool check(string num1, string num2, string num) {
		if (num1.size() > 1 && num1[0] == '0'
			|| num2.size() > 1 && num2[0] == '0') {
			return false;
		}
		string sum = add(num1, num2);
		if (num == sum) {
			return true;
		}
		if (num.size() <= sum.size() ||
			sum.compare(num.substr(0, sum.size())) != 0) {
			return false;
		}
		else {
			return check(num2, sum, num.substr(sum.size()));
		}
	}
	string add(string n, string m) {
		string res;
		int i = n.size() - 1, j = m.size() - 1, carry = 0;
		while (i >= 0 || j >= 0) {
			int sum = carry + (i >= 0 ? (n[i--] - '0') : 0) + (j >= 0 ? (m[j--] - '0') : 0);
			res.push_back(sum % 10 + '0');
			carry = sum / 10;
		}
		if (carry) {
			res.push_back(carry + '0');
		}
		std::reverse(res.begin(), res.end());
		return res;
	}


	//-------------------------------------------------
	// 309. https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
	//-------------------------------------------------
	int maxProfitiv(vector<int>& prices) {
		if (prices.size() <= 1) {
			return 0;
		}

		vector<int> profit(prices.size(), 0);
		int low = 0, high = 0;
		int maxPro(0), sum(0);
		for (int i = 1; i < prices.size(); ++i) {
			if (prices[i] > prices[high]) {
				high = i;
				profit[i] = prices[high] - prices[low];
				//maxPro = max(high - low, maxPro);
			}
			else if (prices[i] < high) {
				high = low = prices[i];
				sum += maxPro;
				maxPro = 0;
			}
		}

		return maxPro + sum;
	}

	//-------------------------------------------------
	// 310. https://leetcode.com/problems/minimum-height-trees/
	//-------------------------------------------------
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		if (n == 1) {
			return { 0 };
		}
		vector<list<int>> graph(n);
		for (auto e : edges) {
			graph[e.first].push_back(e.second);
			graph[e.second].push_back(e.first);
		}
		vector<int> result;
		for (int i = 0; i < graph.size(); i++) {
			if (graph[i].size() == 1) {
				result.push_back(i);
			}
		}
		while (n > 2) {
			n -= result.size();
			vector<int> newResult;
			for (auto i : result) {
				auto next = graph[i].front();
				graph[next].remove(i);
				if (graph[next].size() == 1) {
					newResult.push_back(next);
				}
			}
			result = newResult;
		}

		return result;
	}

	//-------------------------------------------------
	// 313. https://leetcode.com/problems/super-ugly-number/
	//-------------------------------------------------
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		vector<int> ret(n, INT_MAX);
		ret[0] = 1;

		vector<int> indexes(primes.size(), 0);
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < primes.size(); j++) {
				ret[i] = std::min(ret[i], primes[j] * ret[indexes[j]]);
			}
			for (int j = 0; j < indexes.size(); j++) {
				if (ret[i] == primes[j] * ret[indexes[j]]) {
					indexes[j]++;
				}
			}
		}

		return ret[n - 1];
	}

	//-------------------------------------------------
	// 315. https://leetcode.com/problems/remove-duplicate-letters/
	//-------------------------------------------------
	string removeDuplicateLetters(string s) {
		if (s.size() <= 1) {
			return s;
		}
		string result;
		unordered_map<char, int> letterMap;
		unordered_map<char, int>::iterator it;
		for (int i = 0; i < s.size(); ++i) {
			if ((it = letterMap.find(s[i])) == letterMap.end()) {
				result.push_back(s[i]);
				letterMap[s[i]] = result.size() - 1;
			}
			else {
				if (it->second == result.size() - 1 || s[it->second] < s[it->second + 1]) {
					continue;
				}
				result.erase(it->second, 1);
				result.push_back(it->first);
				it->second = result.size() - 1;
			}
		}
		return result;
	}


	//-------------------------------------------------
	// 318. https://leetcode.com/problems/maximum-product-of-word-lengths/
	//-------------------------------------------------
	int maxProduct(vector<string>& words) {
		map<int, size_t> masks;
		for (auto w : words) {
			int mask = 0;
			for (auto c : w) {
				mask |= 1 << (c - 'a');
			}
			masks[mask] = std::max(w.size(), masks[mask]);
		}
		size_t result = 0;
		for (auto i : masks) {
			for (auto j : masks) {
				if (!(i.first & j.first)) {
					result = std::max(result, i.second * j.second);
				}
			}
		}
		return result;
	}

    //-------------------------------------------------
	// 319. https://leetcode.com/problems/bulb-switcher/
	//-------------------------------------------------
    int bulbSwitch(int n) {
        return sqrt(n);
    }
  
	//-------------------------------------------------
	// 322. https://leetcode.com/problems/coin-change/
	//-------------------------------------------------
	int coinChange(vector<int>& coins, int amount) {
		int Max = INT_MAX;
		vector<int> dp(amount + 1, Max);
		dp[0] = 0;
		for (int i = 1; i <= amount; i++) {
			for (int j = 0; j < coins.size(); j++) {
				if (coins[j] <= i) {
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
				}
			}
		}
		return dp[amount] > amount ? -1 : dp[amount];
	}


	//-------------------------------------------------
	// 324. https://leetcode.com/problems/wiggle-sort-ii/
	//-------------------------------------------------
	void wiggleSort(vector<int>& nums) {
		int n = nums.size();

		// Find a median.
		auto midptr = nums.begin() + n / 2;
		nth_element(nums.begin(), midptr, nums.end());
		int mid = *midptr;

		// Index-rewiring.
#define A(i) nums[( 1 + 2 * (i)) % (n | 1)]

		// 3-way-partition-to-wiggly in O(n) time with O(1) space.
		int i = 0, j = 0, k = n - 1;
		while (j <= k) {
			if (A(j) > mid)
				swap(A(i++), A(j++));
			else if (A(j) < mid)
				swap(A(j), A(k--));
			else
				j++;
		}
	}
	
	
	//-------------------------------------------------
	// 326. https://leetcode.com/problems/power-of-three/
	//-------------------------------------------------
	bool isPowerOfThree(int n) {
		if (n == 0) {
			return false;
		}
		double log3f = log(double(n)) / log(3.0);
		int log3i = (int)log3f;
		if (log3f - log3i > 0.5) {
			log3i += 1;
		}
		return (int)pow(3.0, log3i) == n;
	}


	//-------------------------------------------------
	// 328. https://leetcode.com/problems/odd-even-linked-list/
	//-------------------------------------------------
	ListNode* oddEvenList(ListNode* head) {
		if (!head) return head;
		ListNode *odd = head, *evenhead = head->next, *even = evenhead;
		while (even && even->next) {
			odd->next = odd->next->next;
			even->next = even->next->next;
			odd = odd->next;
			even = even->next;
		}
		odd->next = evenhead;
		return head;
	}


	//-------------------------------------------------
	// 330. https://leetcode.com/problems/patching-array/
	//-------------------------------------------------
	int minPatches(vector<int>& nums, int n) {
		uint32_t miss = 1;
		int added = 0;
		int i = 0;
		while (miss <= n) {
			if (i < nums.size() && miss >= nums[i]) {
				miss += nums[i++];
			}
			else {
				miss += miss;
				added++;
			}
		}
		return added;
	}


	//-------------------------------------------------
	// 331. https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
	//-------------------------------------------------
	bool isValidSerialization(string preorder) {
		int du = 1;
		int start = 0;
		auto p = preorder.find(',', start);
		while (p != string::npos) {
			string str = preorder.substr(start, p - start);
			if (--du < 0)
				return false;
			if (str != "#") {
				du += 2;
			}
			start = p + 1;
			p = preorder.find(',', start);
		}
		return du == 1 && preorder.substr(start) == "#";
	}


	//-------------------------------------------------
	// 332. https://leetcode.com/problems/reconstruct-itinerary/
	//-------------------------------------------------
	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		map<string, multiset<string>> graph;
		for (auto t : tickets) {
			graph[t.first].insert(t.second);
		}
		vector<string> route;
		findItineraryDFS(graph, "JFK", route);
		std::reverse(route.begin(), route.end());
		return route;
	}
	void findItineraryDFS(map<string, multiset<string>> &graph, string start, vector<string> &route) {
		while (!graph[start].empty()) {
			auto e = graph[start].begin();
			auto str = *e;
			graph[start].erase(e);
			findItineraryDFS(graph, str, route);
		}
		route.push_back(start);
	}

	//-------------------------------------------------
	// 334. https://leetcode.com/problems/increasing-triplet-subsequence/
	//-------------------------------------------------
	bool increasingTriplet(vector<int>& nums) {
		int c1 = INT_MAX, c2 = INT_MAX;
		for (int x : nums) {
			if (x <= c1) {
				c1 = x;           // c1 is min seen so far (it's a candidate for 1st element)
			} else if (x <= c2) { // here when x > c1, i.e. x might be either c2 or c3
				c2 = x;           // x is better than the current c2, store it
			} else {              // here when we have/had c1 < c2 already and x > c2
				return true;      // the increasing subsequence of 3 elements exists
			}
		}
		return false;
	}

	//-------------------------------------------------
	// 335. https://leetcode.com/problems/self-crossing/
	//-------------------------------------------------
	bool isSelfCrossing(vector<int>& x) {
		int len = x.size();
		if (len <= 3) {
			return false;
		}

		// Categorize the self-crossing scenarios, there are 3 of them: 
		// 1. Fourth line crosses first line and works for fifth line crosses second line and so on...
		// 2. Fifth line meets first line and works for the lines after
		// 3. Sixth line crosses first line and works for the lines after
		for (int i = 3; i < len; i++) {
			if (x[i] >= x[i - 2] && x[i - 1] <= x[i - 3]) {
				return true; //Fourth line crosses first line and onward
			}
			if (i >= 4)	{
				if (x[i - 1] == x[i - 3] && x[i] + x[i - 4] >= x[i - 2]) {
					return true; // Fifth line meets first line and onward
				}
			}
			if (i >= 5) {
				if (x[i - 2] - x[i - 4] >= 0 && x[i] >= x[i - 2] - x[i - 4] &&
					x[i - 1] >= x[i - 3] - x[i - 5] && x[i - 1] <= x[i - 3]) {
					return true;  // Sixth line crosses first line and onward
				}
			}
		}
		return false;
	}


	//-------------------------------------------------
	// 337. https://leetcode.com/problems/house-robber-iii/
	//-------------------------------------------------
	void robSub(TreeNode* root, vector<int> &out) {
		if (root == nullptr) {
			return;
		}
		int val = 0;
		vector<int> left(2, 0), right(2, 0);
		robSub(root->left, left);
		robSub(root->right, right);
		
		out[0] = std::max(left[0], left[1]) + std::max(right[0], right[1]);
		out[1] = root->val + left[0] + right[0];
	}
	int rob(TreeNode *root) {
		vector<int> out(2, 0);
		robSub(root, out);
		return std::max(out[0], out[1]);
	}

    //-------------------------------------------------
	// 338. https://leetcode.com/problems/counting-bits/
	//-------------------------------------------------
    vector<int> countBits(int num) {
        if (num == 0) {
            return  { 0 };
        }
        vector<int> result = { 0, 1 };
        int bound = 4;
        for(int i = 2, j = 0; i <= num; i++) {
            if (i == bound) {
                j = 0;
                bound <<= 1;
            }
            result.push_back(result[j] + 1);
            j++;
        }
        
        return result;
    }

	//-------------------------------------------------
	// 342. https://leetcode.com/problems/power-of-four/
	//-------------------------------------------------
	bool isPowerOfFour(int num) {
		return num > 0 && (num & (num - 1)) == 0 && (num - 1) % 3 == 0;
	}


	//-------------------------------------------------
	// 343. https://leetcode.com/problems/integer-break/
	//-------------------------------------------------
	int integerBreak(int n) {
		if (n == 2) {
			return 1;
		}
		if (n == 3) {
			return 2;
		}
		int result = 1;
		while (n > 4) {
			result *= 3;
			n -= 3;
		}
		result *= n;
		return result;
	}

	//-------------------------------------------------
	// 344. https://leetcode.com/problems/reverse-string/
	//-------------------------------------------------
	string reverseString(string s) {
		int len = s.size();
		for (int i = 0, j = len - 1; i < j; i++, j--) {
			swap(s[i], s[j]);
		}
		return s;
	}

	//-------------------------------------------------
	// 345. https://leetcode.com/problems/reverse-vowels-of-a-string/
	//-------------------------------------------------
	string reverseVowels(string s) {
		int i = 0;
		int j = s.size() - 1;
		set<char> dict = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
		while (i < j) {
			while (i < j && dict.count(s[i]) == 0) i++;
			while (i < j && dict.count(s[j]) == 0) j--;
			if (i < j) {
				swap(s[i++], s[j--]);
			}
		}
		return s;
	}

	//-------------------------------------------------
	// 347. https://leetcode.com/problems/top-k-frequent-elements/
	//-------------------------------------------------
	vector<int> topKFrequent(vector<int> nums, int k) {
		unordered_map<int, int> frequent;
		for (auto num : nums) {
			frequent[num]++;
		}
		vector<pair<int, int>> arrays;
		for (auto f : frequent) {
			arrays.push_back(f);
		}
		heap_sort_ks(arrays, k, [](pair<int, int> f, pair<int, int> s) { return f.second > s.second; });

		vector<int> result;
		for (int i = 0, j = arrays.size() - 1; i < k; i++, j--) {
			result.push_back(arrays[j].first);
		}
		return result;
	}

	//-------------------------------------------------
	// 349. https://leetcode.com/problems/intersection-of-two-arrays/
	//-------------------------------------------------
	vector<int> intersection(vector<int> nums1, vector<int> nums2) {
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());

		vector<int> result;
		int i = 0, j = 0;
		while (i < nums1.size() && j < nums2.size()) {
			while (i < nums1.size() && nums1[i] < nums2[j]) i++;
			while (j < nums2.size() && nums1[i] > nums2[j]) j++;
			if (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
				result.push_back(nums1[i]);
				i++; j++;
				while (i < nums1.size() && nums1[i] == nums1[i - 1]) i++;
				while (j < nums2.size() && nums2[j] == nums2[j - 1]) j++;
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 349. https://leetcode.com/problems/intersection-of-two-arrays-ii/
	//-------------------------------------------------
	vector<int> intersect(vector<int> nums1, vector<int> nums2) {
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());

		vector<int> result;
		int i = 0, j = 0;
		while (i < nums1.size() && j < nums2.size()) {
			while (i < nums1.size() && nums1[i] < nums2[j]) i++;
			while (j < nums2.size() && nums1[i] > nums2[j]) j++;
			if (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
				result.push_back(nums1[i]);
				i++; j++;
			}
		}
		return result;
	}

	//-------------------------------------------------
	// 357. https://leetcode.com/problems/count-numbers-with-unique-digits/
	//-------------------------------------------------
	int countNumbersWithUniqueDigits(int n) {
		if (n == 0) {
			return 1;
		} else if (n == 1) {
			return 10;
		}
		int result = 10;
		for (int i = 2; i <= n; i++) {
			int base = 9;
			for (int j = 1; j < i; j++) {
				base *= 10 - j;
			}
			result += base;
		}
		return result;
	}

	//-------------------------------------------------
	// 367. https://leetcode.com/problems/valid-perfect-square/
	//-------------------------------------------------
	bool isPerfectSquare(int num) {
		if (num == 1) {
			return true;
		}
		int half = num / 2;
		int low = 1, high = half;
		while (low <= high) {
			int mid = (low + high) / 2;
			uint64_t mid2 = (uint64_t)mid * mid;
			if (mid2 == num) {
				return true;
			} else if (mid2 > num) {
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		}
		return false;
	}

	//-------------------------------------------------
	// 368. https://leetcode.com/problems/largest-divisible-subset/
	//-------------------------------------------------
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		sort(nums.begin(), nums.end());

		vector<int> subset(nums.size(), 0);
		vector<int> parent(nums.size(), 0);

		int max = 0, mi = 0;

		for (int i = nums.size() - 1; i >= 0; --i) { // iterate from end to start since it's easier to track the answer index
			for (int j = i; j < nums.size(); ++j) {
				// check every a[j] that is larger than a[i]
				if (nums[j] % nums[i] == 0 && subset[i] < 1 + subset[j]) {
					// if a[j] mod a[i] == 0, it means T[j] can form a larger subset by putting a[i] into T[j]
					subset[i] = 1 + subset[j];
					parent[i] = j;

					if (subset[i] > max) {
						max = subset[i];
						mi = i;
					}
				}
			}
		}

		vector<int> ret;
		for (int i = 0; i < max; ++i)	{
			ret.push_back(nums[mi]);
			mi = parent[mi];
		}
		return ret;
	}
};

//-------------------------------------------------
// 146. https://leetcode.com/problems/lru-cache/
//-------------------------------------------------
class LRUCache {
public:
	LRUCache(int capacity) {
		this->capacity = capacity;
	}

	int get(int key) {
		if (itmap.count(key) == 0) {
			return -1;
		}
		int value = (*itmap[key]).second;
		cache.erase(itmap[key]);
		cache.push_back({ key, value });
		itmap[key] = --cache.end();
		return value;
	}

	void set(int key, int value) {
		if (itmap.count(key)) {
			cache.erase(itmap[key]);
		} else {
			if (cache.size() >= capacity) {
				auto p = cache.front();
				cache.pop_front();
				itmap.erase(p.first);
			}
		}
		cache.push_back({ key, value });
		itmap[key] = --cache.end();
	}

private:
	int capacity;
	list<pair<int,int>> cache;
	unordered_map<int, list<pair<int,int>>::iterator> itmap;
};

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

//-------------------------------------------------
// 173. https://leetcode.com/problems/binary-search-tree-iterator/
//-------------------------------------------------
class BSTIterator {
	stack<TreeNode *> myStack;
public:
	BSTIterator(TreeNode *root) {
		pushAll(root);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !myStack.empty();
	}

	/** @return the next smallest number */
	int next() {
		TreeNode *tmpNode = myStack.top();
		myStack.pop();
		pushAll(tmpNode->right);
		return tmpNode->val;
	}

private:
	void pushAll(TreeNode *node) {
		for (; node != NULL; myStack.push(node), node = node->left);
	}
};


//-------------------------------------------------
// 208. https://leetcode.com/problems/implement-stack-using-queues/
//-------------------------------------------------
class TrieNode {
public:
	// Initialize your data structure here.
	TrieNode() {
		for (auto &v : child) {
			v = nullptr;
		}
		isKey = false;
	}
	bool isKey;
	TrieNode* child[26];
};

class Trie {
public:
	Trie() {
		root = new TrieNode();
	}

	// Inserts a word into the trie.
	void insert(string word) {
		TrieNode *p = root;
		for (auto c : word) {
			c -= 'a';
			if (p->child[c] == nullptr) {
				p->child[c] = new TrieNode();
			}
			p = p->child[c];
		}
		p->isKey = true;
	}

	// Returns if the word is in the trie.
	bool search(string word) {
		TrieNode *p = root;
		for (auto c : word) {
			c -= 'a';
			if (p->child[c] == nullptr) {
				return false;
			}
			p = p->child[c];
		}
		return p->isKey;
	}

	// Returns if there is any word in the trie
	// that starts with the given prefix.
	bool startsWith(string prefix) {
		TrieNode *p = root;
		for (auto c : prefix) {
			c -= 'a';
			if (p->child[c] == nullptr) {
				return false;
			}
			p = p->child[c];
		}
		return true;
	}

private:
	TrieNode* root;
};

//-------------------------------------------------
// 211. https://leetcode.com/problems/implement-stack-using-queues/
//-------------------------------------------------
class WordDictionary {
public:
	WordDictionary() {
		root = new TrieNode();
	}
	// Adds a word into the data structure.
	void addWord(string word) {
		TrieNode *p = root;
		for (auto c : word) {
			c -= 'a';
			if (p->child[c] == nullptr) {
				p->child[c] = new TrieNode();
			}
			p = p->child[c];
		}
		p->isKey = true;
	}

	// Returns if the word is in the data structure. A word could
	// contain the dot character '.' to represent any one letter.
	bool search(string word) {
		return searchTree(root, word, 0);
	}

	bool searchTree(TrieNode* r, string &word, int start) {
		if (start == word.size()) {
			return r->isKey;
		}
		for (int i = start; i < word.size(); ++i) {
			if (word[i] == '.') {
				for (auto v : r->child) {
					if (v && searchTree(v, word, start + 1)) {
						return true;
					}
				}
				return false;
			}
			else {
				return r->child[word[i] - 'a'] == nullptr ? false : searchTree(r->child[word[i] - 'a'], word, start + 1);
			}
		}
	}

private:
	TrieNode* root;
};

//-------------------------------------------------
// 225. https://leetcode.com/problems/implement-stack-using-queues/
//-------------------------------------------------
class Stack {
public:
	// Push element x onto stack.
	void push(int x) {
		qe.push(x);
	}

	// Removes the element on top of the stack.
	void pop() {
		queue<int> temp;
		while (qe.size() > 1) {
			temp.push(qe.front());
			qe.pop();
		}
		temp.swap(qe);
	}

	// Get the top element.
	int top() {
		queue<int> temp;
		while (qe.size() > 1) {
			temp.push(qe.front());
			qe.pop();
		}
		int result = qe.front();
		temp.push(qe.front());
		temp.swap(qe);
		return result;
	}

	// Return whether the stack is empty.
	bool empty() {
		return qe.empty();
	}

private:
	queue<int> qe;
};

//-------------------------------------------------
// 232. https://leetcode.com/problems/implement-queue-using-stacks/
//-------------------------------------------------
class Queue {
public:
	// Push element x to the back of queue.
	void push(int x) {
		st.push(x);
	}

	// Removes the element from in front of queue.
	void pop(void) {
		stack<int> temp;
		while (st.size() > 1) {
			temp.push(st.top());
			st.pop();
		}
		while (!st.empty()) {
			st.pop();
		}
		while (!temp.empty()) {
			st.push(temp.top());
			temp.pop();
		}
	}

	// Get the front element.
	int peek(void) {
		int result;
		stack<int> temp;
		while (st.size() > 1) {
			temp.push(st.top());
			st.pop();
		}
		result = st.top();
		while (!st.empty()) {
			temp.push(st.top());
			st.pop();
		}
		while (!temp.empty()) {
			st.push(temp.top());
			temp.pop();
		}
		return result;
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return st.empty();
	}

private:
	stack<int> st;
};



//-------------------------------------------------
// 284. https://leetcode.com/problems/peeking-iterator/
//-------------------------------------------------
//class Iterator {
//	struct Data;
//	Data* data;
//public:
//	Iterator(const vector<int>& nums);
//	Iterator(const Iterator& iter);
//	virtual ~Iterator();
//	// Returns the next element in the iteration.
//	int next();
//	// Returns true if the iteration has more elements.
//	bool hasNext() const;
//};
//class PeekingIterator : public Iterator {
//public:
//	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
//		// Initialize any member here.
//		// **DO NOT** save a copy of nums and manipulate it directly.
//		// You should only use the Iterator interface methods.
//		data = nullptr;
//	}
//
//	// Returns the next element in the iteration without advancing the iterator.
//	int peek() {
//		if (data != nullptr) {
//			return *data;
//		} else {
//			*data = Iterator::next();
//			return *data;
//		}
//	}
//
//	// hasNext() and next() should behave the same as in the Iterator interface.
//	// Override them if needed.
//	int next() {
//		if (data != nullptr) {
//			int result = *data;
//			data = nullptr;
//			return result;
//		} else {
//			return Iterator::next();
//		}
//	}
//
//	bool hasNext() const {
//		return data != null || Iterator::hasNext();
//	}
//};

//-------------------------------------------------
// 295. https://leetcode.com/problems/find-median-from-data-stream/
//-------------------------------------------------
class MedianFinder {
public:
	// Adds a number into the data structure.
	void addNum(int num) {
		if (smaller_.size() == biger_.size()) {
			if (smaller_.empty() || num <= smaller_.top()) {
				smaller_.push(num);
			} else {
				biger_.push(num);
				smaller_.push(biger_.top());
				biger_.pop();
			}
		} else {
			if (num > smaller_.top()) {
				biger_.push(num);
			} else {
				smaller_.push(num);
				biger_.push(smaller_.top());
				smaller_.pop();
			}
		}
	}

	// Returns the median of current data stream
	double findMedian() {
		if (smaller_.size() > biger_.size()) {
			return static_cast<double>(smaller_.top());
		} else {
			return (smaller_.top() + biger_.top()) / 2.0;
		}
	}

private:
	priority_queue<int> smaller_;
	priority_queue<int, std::vector<int>, std::greater<int>> biger_;
};

//-------------------------------------------------
// 297. https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
//-------------------------------------------------
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		return this->levelOrder(root);
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		return this->makeBinaryTree(data);
	}
private:
	TreeNode* makeBinaryTree(const string &strs) {
		TreeNode *root = nullptr;
		if (strs.empty()) {
			return root;
		}

		char *cstr = new char[strs.size() + 1];
		strcpy(cstr, strs.c_str());
		char *p = strtok(cstr, ",");
		root = new TreeNode(atoi(p));
		queue<TreeNode*> treeQueue;
		treeQueue.push(root);
		char *left, *right;
		while (!treeQueue.empty()) {
			left = strtok(NULL, ",");
			if (left == nullptr) {
				break;
			}
			auto parent = treeQueue.front();
			treeQueue.pop();
			if (strcmp(left, "#") != 0) {
				parent->left = new TreeNode(atoi(left));
				treeQueue.push(parent->left);
			}

			right = strtok(NULL, ",");
			if (right == nullptr) {
				break;
			}
			if (strcmp(right, "#") != 0) {
				parent->right = new TreeNode(atoi(right));
				treeQueue.push(parent->right);
			}
		}
		return root;
	}
	string levelOrder(TreeNode* root) {
		queue<TreeNode*> tq;
		string result;
		if (root == NULL) {
			return result;
		}

		tq.push(root);
		while (!tq.empty()) {
			TreeNode* p = tq.front();
			if (p) {
				result += string(",") + to_string(p->val);
				tq.push(p->left);
				tq.push(p->right);
			}
			else {
				result += ",#";
			}
			tq.pop();
		}
		return result.substr(1);// remove ","
	}
};

//-------------------------------------------------
// 303. https://leetcode.com/problems/range-sum-query-immutable/
//-------------------------------------------------
class NumArray {
public:
	NumArray(vector<int> &nums) {
		this->nums = nums;
		for (int i = 1; i < nums.size(); ++i) {
			this->nums[i] += this->nums[i - 1];
		}
	}

	int sumRange(int i, int j) {
		int sum = nums[j] - nums[i];
		if (i != 0) {
			sum += nums[i] - nums[i - 1];
		}
		else {
			sum += nums[i];
		}
		return sum;
	}

private:
	vector<int> nums;
};

//-------------------------------------------------
// 304. https://leetcode.com/problems/range-sum-query-2d-immutable/
//-------------------------------------------------
class NumMatrix {
public:
	NumMatrix(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) {
			return;
		}
		int m = matrix.size() + 1;
		int n = matrix[0].size() + 1;

		_matrix.emplace_back(n, 0);

		for (int i = 0; i < matrix.size(); ++i) {
			vector<int> row(n, 0);
			for (int j = 1; j < n; ++j) {
				row[j] = matrix[i][j - 1];
			}
			_matrix.push_back(row);
		}

		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				_matrix[i][j] += _matrix[i - 1][j] + _matrix[i][j - 1];
				_matrix[i][j] -= _matrix[i - 1][j - 1];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		int result = _matrix[row2 + 1][col2 + 1] + _matrix[row1][col1];
		result -= _matrix[row2 + 1][col1] + _matrix[row1][col2 + 1];
		return result;
	}

private:
	vector<vector<int>> _matrix;
};

//-------------------------------------------------
// 307. https://leetcode.com/problems/range-sum-query-mutable/
//-------------------------------------------------
class NumArrayii {
public:
	NumArrayii(vector<int> &nums) {
		if (nums.empty()) {
			return;
		}
		data = nums;
		sum.resize(nums.size());
		sum[0] = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			sum[i] = sum[i - 1] + nums[i];
		}
	}

	void update(int i, int val) {
		int diff = val - data[i];
		data[i] = val;
		for (int j = i; j < sum.size(); j++) {
			sum[j] += diff;
		}
	}

	int sumRange(int i, int j) {
		int low = (i == 0) ? 0 : sum[i - 1];
		return sum[j] - low;
	}

private:
	vector<int> sum;
	vector<int> data;
};