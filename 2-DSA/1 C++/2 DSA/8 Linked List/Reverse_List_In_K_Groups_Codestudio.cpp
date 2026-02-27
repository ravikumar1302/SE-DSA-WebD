/*
Reverse_List_In_K_Groups_Codestudio

You are given a linked list of 'N' nodes and an integer 'K'. You have to reverse the given linked list in groups of size K i.e if the list contains x nodes numbered from 1 to x, then you need to reverse each of the groups (1,K),(K+1,2*K), and so on.
For example, if the list is [1, 2, 3, 4, 5, 6] and K = 2, then the new list will be [2, 1, 4, 3, 6, 5].
Note:
1. In case the number of elements in the last cannot be evenly divided into groups of size k, then just reverse the last group(with any size). For example if the list is 1 2 3 4 5 and K = 3, then the answer would be 3 2 1 5 4.

2. All the node values will be distinct.
*/

/****************************************************************
    Following is the Linked List node structure

    class Node
    {
    public:
        int data;
        Node *next;
        Node(int data)
        {
            this->data = data;
            this->next = NULL;
        }
    };

*****************************************************************/


Node* kReverse(Node* head, int k) {
    //base case
    if(head == NULL)
        return NULL;
    
    //Step-1: Reverse first  k nodes
    Node* next = NULL;
    Node* curr = head;
    Node* prev = NULL;
    int count = 0;
    
    while(curr != NULL && count < k)
    {
        next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    
    //Step-2: Recursion
    if(next!= NULL)
        head -> next = kReverse(next, k);
    
    return prev;
}