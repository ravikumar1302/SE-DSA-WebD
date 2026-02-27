/*
Reverse_Nodes_in_k-Group_Leetcode_25

Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

    Example 1:
    Input: head = [1,2,3,4,5], k = 2
    Output: [2,1,4,3,5]

    Example 2:
    Input: head = [1,2,3,4,5], k = 3
    Output: [3,2,1,4,5]
 
Follow-up: Can you solve the problem in O(1) extra memory space?
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        // Recursive Solution
        
        ListNode* temp = head;
        for(int i=0; i<k; i++)
        {
            if(temp == NULL)    // less than k nodes are left
                return head;
            
            temp = temp -> next;
        }
        
        // Reverse the nodes
        
        ListNode* curr = head;
        ListNode* prev = NULL;
        ListNode* fwd = NULL;
        
        for(int i=0; i<k; i++)
        {
            fwd = curr -> next;
            curr -> next = prev; 
            prev = curr;
            curr = fwd;
        }   
        // Now prev represents the head
        
        head -> next = reverseKGroup(curr, k);
        
        return prev;
    }
};

// Time : O(N)
// Space : O(N)