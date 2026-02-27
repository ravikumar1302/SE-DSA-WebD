/*
Preorder_traversal_of_a_BST_Codestudio

You have been given an array/list 'PREORDER' representing the preorder traversal of a BST with 'N' nodes. All the elements in the given array have distinct values.
Your task is to construct a binary search tree that matches the given preorder traversal.
*/

/*
    Following is the class structure of BinaryTreeNode class for referance:

    class BinaryTreeNode {
       public : 
        T data;
        BinaryTreeNode<T> *left;
        BinaryTreeNode<T> *right;

        BinaryTreeNode(T data) {
            this -> data = data;
            left = NULL;
            right = NULL;
        }

        ~BinaryTreeNode() {
            if (left){
                delete left;
            }
            if (right){
                delete right;
            }
        }
    };
*/


// O(N^2) solution it is : will give TLE
BinaryTreeNode<int>* solve(BinaryTreeNode<int>* &root, int value)

{
    if(root == NULL)
    {
        root = new BinaryTreeNode<int>(value);
        return root;
    }
    if(root-> data > value)
        root -> left = solve(root->left, value);
    if(root-> data < value)
        root -> right = solve(root->right, value);
    
    return root;
}

BinaryTreeNode<int>* preorderToBST(vector<int> &preorder) {
    // Preorder : NLR
    BinaryTreeNode<int>* root = new BinaryTreeNode<int>(preorder[0]);
    
    int size = preorder.size();
    for(int i = 1; i<size; i++)
        solve(root, preorder[i]);

    return root;
}


// APPROACH -2  
// Time : O(N logN)
// We are provided with preorder, sort(N logN) it and get an inorder array. and then make a BT from inorder and preorder


// Approach -3
// Time : O(N)
BinaryTreeNode<int>* solve(vector<int> &preorder, int mini, int maxi, int &i)
{
    if(i >= preorder.size())
        return NULL;
    if(preorder[i] < mini || preorder[i] >maxi)
        return NULL;
    
    BinaryTreeNode<int>* root = new BinaryTreeNode<int>(preorder[i++]);
    root -> left = solve(preorder, mini, root -> data, i);
    root -> right = solve(preorder, root -> data, maxi, i);
    return root;
}

BinaryTreeNode<int>* preorderToBST(vector<int> &preorder) {
    // Preorder : NLR
    
    int mini = INT_MIN;
    int maxi = INT_MAX;
    int i = 0;
    return solve(preorder, mini, maxi, i); 
}