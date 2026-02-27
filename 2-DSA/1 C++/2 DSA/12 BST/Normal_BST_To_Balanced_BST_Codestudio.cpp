/*
Normal_BST_To_Balanced_BST_Codestudio

You have been given a binary search tree of integers with ‘N’ nodes. Your task is to convert it into a balanced BST with the minimum height possible.

A binary search tree (BST) is a binary tree data structure that has the following properties.
    • The left subtree of a node contains only nodes with data less than the node’s data.
    • The right subtree of a node contains only nodes with data greater than the node’s data.
    • Both the left and right subtrees must also be binary search trees.

A Balanced BST is defined as a BST, in which the height of two subtrees of every node differs no more than 1.
*/

/*************************************************************
    Following is the Binary Serach Tree node structure

    template <typename T>
    class TreeNode
    {
    public :
        T data;
        TreeNode<T> *left;
        TreeNode<T> *right;

        TreeNode(T data) {
            this -> data = data;
            left = NULL;
            right = NULL;
        }

        ~TreeNode() {
            if (left)
                delete left;
            if (right)
                delete right;
        }
    };

*************************************************************/
void inorder(TreeNode<int>* root, vector<int> &values)
{
    if(root == NULL)
        return;
    inorder(root->left, values);
    values.push_back(root -> data);
    inorder(root->right, values);
}

TreeNode<int>* buildtree (int s, int e, vector<int> &values)
{
    //Base case
    if(s>e)
        return NULL;
    
    int mid = (s+e)/2;
    TreeNode<int>* root = new TreeNode<int>(values[mid]);
    root -> left = buildtree(s, mid-1, values);
    root -> right = buildtree(mid+1, e, values);
    
    return root;
}
TreeNode<int>* balancedBst(TreeNode<int>* root) {
    
    vector<int> values;
    
    inorder(root, values);    // O(N) time and space

    return buildtree(0, values.size()-1, values);
}
