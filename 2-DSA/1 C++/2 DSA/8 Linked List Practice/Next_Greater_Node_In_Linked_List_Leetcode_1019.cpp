/*
Next_Greater_Node_In_Linked_List_Leetcode_1019

You are given the head of a linked list with n nodes.

For each node in the list, find the value of the next greater node. That is, for each node, find the value of the first node that is next to it and has a strictly larger value than it.

Return an integer array answer where answer[i] is the value of the next greater node of the ith node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.

 
Example 1:
Input: head = [2,1,5]
Output: [5,5,0]
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
    vector<int> nextLargerNodes(ListNode* head) {
        if(head == NULL)
            return {0};
        
        //Reverse the Linked list
        ListNode* curr = head;
        ListNode* prev = NULL;
        ListNode* fwd = NULL;
        while(curr != NULL)
        {
            fwd = curr -> next;
            curr -> next = prev;
            prev = curr;
            curr = fwd;
        } //prev is head now
        
        stack<int> s;
        vector<int> ans;
        while(prev != NULL)
        {
            if(s.empty())
            {
                ans.push_back(0);
                s.push(prev -> val);
                prev = prev -> next;
            }
            else if(s.top() > prev -> val)
            {
                ans.push_back(s.top());
                s.push(prev -> val);
                prev = prev -> next;
            }
            else
            {
                s.pop();
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
             
    }
};
