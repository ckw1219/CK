#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//快排链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0),next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* division(ListNode* head, ListNode* povit, ListNode* node_end) {
    int base_val = povit->val;

    ListNode* temp_cur = povit;
    ListNode* cur = povit;

    cur = cur->next;
    while (cur != node_end) {
        if (cur->val < base_val) {
            temp_cur = temp_cur->next;

            int temp_val = temp_cur->val;
            temp_cur->val = cur->val;
            cur->val = temp_val;
        }
        cur = cur->next;
    }

    swap(povit->val, temp_cur->val);

    return temp_cur;
}

void quick_sort_list(ListNode* head, ListNode* povit, ListNode* node_end) {
    if (povit != node_end) {
        ListNode* base_node = division(head, povit, node_end);

        // ListNode* cur = head;
        // ListNode* pre;
        // while (cur != base_node) {
        //     pre = cur;
        //     cur = cur->next;
        // }
        quick_sort_list(head, povit, base_node);
        quick_sort_list(head, base_node->next, node_end);
    }
}


int main() {
    ListNode* head = new ListNode(4);
    ListNode* cur = head;
    cur->next = new ListNode(1);
    cur = cur->next;

    cur->next = new ListNode(3);
    cur = cur->next;

    cur->next = new ListNode(5);
    cur = cur->next;

    cur->next = new ListNode(2);
    cur = cur->next;

    ListNode* node_end = head;
    while (node_end->next) {
        node_end = node_end->next;
    }
    quick_sort_list(head, head, nullptr);
    
    while (head) {
        std::cout << head->val <<endl;
        head = head->next;
    }
    return 0;
}



// #include<iostream>
// #include<algorithm>
// using namespace std;
// class ListNode {
// public:
//     int val;
//     ListNode *next;
//     ListNode(int val) {
//         this->val = val;
//         this->next = NULL;
// 	}
// };
 
// void print_node(ListNode *head,ListNode *end){
// 	//输出链表 
// 	while(head!=end){
// 		cout<<head->val<<" ";
// 		head=head->next;
// 	}
// 	cout<<endl;
// }
   
// void quickSort(ListNode *start,ListNode *end) {
//     // write your code here
//     if(start==end) 
// 		return ;
// 	ListNode *slow=start;
//     ListNode *fast=start->next;
//     int k=start->val;
//     while(fast!=end){
//     	if(fast->val < k){
//     		swap(slow->next->val,fast->val);
//     		slow=slow->next;
// 		}
// 		fast=fast->next;
// 	}
// 	swap(slow->val,start->val);
// 	print_node(start,end);
// 	quickSort(start,slow);
// 	quickSort(slow->next,end);
// }
	  
// int main() {
// 	int a[]={4,8,2,3,2,5,6,4,8,13,10};
// 	ListNode *l1,*p;
// 	l1=new ListNode(a[0]);
// 	p=l1;
// 	for(int i=1;i<(sizeof(a)/sizeof(int));i++){
// 		ListNode *temp=new ListNode(a[i]);
// 		p->next=temp;
// 		p=p->next;
// 	}
// 	quickSort(l1,NULL);
// 	print_node(l1,NULL);	
// }