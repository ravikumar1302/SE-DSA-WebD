/*
Intersection_of_two_sorted_Linked_lists_GFG

Given two lists sorted in increasing order, create a new list representing the intersection of the two lists. The new list should be made with its own memory — the original lists should not be changed.
Note: The list elements are not necessarily distinct.

    Example 1:

    Input:
    L1 = 1->2->3->4->6
    L2 = 2->4->6->8
    Output: 2 4 6
    Explanation: For the given first two linked list, 2, 4 and 6 are the elements in the intersection.
*/

void insertAtTail(Node* &head, Node* &tail, int value)
{
    Node* temp = new Node(value);
    if(head == NULL)    //Empty list
    {
        tail = temp;
        head = temp;
        return ;
    }
    else
    {
        tail -> next = temp;
        tail = temp;
    }
}

Node* findIntersection(Node* head1, Node* head2)
{
    Node* anshead = NULL;
    Node* anstail = NULL;
    
    while(head1 != NULL && head2 != NULL)
    {
        int a = head1 -> data;
        int b = head2 -> data;
        if(a == b)
        {
            insertAtTail(anshead, anstail, a);
            head1 = head1 -> next;
            head2 = head2 -> next;
        }
            
        else if(a < b)
            head1 = head1 -> next;
        
        else if(b < a)
            head2 = head2 -> next;
    }
    return anshead;
}
