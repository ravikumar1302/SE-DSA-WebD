/*
Construct_Tree_from_Inorder_&_Preorder_GFG
Construct Binary Tree from Preorder and Inorder Traversal Leetcode_105

Given 2 Arrays of Inorder and preorder traversal. Construct a tree and print the Postorder traversal. 

    Example 1:

    Input:
    N = 4
    inorder[] = {1 6 8 7}
    preorder[] = {1 6 7 8}
    Output: 8 7 6 1

Expected Time Complexity: O(N*N).
Expected Auxiliary Space: O(N)
*/

/*Complete the code here.
Node is as follows:
struct Node
{
  int data;
  Node* left;
  Node* right;
};
*/
class Solution{
    public:
    int findPos(int in[], int element, int n)
    {
        for(int i = 0; i < n; i++)
            if(in[i] == element)
                return i;
        
        return -1;
    }
    
    Node* solve(int in[], int pre[], int &index, int inorderStart, int inorderEnd, int n )
    {
        if(index >= n || inorderStart > inorderEnd)
            return NULL;
        
        int element = pre[index++];
        Node* root = new Node(element);
        int position = findPos(in, element, n);
        
        //Recursive calls
        root -> left = solve(in, pre, index, inorderStart, position -1, n);
        root -> right = solve(in, pre, index, position +1, inorderEnd, n);
        
        return root;
    }
    
    Node* buildTree(int in[],int pre[], int n)
    {
        int preOrderIndex = 0;
        Node* ans = solve(in, pre, preOrderIndex, 0, n-1 , n);
        return ans;
    }
};


// APPROACH -2 : using map

class Solution{
    public:
    void create(int in[], map<int,int> &nodeToIndex, int n)
    {
        for(int i = 0; i < n; i++)
            nodeToIndex[in[i]] = i;
    }
    
    Node* solve(int in[], int pre[], int &index, int inorderStart, int inorderEnd, int n, map<int,int> &nodeToIndex )
    {
        if(index >= n || inorderStart > inorderEnd)
            return NULL;
        
        //creating root node for element
        int element = pre[index++];
        Node* root = new Node(element);
        
        //find element's index in inorder
        int position = nodeToIndex[element];
        
        //Recursive calls
        root -> left = solve(in, pre, index, inorderStart, position -1, n, nodeToIndex);
        root -> right = solve(in, pre, index, position +1, inorderEnd, n, nodeToIndex);
        
        return root;
    }
    
    Node* buildTree(int in[],int pre[], int n)
    {
        int preOrderIndex = 0;
        map<int,int> nodeToIndex;
        
        //creating mapping
        create(in, nodeToIndex, n);
        Node* ans = solve(in, pre, preOrderIndex, 0, n-1 , n, nodeToIndex);
        return ans;
    }
};