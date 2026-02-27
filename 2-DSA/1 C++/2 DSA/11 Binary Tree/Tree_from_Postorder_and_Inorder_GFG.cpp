/*
Tree_from_Postorder_and_Inorder_GFG

Given inorder and postorder traversals of a Binary Tree in the arrays in[] and post[] respectively. The task is to construct the binary tree from these traversals.

 

Example 1:
Input : N = 8, 
in[] = 4 8 2 5 1 6 3 7
post[] =8 4 5 2 6 7 3 1
Output: 1 2 4 8 5 3 6 7
Explanation: For the given postorder and inorder traversal of tree the  resultant binary tree will be
           1
       /      \
     2         3
   /  \      /  \
  4    5    6    7
   \
     8

Expected Time Complexity: O(N2)
Expected Auxiliary Space: O(N)

*/

/* Tree node structure

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};*/

//Function to return a tree created from postorder and inoreder traversals.

void createMapping(int in[], map<int,int> &nodeToIndex, int n)
{
    for(int i=0; i<n; i++)
        nodeToIndex[in[i]] = i;
}

Node* solve(int in[], int post[], int &index, int inorderStart, int inorderEnd, int n, map<int,int> &nodeToIndex)
{
    if( index < 0 || inorderStart > inorderEnd)
        return NULL;
    
    //creating new node for root
    int element = post[index--];
    Node* root = new Node(element);
    
    //find element index in inorder
    int position = nodeToIndex[element];
    
    //Recursive calls (in case of post and inorder, we first build the right subtree)
    root -> right = solve(in, post, index, position +1, inorderEnd, n, nodeToIndex);
    root -> left = solve(in, post, index, inorderStart, position -1, n, nodeToIndex);
    
    return root;
}

Node *buildTree(int in[], int post[], int n) {
    int postorderIndex = n-1;
    
    map<int,int> nodeToIndex;
    createMapping(in, nodeToIndex, n); //T.C. : O (nlogN) as map insertion take logN time
    
    Node* ans = solve(in, post, postorderIndex, 0, n-1, n, nodeToIndex);  //T.C. : O (N) as we are traversing each element once
    
    return ans;
}
 //T.C. : O (NlogN)