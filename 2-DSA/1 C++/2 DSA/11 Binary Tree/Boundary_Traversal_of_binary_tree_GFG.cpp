/*
Boundary_Traversal_of_binary_tree_GFG

Given a Binary Tree, find its Boundary Traversal. The traversal should be in the following order: 

Left boundary nodes: defined as the path from the root to the left-most node ie- the leaf node you could reach when you always travel preferring the left subtree over the right subtree. 
Leaf nodes: All the leaf nodes except for the ones that are part of left or right boundary.
Reverse right boundary nodes: defined as the path from the right-most node to the root. The right-most node is the leaf node you could reach when you always travel preferring the right subtree over the left subtree. Exclude the root from this as it was already included in the traversal of left boundary nodes.
Note: If the root doesn't have a left subtree or right subtree, then the root itself is the left or right boundary. 

Example 1:

Input:
        1 
      /   \
     2     3  
    / \   / \ 
   4   5 6   7
      / \
     8   9
   
Output: 1 2 4 8 9 6 7 3

Expected Time Complexity: O(N). 
Expected Auxiliary Space: O(Height of the Tree).
*/

class Solution {
public:
    void leftBoundary(Node* root, vector<int> &ans )
    {
        if( (root == NULL) || (root -> left == NULL && root -> right == NULL) )   
            return;  //base case & leaf node case

        ans.push_back(root -> data);
        if(root -> left)
            leftBoundary(root -> left, ans);
        else
            leftBoundary(root -> right, ans);
        
    }
    
    void leaves(Node* root, vector<int> &ans )
    {
        if(root == NULL)
            return ;
        
        if(root -> left == NULL && root -> right == NULL)   //leaf node case
            {
                ans.push_back(root -> data);
                return; 
            }
        
        leaves(root -> left, ans);
        leaves(root -> right, ans);
    }   
    
    void rightBoundary(Node* root, vector<int> &ans )
    {
        if( (root == NULL) || (root -> left == NULL && root -> right == NULL) )   
            return;  //base case & leaf node case
        
        
        if(root -> right)
            rightBoundary(root -> right, ans);
        else
            rightBoundary(root -> left, ans);
        
        ans.push_back(root -> data);    // Bcz on right side, data will enter while going back, so this line is written after if else
        
    }
    

    
    vector <int> boundary(Node *root)
    {
        vector<int> ans;
        if(root == NULL)
            return ans;
        ans.push_back(root -> data);
        
        //Left part traverse
        leftBoundary(root -> left, ans);
        
        //traverse tree nodes
        leaves(root -> left, ans);
        leaves(root -> right,ans);
        
        //right part traverse
        rightBoundary(root -> right, ans);
        
        return ans;
    }
};