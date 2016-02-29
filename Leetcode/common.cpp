#include "common.h"

ListNode* makeList(const vector<int> &values) {
	ListNode head(0);
	ListNode* p = &head;
	for (auto v : values) {
		p->next = new ListNode(v);
		p = p->next;
	}
	return head.next;
}

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
		if (strcmp(left, "null") != 0) {
			parent->left = new TreeNode(atoi(left));
			treeQueue.push(parent->left);
		}

		right = strtok(NULL, ",");
		if (right == nullptr) {
			break;
		}
		if (strcmp(right, "null") != 0) {
			parent->right = new TreeNode(atoi(right));
			treeQueue.push(parent->right);
		}
	}
	return root;
}

TreeLinkNode* makeBinaryLinkTree(const string &strs) {
	TreeLinkNode *root = nullptr;
	if (strs.empty()) {
		return root;
	}

	char *cstr = new char[strs.size() + 1];
	strcpy(cstr, strs.c_str());
	char *p = strtok(cstr, ",");
	root = new TreeLinkNode(atoi(p));
	queue<TreeLinkNode*> treeQueue;
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
			parent->left = new TreeLinkNode(atoi(left));
			treeQueue.push(parent->left);
		}

		right = strtok(NULL, ",");
		if (right == nullptr) {
			break;
		}
		if (strcmp(right, "#") != 0) {
			parent->right = new TreeLinkNode(atoi(right));
			treeQueue.push(parent->right);
		}
	}
	return root;
}

// https://leetcode.com/faq/#different-output
void test_makeTree() {
	auto t1 = makeBinaryTree("1");
	auto t2 = makeBinaryTree("1,2,3");
	auto t3 = makeBinaryTree("1,null,2,3");
	auto t4 = makeBinaryTree("5,4,7,3,null,2,null,-1,null,9");
}