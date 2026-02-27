/*
Remove_Duplicates_from_Sorted_List_II_Leetcode_82

Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. 
Return the linked list sorted as well.

    Example 1:
    Input: head = [1,2,3,3,4,4,5]
    Output: [1,2,5]

    Example 2:
    Input: head = [1,1,1,2,3]
    Output: [2,3] 

Constraints:
    The number of nodes in the list is in the range [0, 300].
    -100 <= Node.val <= 100
    The list is guaranteed to be sorted in ascending order.
*/


/*
    first make a dummy node and assign its value equals to 0 and its next points to the head of the given linked list, also make a prev node and point it to the dummy node.
    Always remember that a prev node is always required wherever we have to delete a node or we have to break links and create new links . this thing is very important for beginner coders for developing their intusions in future. That's not a rule i have said it on the basis of my coding expirience.
    Then you have to traverse the linked list so run a while loop.
    check that if the two adjacent nodes are equal or not if the two adjacent nodes are equal then traverse trhe linked list upto ehen the adjacent nodes are not identical.
    Then directly connect the link from prev->next to the head->next.
    While in other case is the adjacent nodes are not equal then simply traverse the linked list by prev=prev->next.
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
    ListNode* deleteDuplicates(ListNode* head) {
        
        ListNode *dummy=new ListNode(0,head);
        ListNode *prev=dummy;
        
        while(head!=NULL)
        {
            if(head->next!=NULL && head->val==head->next->val)
            {

                while(head->next!=NULL && head->val==head->next->val)
                    head=head->next;

                prev->next = head->next;
             }

            else 
                prev = prev->next;


            head = head->next;
        }
        
        return dummy->next;
    }
};