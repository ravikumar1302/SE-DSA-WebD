/*
Reverse_DLL_nodes_in_groups_Codestudio

You are given a Doubly Linked List of integers and a positive integer 'K' representing the group size. Modify the linked list by reversing every group of 'K' nodes in the linked list.
A doubly linked list is a type of linked list that is bidirectional, that is, it can be traversed in both directions, forward and backward.

    Example
    Linked list: 8 9 10 11 12
    K: 3 

    Output: 10 9 8 12 11

    We reverse the first K (3) nodes. Now, since the number of nodes remaining in the list (2) is less than K, we just reverse the remaining nodes (11 and 12).  

*/
/*********************************************************

    Following is the class structure of the Node class:

    class Node
	{
	public:
	    int data;
	    Node *next;
	    Node *prev;
	    Node(int data)
	    {
	        this->data = data;
	        this->next = NULL;
	        this->prev = NULL;
	    }
	};

************************************************************/

Node* reverseDLLInGroups(Node* head, int k)
{	
    //Base case
    if(head == NULL)
        return head;
    
    //Fistly reverse first k nodes
    Node* curr = head;
    Node* prev = NULL;
    Node* fwd = NULL;
    int count = 0;
    
    while(curr != NULL && count < k)
    {
        fwd = curr -> next;
        curr -> next = prev;
        curr -> prev = fwd;
        
        //Update pointers
        prev = curr;
        curr = fwd;
        count++;
    }
    // prev represents the head of reversed linked list
    
    //Now recursion
    if(fwd != NULL)
        head -> next = reverseDLLInGroups(fwd ,k);
    return prev;
}

