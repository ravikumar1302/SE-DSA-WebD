/*
Convert_Binary_Number_in_a_Linked_List_to_Integer_Leetcode_1290

Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1. The linked list holds the binary representation of a number.

Return the decimal value of the number in the linked list.

    Example 1:
    Input: head = [1,0,1]
    Output: 5
    Explanation: (101) in base 2 = (5) in base 10
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
    int getDecimalValue(ListNode* head) {
        
        // Approach: store value in array, and find decimal no (Space : O(N))
        vector<int> ans;
        while(head != NULL)
        {
            ans.push_back(head -> val);
            head = head -> next;
        }
        
        //Now we have array of the binary number
        
        int size = ans.size();
        int rem = 0;
        int dec = 0;
        int k = 0;
        for(int i=size-1; i>=0; i--)
        {
            dec = dec + ans[i]*pow(2,k);
            k++;
        }
        return dec;
    }
};