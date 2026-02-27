/*
Flatten_BST_To_A_Sorted_List_Codestudio

You have been given a Binary Search Tree (BST). Your task is to flatten the given BST to a sorted list. More formally, you have to make a right-skewed BST from the given BST, i.e., the left child of all the nodes must be NULL, and the value at the right child must be greater than the current node.
A binary search tree (BST), also called an ordered or sorted binary tree, is a rooted binary tree whose internal nodes each store a value greater than all the values in the node's left subtree and less than those in its right subtree.
Follow Up :
Can you solve this in O(N) time and O(H)  space complexity?

*/

/************************************************************

    Following is the Binary Tree node structure
    
    template <typename T>
    class TreeNode {
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
            if(left)
                delete left;
            if(right)
                delete right;
        }
    };

************************************************************/
void inorder(TreeNode<int>* root, vector<int> &values)
{
    if(root == NULL)
        return;
    inorder(root->left, values);
    values.push_back(root -> data);
    inorder(root->right, values);
}

TreeNode<int>* flatten(TreeNode<int>* root)
{
    vector<int> values;
    
    inorder(root, values);    // O(N) time and O(N) space
    int size = values.size();
    
    TreeNode<int>* newRoot = new TreeNode<int>(values[0]);
    TreeNode<int>* curr = newRoot;
    
    for(int i = 1; i<size ; i++)
    {
        TreeNode<int>* temp = new TreeNode<int>(values[i]);
        
        curr -> left = NULL;
        curr -> right = temp;
        curr = temp;
    }
    
    curr ->left = NULL;
    curr -> right = NULL;
    
    return newRoot;

}
