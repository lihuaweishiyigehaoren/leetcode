#include <stddef.h>
#include <iostream>
using namespace std;
 // Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

/*
*@describe my solution
*/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *l3 = new ListNode(-1);
		ListNode *currentNode = l3;
        int addition = 0;
		int addend = 0, be_addend = 0;
        while(l1 != NULL || l2 != NULL){
			l1==NULL?addend=0:addend=l1->val;
			l2==NULL?be_addend=0:be_addend=l2->val;
            int sum = addend + be_addend + addition;
            if(sum/10==0){
				addition = 0;
                currentNode->val = sum;
            }else{
                addition = 1;
                currentNode->val = sum%10;
            }

			if(l1 != NULL) l1 = l1->next;
			if(l2 != NULL) l2 = l2->next;

			if(l1==NULL&&l2==NULL){
				if(addition==1){
					currentNode->next = new ListNode(1);
				}else{
					break;
				}			
			}else{
				currentNode->next = new ListNode(-1);
			}
			
			currentNode = currentNode->next;
        }
        return l3;
    }
};


int main(){
	/*
	*@test1
	*/
	ListNode* l1 = new ListNode(2);
	l1->next = new ListNode(4);
	l1->next->next = new ListNode(3);
	ListNode* l2 = new ListNode(5);
	l2->next = new ListNode(6);
	l2->next->next = new ListNode(4);
	/*
	*@test2
	*/
	//ListNode *l1 = new ListNode(1);
	//ListNode *l2 = new ListNode(1);
	//l2->next = new ListNode(4);
	Solution s;
	ListNode* l3 = s.addTwoNumbers(l1,l2);
	cout<<l3->val<<" -> "<<l3->next->val<<" -> "<<l3->next->next->val;
	return 0;
}
