/*
Swapping_Nodes_in_a_Linked_List_Leetcode_1721

You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).

    Example 1:
    Input: head = [1,2,3,4,5], k = 2
    Output: [1,4,3,2,5]
   
    Example 2:
    Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
    Output: [7,9,6,6,8,7,3,0,9,5]
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
private:
    int getlen(ListNode* head)
    {
        if(head == NULL)
            return 0;
        int len = 0;
        while(head != NULL)
        {
            head = head -> next;
            len++;
        }
        return len;
    }
    
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* temp =  head;
        int Kend = getlen(head) + 1 - k;        
        
        int count =1;
        while(temp != NULL && count < k)
        {
            temp = temp -> next;
            count++;
        }
        ListNode* first = temp;
        int val1 = first -> val;
        
        count =1;
        temp = head;
        while(temp != NULL && count < Kend)
        {
            temp = temp -> next;
            count++;
        }
        ListNode* second = temp;
        int val2 = second-> val;
        
        first -> val = val2;
        second -> val = val1;
        
        return head;
    }
};

