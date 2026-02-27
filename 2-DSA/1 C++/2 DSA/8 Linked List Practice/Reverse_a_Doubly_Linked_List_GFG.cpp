/*
Reverse_a_Doubly_Linked_List_GFG

Given a doubly linked list of n elements. The task is to reverse the doubly linked list.

    Example 1:
    Input:
    LinkedList: 3 <--> 4 <--> 5
    Output: 5 4 3
*/

struct Node
{
    int data;
    Node * next;
    Node * prev;
    Node (int x)
    {
        data=x;
        next=NULL;
        prev=NULL;
    }
        
};
*/
Node* reverseDLL(Node * head)
{
    Node* curr = head;
    Node* prev = NULL;;
    Node* next = NULL;
    while(curr != NULL)
    {
        next = curr -> next;
        curr -> next = prev;
        curr -> prev = next;
        prev = curr;
        curr = next;
        
    }
    return prev;
}

