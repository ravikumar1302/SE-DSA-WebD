/*
Rotate_doubly_Linked_List_GFG

Given a doubly linked list, rotate the linked list counter-clockwise by P nodes. Here P is a given positive integer and is smaller than the count of nodes(N) in a linked list.

    Example 1:
    Input: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6 , P = 2
    Output: 3 <-> 4 <-> 5 <-> 6 <-> 1 <-> 2
    Explanation: Doubly linked list after rotating 2 nodes is: 3 4 5 6 1 2.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)

*/

/
typedef struct node
{
  int data;
  struct node*next,*prev;
  
  node(int x){
      data = x;
      next = NULL;
      prev = NULL;
  }
  
} Node;
*/

class Solution {
public:
    Node *rotateDLL(Node *start,int p)
    {
        Node* last = start;
        while(last -> next != NULL)
            last = last -> next;
        
        while(p)    {
            //connecting last and first node
            last -> next = start;
            start -> prev = last;
            
            Node* temp = start -> next;
            
            //breaking connections of first node
            start -> next -> prev = NULL;
            start -> next = NULL;
            
            //changing pointers
            last = start;
            start = temp;
            
            
            p--;
        }
        
    }
};