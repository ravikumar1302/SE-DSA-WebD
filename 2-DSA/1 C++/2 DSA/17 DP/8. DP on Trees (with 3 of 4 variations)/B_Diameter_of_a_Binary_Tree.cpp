/*
Diameter_of_a_Binary_Tree_GFG

The diameter of a tree (sometimes called the width) is the number of nodes on the longest path between two end nodes. The diagram below shows two trees each with diameter nine, the leaves that form the ends of the longest path are shaded (note that there is more than one path in each tree of length nine, but no path longer than nine nodes). 

Example 1:

Input:
       1
     /  \
    2    3
Output: 3

*/

/*Tree node structure  used in the program

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


class Solution {
  public:
    // Function to return the diameter of a Binary Tree.
    
    int solve(Node* root, int &res)
    {
        // Base case
        if(root == NULL)
            return 0;
        
        int l = solve(root->left, res);
        int r = solve(root->right, res);
        
        int temp = 1 + max(l,r);
        int ans = max(temp, 1+l+r);
        res = max(res, ans);
        
        return temp;
    }
    
    int diameter(Node* root) {
       
       int res = INT_MIN;
       solve(root, res);
       
       return res;
    }
};