/*
Two_Sum_IV_Input_is_a_BST_Codestudio

You have been given a Binary Search Tree and a target value. You need to find out whether there exists a pair of node values in the BST, such that their sum is equal to the target value.
A binary search tree (BST), also called an ordered or sorted binary tree, is a rooted binary tree whose internal nodes each store a value greater than all the values keys in the node's left subtree and less than those in its right subtree.
Follow Up:

Can you solve this in O(N) time, and O(H) space complexity?

*/

// Following is the Binary Tree node structure
/**************
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
    
};
***************/

void inorder(BinaryTreeNode<int>* root, vector<int> &ans)
{
    if(root == NULL)
        return;
    inorder(root->left, ans);
    ans.push_back(root-> data);
    inorder(root->right, ans);
}

bool twoSumInBST(BinaryTreeNode<int>* root, int target) {
	vector<int> ans;    // O(N) space
    inorder(root, ans);
    
    int s = 0;
    int e = ans.size()-1;
    while(s<e)
    {
        if(ans[s]+ans[e] == target)
            return true;
        else if(ans[s] +ans[e] > target)
            e--;
        else
            s++;
    }
    return false;
}
