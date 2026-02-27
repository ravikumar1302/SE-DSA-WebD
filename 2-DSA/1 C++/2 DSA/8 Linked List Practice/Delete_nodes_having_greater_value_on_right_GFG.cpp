/*
Delete_nodes_having_greater_value_on_right_GFG

Given a singly linked list, remove all the nodes which have a greater value on their right side.

    Example 1:

    Input:
    LinkedList = 12->15->10->11->5->6->2->3
    Output: 15 11 6 3
    Explanation: Since, 12, 10, 5 and 2 are the elements which have greater elements on the following nodes. So, after deleting them, the linked list would like be 15, 11, 6, 3.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)

*/

The structure of linked list is the following

struct Node
{
    int data;
    Node* next;
    
    Node(int x){
        data = x;
        next = NULL;
    }
};
*/
class Solution
{
    public:
    Node* reverse(Node* head)
    {
        if(head == NULL)
            return head;
        
        Node* prev = NULL;
        Node* fwd = NULL;
        Node* curr = head;
        
        while(curr != NULL)
        {
            fwd = curr -> next;
            curr -> next = prev;
            prev = curr;
            curr = fwd;
        }
        return prev;
    }
    
    Node *compute(Node *head)
    {
        // Approach : reverse the LL and if any element comes smaller than the largest, delete it
        
        Node* newHead = reverse(head);
        Node* temp = newHead;
        
        int largest = temp -> data;
        Node* prev = NULL;
        Node* fwd = NULL;
        Node* curr = head;
        
        while(temp != NULL && temp -> next != NULL)
        {
            if( temp -> next -> data < largest)
            {
                // Delete temp -> next
                Node* dummy = temp -> next;
                temp -> next = temp -> next -> next;
                delete dummy;
                
            }
            else
            {
                // move ahead and change largest
                temp = temp -> next;
                largest = temp -> data;
            }
        }
        newHead = reverse(newHead);
        return newHead;
        
    }
    
};