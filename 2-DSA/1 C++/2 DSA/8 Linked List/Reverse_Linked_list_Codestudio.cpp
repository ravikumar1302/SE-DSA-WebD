/*
Reverse_Linked_list_Codestudio

Given a singly linked list of integers. Your task is to return the head of the reversed linked list.
For Example:
The given linked list is 1 -> 2 -> 3 -> 4-> NULL. Then the reverse linked list is 4 -> 3 -> 2 -> 1 -> NULL and the head of the reversed linked list will be 4.
Follow Up :
*/

#include <bits/stdc++.h> 
/****************************************************************

    Following is the class structure of the LinkedListNode class:

    template <typename T>
    class LinkedListNode
    {
    public:
        T data;
        LinkedListNode<T> *next;
        LinkedListNode(T data)
        {
            this->data = data;
            this->next = NULL;
        }
    };

*****************************************************************/

//Recursion Method-2
// it will return the head of the reverse list
LinkedListNode<int>* reverse1(LinkedListNode<int>* head)
    {
        if(head == NULL || head -> next == NULL)    //base case
            return head;

        LinkedListNode<int>* smallhead = reverse1(head -> next);
        head -> next -> next = head;
        head -> next = NULL;
        return smallhead;
    }

//Recursion Method-1
void reverse (LinkedListNode<int>* &head, LinkedListNode<int>* curr, LinkedListNode<int>* prev)
{
    // base case
    if(curr == NULL)
    {
        head = prev;
        return;
    }
    LinkedListNode<int>* forward = curr -> next;
    reverse(head, forward, curr);
    curr -> next = prev;
}

LinkedListNode<int> *reverseLinkedList(LinkedListNode<int> *head) 
{
    //For method 2
    return reverse1(head);
    /*
    //For method 1
    LinkedListNode<int>* curr = head;
    LinkedListNode<int>* prev = NULL;
    reverse(head, curr, prev);
    return head;
   
    //Itreative method
    if(head == NULL || head -> next == NULL)    //Empty list or 1 node only
        return head; 
    
    LinkedListNode<int>* prev = NULL;
    LinkedListNode<int>* curr = head;
    LinkedListNode<int>* forward = NULL;
    while(curr != NULL)
    {
        forward = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = forward;
    }
    return prev;
    */
}