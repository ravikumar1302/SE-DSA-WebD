/*
Left_View_of_Binary_Tree_GFG

Given a Binary Tree, print Left view of it. Left view of a Binary Tree is set of nodes visible when tree is visited from Left side. The task is to complete the function leftView(), which accepts root of the tree as argument.

Left view of following tree is 1 2 4 8.

          1
       /     \
     2        3
   /     \    /    \
  4     5   6    7
   \
     8   

Example 1:

Input:
   1
 /  \
3    2
Output: 1 3

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(N).
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

//Function to return a list containing elements of left view of the binary tree.

void solve(Node* root, vector<int> &ans, int lvl)
{
    if(root == NULL)    //Base case
        return ;
    
    //We entered a new level
    if(lvl == ans.size())
        ans.push_back(root -> data);
    
    solve(root -> left, ans, lvl +1);
    solve(root -> right,ans, lvl +1);
}

vector<int> leftView(Node *root)
{
   vector<int> ans;
   solve(root, ans, 0);
   return ans;
}