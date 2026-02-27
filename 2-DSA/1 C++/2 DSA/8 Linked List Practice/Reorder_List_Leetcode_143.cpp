/*
Reorder_List_Leetcode_143

You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.

Example 1:
Input: head = [1,2,3,4]
Output: [1,4,2,3]
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
    ListNode* reverse(ListNode* head)
    {
        if(head == NULL)
            return head;
        ListNode* curr = head;
        ListNode* prev = NULL;
        ListNode* fwd = NULL;
        
        while(curr != NULL)
        {
            fwd = curr -> next;
            curr -> next = prev;
            prev = curr;
            curr = fwd;
        }
        return prev;
    }
    
    void reorderList(ListNode* head) {
        
        //find mid
        // Reverse right half
        // Now link elemetns one by one, starting from left then right ans so on
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while(fast != NULL && fast -> next != NULL )
        {
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        
        ListNode* mid = slow;
        ListNode* right = slow -> next;
        mid -> next = NULL;
        ListNode* left = head;
        
        right = reverse(right);
        
        while(left != NULL && right != NULL)
        {
            ListNode* fwd = left -> next;
            left -> next = right;
            ListNode* fwd2 = right -> next;
            right -> next = fwd;
            
            left = fwd;
            right = fwd2;
        }
        head = left;
    }
};