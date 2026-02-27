/*
Lowest_Common_Ancestor_in_a_Binary_Tree_GFG

Given a Binary Tree with all unique values and two nodes value, n1 and n2. The task is to find the lowest common ancestor of the given two nodes. We may assume that either both n1 and n2 are present in the tree or none of them are present.

Example 1:

Input : n1 = 2 , n2 = 3  
       1 
      / \ 
     2   3
Output: 1
Explanation : LCA of 2 and 3 is 1.

Expected Time Complexity:O(N).
Expected Auxiliary Space:O(Height of Tree).

*/

/* A binary tree node

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};
 */

class Solution
{
    public:
    //Function to return the lowest common ancestor in a Binary Tree.
    Node* lca(Node* root ,int n1 ,int n2 )
    {
        if(root == NULL)
            return NULL;
        if(root -> data == n1 || root -> data == n2)
            return root;
        
        Node* leftans = lca(root -> left, n1, n2);
        Node* rightans = lca(root -> right, n1, n2);
        
        if(leftans != NULL && rightans != NULL)
            return root;
        else if(leftans != NULL && rightans == NULL)
            return leftans;
        else if(leftans == NULL && rightans != NULL)
            return  rightans;
        else 
            return NULL;
    }
};