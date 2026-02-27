/*
Remove_Linked_List_Elements_Leetcode_203

Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.
    Example 1:
    Input: head = [1,2,6,3,4,5,6], val = 6
    Output: [1,2,3,4,5]
   
    Example 2:
    Input: head = [], val = 1
    Output: []

    Example 3:
    Input: head = [7,7,7,7], val = 7
    Output: []
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(head == NULL)
            return head;


        ListNode* curr = head;
        while(curr != NULL)
        {
            //element found, remove it
            if( curr -> next != NULL && (curr -> next -> val == val) )
            {
                ListNode* next_next = curr -> next -> next;
                ListNode* to_del = curr -> next;
                delete to_del;
                curr -> next = next_next;
            }
            else
                curr = curr -> next;
        }
                
        // if head need to be deleted
        if(head != NULL && head -> val == val)
        {
            ListNode* temp = head;
            head = head -> next;
            temp -> next = NULL;
            delete temp;
        }
        
        return head;
    }
};
