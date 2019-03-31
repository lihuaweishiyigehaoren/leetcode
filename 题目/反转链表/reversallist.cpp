/*
反转一个单链表。

示例:

输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
*/
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode * p = head;
        ListNode * q = head->next;
        ListNode * r ;

        p->next = nullptr;

        while(q != nullptr)
        {
            r = q->next;
            q->next = p;

            p = q;
            q = r;
            
        }
        

        

        return p;
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
    reValue = A.reverseList(a);
    std::cout<< "reValue->val"<<std::endl;

    ListNode * reValueLook = new ListNode(0);
    reValueLook = reValue;
    while(reValueLook != nullptr){
        std::cout << reValueLook->val <<std::endl;
        reValueLook = reValueLook->next;
    }
    

    return 0;
}

// #include <iostream>
// #include <vector>
// using namespace std;

// class A {
// public:
// 	void fun1() {
// 		cout << "A1" << endl;
// 		fun2();
// 	}
// 	void fun2() {
// 		cout << "A2" << endl;
// 		fun3();
// 	}
// 	void fun3() {
// 		cout << "A3" << endl;
// 		fun4();
// 	}
// 	void fun4() {
// 		cout << "A4" << endl;
// 	}

// };

// class B :public A {
// public:
//     // void fun1() {
// 	// 	cout << "B1" << endl;
// 	// 	fun2();
// 	// }
// 	// void fun2() {
// 	// 	cout << "B2" << endl;
// 	// 	fun3();
// 	// }
// 	void fun3() {
// 		cout << "B3" << endl;
// 		fun4();
// 	}
// 	void fun4() {
// 		cout << "B4" << endl;
// 	}
// };

// int main() {
// 	A a;
// 	B b;
// 	a.fun1();
// 	b.fun1();
    
//     // std::cout<<sizeof(a)<<std::endl;
//     // std::cout<<sizeof(b)<<std::endl;
// 	system("pause");
// 	return 0;
// }