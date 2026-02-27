/*
Check_for_Balanced_Tree_GFG
Balanced Binary Tree Leetcode_110

Given a binary tree, find if it is height balanced or not. 
A tree is height balanced if difference between heights of left and right subtrees is not more than one for all nodes of tree. 

    A height balanced tree
            1
        /     \
    10      39
    /
    5

    An unbalanced tree
            1
        /    
    10   
    /
    5

    Example 1:

    Input:
        1
        /
    2
        \
        3 
    Output: 0
    Explanation: The max difference in height of left subtree and right subtree is 2, which is greater than 1. Hence unbalanced

*/

/*A binary tree node structure

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

class Solution{
    private:
    int height(Node* root)
    {
        if(root == NULL)
            return 0;
            
        int l = height(root -> left);
        int r = height(root -> right);
        return max(l,r) + 1;
    }
    
    public:
    //Function to check whether a binary tree is balanced or not.
    bool isBalanced(Node *root)
    {
        if(root == NULL)
            return true;
        bool left = isBalanced(root -> left);
        bool right = isBalanced(root -> right);
        
        bool diff = abs( height(root -> left) - height(root -> right) ) <= 1;
        
        if(left && right && diff)
            return true;
        else
            return false;
    }
        
    };
//Brute force approach : O(N^2)


//Optimized Approach : O(N) below:
class Solution{
    public:
        pair<bool, int> balanced(Node* root)
    {
        if(root == NULL)
        {
            pair<bool, int> p = make_pair(true,0);
            return p;
        }
        
        pair<bool, int> left = balanced(root -> left);
        pair<bool, int> right = balanced(root -> right);
        
        bool leftans = left.first;
        bool rightans = right.first;
        
        bool diff = abs(left.second - right.second) <= 1;
        
        pair<bool, int> ans;
        ans.second = max(left.second, right.second) + 1;
        
        if(leftans && rightans && diff)
            ans.first = true;
        else
            ans.first = false;
            
        return ans;
    }
    
    //Function to check whether a binary tree is balanced or not.
    bool isBalanced(Node *root)
    {
        return balanced(root).first;
    }
};
// O(N) solution