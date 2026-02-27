/*
Find_K-th_smallest_Element_in_BST_Codestudio
Kth Smallest Element in a BST Leetcode_230

Given a binary search tree and an integer ‘K’. Your task is to find the ‘K-th’ smallest element in the given BST( binary search tree).
BST ( binary search tree) -
If all the smallest nodes on the left side and all the greater nodes on the right side of the node current node.


Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize? 
*/

/*************************************************************
 
    Following is the Binary Tree node structure

    class BinaryTreeNode 
    {
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

*************************************************************/

void inorder(BinaryTreeNode<int>* root, int k, vector<int> &ans)
{
    if(root == NULL)
        return;
    inorder(root->left, k, ans);
    ans.push_back(root-> data);
    inorder(root->right, k, ans);
}

int kthSmallest(BinaryTreeNode<int>* root, int k) {
    vector<int> ans;
    inorder(root, k,ans);
    if(k > ans.size())
        return -1;
    else
        return ans[k-1];
}
// T.C. : O(N)
// S.C. : O(N)


// Approach -2
// T.C. : O(N)
// Space : O(1), excluding recursicve call stack. Here no vector is used, so extra space will be used by recusrive calls only

int inorder(BinaryTreeNode<int>* root, int k, int &i)
{
    if(root == NULL)
        return -1;
    if(i == k)
        return i;
    // L
    int left = inorder(root->left, k, i);
    if(left != -1)
           return left;
    // N
    i++;
    if(i == k)
        return root ->data;
    // R
    return inorder(root->right, k, i);
}

int kthSmallest(BinaryTreeNode<int>* root, int k) {
    int i = 0;
    return inorder(root, k,i);
}