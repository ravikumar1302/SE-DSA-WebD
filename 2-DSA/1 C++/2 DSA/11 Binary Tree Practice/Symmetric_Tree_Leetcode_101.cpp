/*
Symmetric_Tree_Leetcode_101
Symmetric Tree_GFG

Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

    Example 1:
    Input: root = [1,2,2,3,4,4,3]
    Output: true

    Example 2:
    Input: root = [1,2,2,null,3,null,3]
    Output: false

Follow up: Could you solve it both recursively and iteratively?

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(Height of the Tree).
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool solve(TreeNode* l, TreeNode* r)
    {
        if(l == NULL && r == NULL)
            return true;
        if(l == NULL && r != NULL)
            return false;
        if(l != NULL && r == NULL)
            return false;
        
        if(l-> val != r-> val)
            return false;
        
        return solve(l-> left, r-> right) && solve(l->right, r -> left);
    }
    
    bool isSymmetric(TreeNode* root) {
        
        // if(root == NULL) return true;        // This Condition is necessary for GFG test cases to pass

        return solve(root -> left, root -> right);
    }
};