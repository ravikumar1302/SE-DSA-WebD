/*
Flatten_binary_tree_to_linked_list_GFG

Given a binary tree, flatten it into linked list in-place. Usage of auxiliary data structure is not allowed. After flattening, left of each node should point to NULL and right should contain next node in preorder.

Example 1
Input  
          1
        /   \
       2     5
      / \     \
     3   4     6
Output :
1 2 3 4 5 6 
Explanation: After flattening, the tree looks like this
    1
     \
      2
       \
        3
         \
          4
           \
            5
             \
              6 
Here, left of each node points to NULL and right contains the next node in preorder.The inorder traversal of this flattened tree  is 1 2 3 4 5 6.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)

*/

class Solution
{
    public:
    void flatten(Node *root)
    {
        Node* curr = root;
        while(curr != NULL)
        {
            
            if(curr -> left)
            {
                Node* pred = curr -> left;
                while(pred -> right)
                    pred = pred -> right;
                
                pred -> right = curr -> right;
                curr -> right = curr -> left;
                curr -> left = NULL; //either use this or the below part
            }
            
            curr = curr -> right;
        }
        /*
        //left part NULL
        curr = root;
        while(curr != NULL)
        {
            curr -> left = NULL;
            curr = curr -> right;
        }*/
    }
};