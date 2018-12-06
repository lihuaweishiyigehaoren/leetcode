#include <stddef.h>
#include <iostream>
using namespace std;
 // Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *l3 = new ListNode(-1);
		ListNode *currentNode = l3;
        int addition = 0;
        while(l1 != NULL && l2 != NULL){
            int sum = l1->val + l2->val + addition;
            if(sum/10==0){
				addition = 0;
                currentNode->val = sum;
            }else{
                addition = 1;
                currentNode->val = sum%10;
            }
            l1 = l1->next;
            l2 = l2->next;
			currentNode->next = new ListNode(-1);
			currentNode = currentNode->next;
        }
        return l3;
    }
};


int main(){
	ListNode* l1 = new ListNode(2);
	l1->next = new ListNode(4);
	l1->next->next = new ListNode(3);
	ListNode* l2 = new ListNode(5);
	l2->next = new ListNode(6);
	l2->next->next = new ListNode(4);
	Solution s;
	ListNode* l3 = s.addTwoNumbers(l1,l2);
	cout<<l3->val<<" -> "<<l3->next->val<<" -> "<<l3->next->next->val;
	return 0;
}
