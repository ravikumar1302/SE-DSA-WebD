/*
Merge_In_Between_Linked_Lists_Leetcode_1669

You are given two linked lists: list1 and list2 of sizes n and m respectively.

Remove list1's nodes from the ath node to the bth node, and put list2 in their place.

The blue edges and nodes in the following figure indicate the result:


Build the result list and return its head.


    Example 1:
    Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
    Output: [0,1,2,1000000,1000001,1000002,5]
    Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges and nodes in the above figure indicate the result.
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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        
        // Point temp1 (a-1) node to l2
        ListNode* temp = list1;
        int count = 1;
        while(temp != NULL && count < a )
        {
            temp = temp -> next;
            count++;
        }
        
        ListNode* delStart = temp -> next;
        temp -> next = list2;
            
        //traverse through l1 till del_end
        while(delStart != NULL && count < b)
        {
            delStart = delStart -> next;
            count++;
        }
            
        // point temp2 to delend ->next and del_end -> next = NULL
        ListNode* temp2 = delStart -> next;
        delStart -> next = NULL;
            
        //traverse through l2 and point last node to temp2
        while(temp != NULL && temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = temp2;
            
        //return ans
        return list1;
    }
};

