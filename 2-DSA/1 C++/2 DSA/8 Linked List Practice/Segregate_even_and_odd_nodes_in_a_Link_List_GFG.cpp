/*
Segregate_even_and_odd_nodes_in_a_Link_List_GFG

Given a link list of size N, modify the list such that all the even numbers appear before all the odd numbers in the modified list. The order of appearance of numbers within each segregation should be same as that in the original list.

NOTE: Don't create a new linked list, instead rearrange the provided one.

    Example 1:
    Input : N = 7, Link List : 17 -> 15 -> 8 -> 9 -> 2 -> 4 -> 6 -> NULL
    Output: 8 2 4 6 17 15 9
    Explaination: 8,2,4,6 are the even numbers so they appear first and 17,15,9 are odd numbers that appear later.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)
*/

/*
struct Node
{
    int data;
    struct Node* next;
    
    Node(int x){
        data = x;
        next = NULL;
    }
};
*/
class Solution{
public:
    Node* divide(int N, Node *head){

        Node* even_head=NULL;
        Node* temp=head;
        Node* new_head=head;
        Node* prev=head;
        
        if(!head || !head->next)
            return head;
            
        if(head->data%2==0)
            even_head=head;
        
        while(temp->next)
        {
            if(temp->next->data%2==0 && temp->data%2!=0)    // even
            {
                Node* store=temp->next;
                temp->next=temp->next->next;
                
                if(!even_head)  // if evenhead is null
                {
                    store->next=head;
                    even_head=store;
                    new_head=store;
                }
                else
                {
                    store->next=even_head->next;
                    even_head->next=store;
                    even_head=store;
                }
            }
            
            else    // odd
            {  
                if(temp->data%2==0)
                    even_head=temp;
                    
                temp=temp->next;
            }
        } // while loop ends here
        
        return new_head;
    }
};