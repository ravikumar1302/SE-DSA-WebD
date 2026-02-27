/*
Right_View_of_Binary_Tree_GFG
Binary Tree Right Side View Leetcode_199

Given a Binary Tree, find Right view of it. Right view of a Binary Tree is set of nodes visible when tree is viewed from right side.

Right view of following tree is 1 3 7 8.

          1
       /     \
     2        3
   /   \      /    \
  4     5   6    7
    \
     8

Example 1:

Input:
       1
    /    \
   3      2
Output: 1 2

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(Height of the Tree).

*/

/* A binary tree node has data, pointer to left child
   and a pointer to right child 
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
}; */

// Should return  right view of tree

class Solution
{
    public:
    //Function to return list containing elements of right view of binary tree.
    
    void solve(Node* root, vector<int> &ans, int lvl)
    {
        if(root == NULL)
            return;
        
        if(lvl == ans.size())
            ans.push_back(root -> data);
        
        solve(root -> right, ans, lvl +1);
        solve(root -> left, ans, lvl +1);
    }
    
    vector<int> rightView(Node *root)
    {
       vector<int> ans;
       solve(root, ans, 0);
       return ans;
    }
};