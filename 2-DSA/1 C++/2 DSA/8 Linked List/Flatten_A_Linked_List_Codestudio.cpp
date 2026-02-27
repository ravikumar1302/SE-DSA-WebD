/*
Flatten_A_Linked_List_Codestudio

You are given a linked list containing N nodes, where every node in the linked list contains two pointers, first one is ‘NEXT’ which points to the next node in the list and the second one is ‘CHILD’ pointer to a linked list where the head is this node. 
And each of these child linked lists is in sorted order.
Your task is to flatten this linked such that all nodes appear in a single layer or level while the nodes should maintain the sorted order.

For Example:
The given linked list is - 

So your output should be 

1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 12 → 20 → null.
*/


#include <bits/stdc++.h> 
/****************************************************************

    Following is the class structure of the Node class:

class Node {
public:
	int data;
	Node* next;
	Node* child;

	Node(int data) {
		this->data = data;
		this->next = NULL;
		this->child = NULL;
	}
};

*****************************************************************/

#include <bits/stdc++.h> 
/****************************************************************

    Following is the class structure of the Node class:

class Node {
public:
	int data;
	Node* next;
	Node* child;

	Node(int data) {
		this->data = data;
		this->next = NULL;
		this->child = NULL;
	}
};

Expected Time Complexity: O(N*N*M)
Expected Auxiliary Space: O(1)

*****************************************************************/
Node* merge(Node* a, Node* b)
{
    if(a == NULL) 
        return b;
    if(b == NULL) 
        return a;
    
    Node* res = new Node(-1);
    Node* temp = res;
    
    while(a != NULL && b != NULL)
    {
        if(a -> data <= b -> data)
        {
            temp -> child = a;
            temp = temp -> child;
            a = a -> child;
            temp -> next = NULL;
        }
        else //b-> data > a -> data
        {
            temp -> child = b;
            temp = temp -> child;
            b = b -> child;
            temp -> next = NULL;
        }
    }
    if( a != NULL )    //elements left in a 
        temp -> child = a;
    else if(b != NULL)
        temp -> child = b;
    
    temp = res;
    res = res-> child;
    delete temp;
    return res;
}

Node* flattenLinkedList(Node* head) 
{
	if(head == NULL || head -> next == NULL)
        return head;
    //Recursive call
    Node* down = head;
    Node* head2 = head -> next;
    head -> next = NULL;
    Node* right = flattenLinkedList(head2);

    Node* res = merge(down, right);
    return res;
}
