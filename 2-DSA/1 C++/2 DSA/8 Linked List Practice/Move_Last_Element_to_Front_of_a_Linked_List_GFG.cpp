/*
Move_Last_Element_to_Front_of_a_Linked_List_GFG

You are given the head of a Linked List. You have to move the last element to the front of the Linked List and return the list.

    Example 1:

    Input : N = 5, List = {2,5,6,2,1}
    Output : {1,2,5,6,2}
    Explanation : In the given linked list, the last element is 1, after moving the last element to the front the linked list will be {1,2,5,6,2}.
*/

class Solution{
public:
    ListNode *moveToFront(ListNode *head)
    {
        if(head == NULL || head -> next == NULL)
            return head;
        ListNode* refHead = head;
        ListNode* last = head;
        ListNode* lastsecond = head;
        
        while(last != NULL && last -> next != NULL)
        {
            lastsecond = last;
            last = last -> next;
        }
        //Now last reached to null
        lastsecond -> next = NULL;
        last -> next = refHead;
        head = last;
        return head;
        
    }
};