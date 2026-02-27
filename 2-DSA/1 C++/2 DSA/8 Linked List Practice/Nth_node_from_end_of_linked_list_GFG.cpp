/*
Nth_node_from_end_of_linked_list_GFG

Given a linked list consisting of L nodes and given a number N. The task is to find the Nth node from the end of the linked list.

Example 1:
Input : N = 2, LinkedList: 1->2->3->4->5->6->7->8->9
Output : 8
Explanation : In the first example, there are 9 nodes in linked list and we need to find 2nd node from end. 2nd node from end os 8.  

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(1).
*/

// Aproach count total nodes 
// Time : O(N)
// Space : O(1)

int count_size(Node *head)
{
    int count = 0;
    while(head != NULL)
    {
        head = head->next;
        count++;
    }
    return count;
}
int getNthFromLast(Node *head, int n)
{
       int size = count_size(head);
       if(n > size)    
            return -1;
        
       Node *temp = head;
       int count = size - n + 1;
       while(temp != NULL && count > 1)
       {
           temp = temp -> next;
           count--;
       }
       
       return temp -> data;
}