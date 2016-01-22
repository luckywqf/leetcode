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

ListNode* makeList(const vector<int> &values);
TreeNode* makeBinaryTree(const string &strs);