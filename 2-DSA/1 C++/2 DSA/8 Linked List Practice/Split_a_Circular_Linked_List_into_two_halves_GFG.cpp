/*
Split_a_Circular_Linked_List_into_two_halves_GFG

Given a Cirular Linked List of size N, split it into two halves circular lists. If there are odd number of nodes in the given circular linked list then out of the resulting two halved lists, first list should have one node more than the second list. The resultant lists should also be circular lists and not linear lists.

    Example 1:
    Input : Circular LinkedList: 1->5->7
    Output:
    1 5
    7
*/
/* The structure of linked list is the following
struct Node
{
  int data;
  struct Node *next;
  
  Node(int x){
      data = x;
      next = NULL;
  }
};
*/

//  function which splits the circular linked list.  head is pointer
// to head Node of given lined list.  head1_ref1 and *head_ref2
// are pointers to head pointers of resultant two halves.

void splitList(Node *head, Node **head1_ref, Node **head2_ref)
{
    if(head == NULL)
        return;
        
    Node* slow = head;
    Node* fast = head;
    while(fast -> next != head && fast -> next -> next != head)
    {
        fast = fast -> next -> next;
        slow = slow -> next;
    }
    *head2_ref = slow -> next;
    *head1_ref = head;
    
    //making split list circular
    slow -> next = head;
    if(fast -> next == head)
        fast -> next = *head2_ref;
    else
        fast -> next -> next = * head2_ref;
    
}