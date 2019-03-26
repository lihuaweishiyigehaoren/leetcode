/*
给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：

给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：

给定的 n 保证是有效的。

进阶：

你能尝试使用一趟扫描实现吗？
*/
#include <iostream>


 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };


class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {

		int length = 0;
		ListNode * dummy = new ListNode(0);
		dummy->next = head;
		ListNode * first = head;
		while (first != NULL)
		{
			length++;
			first = first->next;
		}

		length = length - n;

		while (length>0)
		{
			length--;
			first = first->next;
		}

		first->next = first->next->next;

		return dummy->next;
	}
};

int main()
{
	ListNode * a = new ListNode(1);
	ListNode * b = new ListNode(2);
	ListNode * c = new ListNode(3);
	ListNode * d = new ListNode(4);
	ListNode * e = new ListNode(5);
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;

	ListNode * reValue;
	Solution A;
	reValue = A.removeNthFromEnd(a, 2);

	// std::cout << "helloworld" << std::endl;

	system("pause");
	return 0;
}