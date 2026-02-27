/*
Maximum_Twin_Sum_of_a_Linked_List_Leetcode_2130

In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.

For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. These are the only nodes with twins for n = 4.
The twin sum is defined as the sum of a node and its twin.

Given the head of a linked list with even length, return the maximum twin sum of the linked list.

    Example 1:
    Input: head = [5,4,2,1]
    Output: 6
    Explanation : Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
    There are no other nodes with twins in the linked list. Thus, the maximum twin sum of the linked list is 6. 
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
    int pairSum(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        int maxVal = 0;
        
        //Get mid
        while(fast != NULL && fast -> next != NULL)
        {
            slow = slow -> next;
            fast = fast -> next -> next;
        } // slow is our middle
        
        // Reverse second part of linked list
        ListNode *nextNode, *prev = NULL;
        while (slow) {
            nextNode = slow->next;
            slow->next = prev;
            prev = slow;
            slow = nextNode;
        }

        // Get max sum of pairs
        while(prev)
        {
            maxVal = max(maxVal, head -> val + prev -> val);
            prev = prev -> next;
            head = head -> next;
        }

        return maxVal;
    }
};


/* Leetcode 3 approaches solution

Approach 1 : Naive Approach , Using Vector, uses extra space
Time Complexity : O(N) , Space Complexity : O(N)

int pairSum(ListNode* head) {
        
        Approach 1 : But using extra space
        vector<int> vec;
        
        ListNode *curr = head;
        
        while(curr)
        {
            vec.push_back(curr->val);
            curr = curr->next;
        }
        int i=0,j=vec.size()-1;
        
        int maxVal = 0 ;
        
        while(i<j)
            maxVal = max(maxVal , vec[i++] + vec[j--]);            
        
        return maxVal;
}

Approach 2 : Using Two Pointer Approach and then reversing the second half of the linked list
Time Complexity : O(N) , Space Complexity : O(1)

void reverseLL(ListNode **head) {
        ListNode *curr = *head;
        ListNode *prevNode = NULL;
        ListNode *nextNode;
        
        while(curr) {
            nextNode = curr->next;
            curr->next = prevNode;
            prevNode = curr;
            curr = nextNode;
        }
        
        *head = prevNode;
        
    }
	
int pairSum(ListNode* head) 
{
	
	 ListNode *slow = head;
        ListNode *fast = head;
        
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        slow = slow->next;
        
        reverseLL(&slow);
        int maxVal = 0;
        while(slow) {
            maxVal = max(maxVal,head->val + slow->val);
            slow = slow->next;
            head = head->next;
        }
        
        return maxVal;
}

Approach 3 : Using Stack,
Time Complexity : O(N) , Space Complexity : O(N)

int pairSum(ListNode* head) {
stack<int> st;
        
        ListNode *curr = head;
        
        while(curr) {
            st.push(curr->val);
            curr = curr->next;
        }
        
        int maxTwinVal = 0;
        int size = st.size();
        int count = 1;
        while(count++ <= size/2) {
            maxTwinVal = max(maxTwinVal , st.top() + head->val);
            st.pop();
            head = head->next;
        }
        
        return maxTwinVal;
}

*/