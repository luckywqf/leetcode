#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <memory>
#include <tuple>
#include <numeric>
#include <cstdint>
#include <cstring>
#include <cassert>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

inline int GetListLength(ListNode *head) {
	int len = 0;
	ListNode *p = head;
	while (p) {
		++len;
		p = p->next;
	}
	return len;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

template<typename T>
inline T myabs(T t) {
	return t > 0 ? t : -t;
}

template<class T, class Compare>
void make_heap(vector<T> &nums, int len, int index, Compare com) {
	int i = index;
	while (i < len) {
		int child = i * 2 + 1;
		if (child >= len) {
			break;
		}
		if (child + 1 < len && com(nums[child + 1], nums[child])) {
			child = child + 1;
		}
		if (com(nums[child], nums[i])) {
			swap(nums[child], nums[i]);
			i = child;
		}
		else {
			break;
		}
	}
}

template<class T, class Compare>
void heap_sort(vector<T> &nums, Compare com = std::less<T>()) {
	int first = nums.size() / 2 - 1;
	for (int i = first; i >= 0; i--) {
		make_heap(nums, nums.size(), i, com);
	}
	for (int i = nums.size() - 1; i >= 0; i--) {
		swap(nums[i], nums[0]);
		make_heap(nums, i, 0, com);
	}
}

template<class T, class Compare>
void heap_sort_ks(vector<T> &nums, int k, Compare com = std::less<T>()) {
	int first = nums.size() / 2 - 1;
	for (int i = first; i >= 0; i--) {
		make_heap(nums, nums.size(), i, com);
	}
	for (int i = nums.size() - 1, j = 0; i >= 0 && j < k; i--, j++) {
		swap(nums[i], nums[0]);
		make_heap(nums, i, 0, com);
	}
}

template<class T, class Compare>
T heap_sort_kth(vector<T> &nums, int k, Compare com = std::less<T>()) {
	int first = nums.size() / 2 - 1;
	for (int i = first; i >= 0; i--) {
		make_heap(nums, nums.size(), i, com);
	}
	for (int i = nums.size() - 1, j = 1; i >= 0; i--, j++) {
		if (j == k) {
			return nums[0];
		}
		swap(nums[i], nums[0]);
		make_heap(nums, i, 0, com);
	}
}

ListNode* makeList(const vector<int> &values);
TreeNode* makeBinaryTree(const string &strs);
TreeLinkNode* makeBinaryLinkTree(const string &strs);