/*
����һ������ɾ������ĵ����� n ���ڵ㣬���ҷ��������ͷ��㡣

ʾ����

����һ������: 1->2->3->4->5, �� n = 2.

��ɾ���˵����ڶ����ڵ�������Ϊ 1->2->3->5.
˵����

������ n ��֤����Ч�ġ�

���ף�

���ܳ���ʹ��һ��ɨ��ʵ����
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