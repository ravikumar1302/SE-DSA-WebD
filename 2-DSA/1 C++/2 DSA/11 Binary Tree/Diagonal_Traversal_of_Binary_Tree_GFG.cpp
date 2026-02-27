/*
Diagonal_Traversal_of_Binary_Tree_GFG

Given a Binary Tree, print the diagonal traversal of the binary tree.

Consider lines of slope -1 passing between nodes. Given a Binary Tree, print all diagonal elements in a binary tree belonging to same line.

Example 1:

Input :
            8
         /     \
        3      10
      /   \      \
     1     6     14
         /   \   /
        4     7 13
Output : 8 10 14 3 6 7 13 1 4

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(N).

*/

/* A binary tree node
struct Node
{
    int data;
    Node* left, * right;
}; */


vector<int> diagonal(Node *root)
{
   vector<int> ans;
   if(root == NULL)
        return ans;
    queue<Node*> q;
    q.push(root);
    
    while(!q.empty())
    {
        Node* temp = q.front();
        q.pop();
        
        while(temp) //will leave this loop when temp is null
        {
            if(temp -> left)
                q.push(temp -> left);
            ans.push_back(temp -> data);
            temp = temp -> right;
        }
    }
    return ans;
}

// T.C. : O(N)
// S.C. : O(N)