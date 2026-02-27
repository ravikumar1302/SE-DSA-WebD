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


// Approach-1 : T.C. : O(N^2),  as diameter function is calling height function
class Solution {
    int height(Node* root)
    {
        if(root == NULL)
            return 0;
            
        int l = height(root -> left);
        int r = height(root -> right);
        return max(l,r) + 1;
    }
  public:
    // Function to return the diameter of a Binary Tree.
    int diameter(Node* root) {
        if(root == NULL)
            return 0;
        int ld = diameter(root -> left);
        int rd = diameter(root -> right);
        int ans = height(root -> left) + height(root -> right) + 1;
        return max(ld, max(rd, ans));
    }
};


// Approach-2 : Time : O(N) Approach
pair<int,int> diameterFast(Node* root) {
    
    //base case
    if(root == NULL) {
        pair<int,int> p = make_pair(0,0);
        return p;
    }
    
    pair<int,int> left = diameterFast(root->left);
    pair<int,int> right = diameterFast(root->right);
    
    int op1 = left.first;
    int op2 = right.first;
    int op3 = left.second + right.second + 1;
    
    pair<int,int> ans;
    ans.first = max(op1, max(op2, op3));;
    ans.second = max(left.second , right.second) + 1;

    return ans;
}
int diameter(Node* root) {
    
    return diameterFast(root).first;
}