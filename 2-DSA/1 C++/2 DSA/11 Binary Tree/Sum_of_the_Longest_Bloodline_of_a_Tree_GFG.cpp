/*
Sum of the Longest Bloodline of a Tree (Sum of nodes on the longest path from root to leaf node)

Given a binary tree of size N. Your task is to complete the function sumOfLongRootToLeafPath(), that find the sum of all nodes on the longest path from root to leaf node.
If two or more paths compete for the longest path, then the path having maximum sum of nodes is being considered.

Example 1:

Input: 
        4        
       / \       
      2   5      
     / \ / \     
    7  1 2  3    
      /
     6
Output: 13
Explanation:
        4        
       / \       
      2   5      
     / \ / \     
    7  1 2  3 
      /
     6

The highlighted nodes (4, 2, 1, 6) above are part of the longest root to leaf path having sum = (4 + 2 + 1 + 6) = 13

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(N)
*/

/*
structure of the node of the binary tree is as
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
};
*/

class Solution
{
public:
    void solve(Node* root, int sum, int &maxsum, int len, int &maxlen)
    {
        if(root == NULL)
            {
                if(len > maxlen)
                {
                    maxlen = len;
                    maxsum = sum;
                }
                else if(len == maxlen)
                    maxsum = max(sum, maxsum);
                return;
            }
        sum = sum + root -> data;
        solve(root -> left, sum, maxsum, len + 1, maxlen);
        solve(root -> right, sum, maxsum, len + 1, maxlen);
    }
    
    int sumOfLongRootToLeafPath(Node *root)
    {
        int len = 0;
        int maxlen = 0;
        int sum = 0;
        int maxsum = INT_MIN;
        
        solve(root, sum, maxsum, len, maxlen);
        
        return maxsum;
    }
};