/*
Remove_Nth_Node_From_End_of_List_Leetcode_19

Given the head of a linked list, remove the nth node from the end of the list and return its head.

    Example 1:
    Input: head = [1,2,3,4,5], n = 2
    Output: [1,2,3,5]

    Example 2:
    Input: head = [1], n = 1
    Output: []

    Example 3:
    Input: head = [1,2], n = 1
    Output: [1]

Follow up: Could you do this in one pass?
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
    int get_length(ListNode* head)
    {
        int size = 0;
        while(head != NULL)
        {
            head = head->next;
            size++;
        }
        return size;
    }
    
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        // Step-1 : Find list length
        int size = get_length(head);
        if(size == n)
            return head->next;
        
        // Step-2 : Traverse till (size - n) and point that node to next node
        int cnt = 0;
        ListNode* temp = head;
        
        while(temp != NULL && cnt < size - n - 1)
        {
            temp = temp -> next;
            cnt++;
        }
        
        // Step-3 : Delete node
        temp -> next = temp->next->next;
        
        // Step-4 : Return ans
        return head;
    }
};