/*
Find_pairs_with_given_sum_in_doubly_linked_list_GFG

Given a sorted doubly linked list of positive distinct elements, the task is to find pairs in a doubly-linked list whose sum is equal to given value target.

    Example 1:

    Input :  1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9, target = 7
    Output: (1, 6), (2,5)
    Explanation: We can see that there are two pairs (1, 6) and (2,5) with sum 7.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)

*/


class Solution
{
public:
    vector<pair<int, int>> findPairsWithGivenSum(Node *head, int target)
    {
        vector<pair<int,int>>ans;
       
       Node* i=head;
       Node* temp=head;
       while(temp->next!=NULL)
           temp=temp->next;
           
       Node* j=temp;
       while(i->data<j->data)
       {
           if(i->data+j->data==target)
           {
               ans.push_back({i->data,j->data});
               i=i->next;
               j=j->prev;
           }
           else
           {
               if(i->data+j->data>target)
               {
                   j=j->prev;
               }
               else
               {
                   i=i->next;
               }
           }
       }
       return ans;
    }
};