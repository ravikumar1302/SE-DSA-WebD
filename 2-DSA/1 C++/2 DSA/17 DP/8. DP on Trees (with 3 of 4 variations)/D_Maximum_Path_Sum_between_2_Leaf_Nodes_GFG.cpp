/*
Maximum_Path_Sum_between_2_Leaf_Nodes_GFG

Given a binary tree in which each node element contains a number. Find the maximum possible path sum from one leaf node to another leaf node.

Note: Here Leaf node is a node which is connected to exactly one different node.

Example 2:
Input:    
            -15                               
         /      \                          
        5         6                      
      /  \       / \
    -8    1     3   9
   /  \              \
  2   -3              0
                     / \
                    4  -1
                       /
                     10  
Output:  27
Explanation : The maximum possible sum from one leaf node to another is (3 + 6 + 9 + 0 + -1 + 10 = 27)

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(Height of Tree)
*/


/*
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

class Solution {
public:
    
    int solve(Node* root, int &res)
    {
        // Base case
        if(root == NULL)
            return 0;
            
        if(root->left == NULL && root->right == NULL)
            return root->data;
            
        // Hypothesis
        int l = solve(root->left, res);
        int r = solve(root->right, res);
        
        // Induction
        if(root->left == NULL)
            return (r + root->data);
        if(root->right == NULL)
            return (l + root->data);
            
        int temp = max(l,r) + root->data;
        int ans = l+r+root->data;
        res = max(res, ans);
        
        // return
        return temp;
    }
    
    int maxPathSum(Node* root)
    {
        int res = INT_MIN;
        
        int x = solve(root, res);
        if(root->left == NULL || root->right == NULL)
            return max (res, x);
        return res;
    }
};