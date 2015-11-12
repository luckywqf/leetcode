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