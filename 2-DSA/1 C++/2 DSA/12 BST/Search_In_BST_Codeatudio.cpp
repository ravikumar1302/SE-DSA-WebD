/*
Search_In_BST_Codeatudio

There is a Binary Search Tree (BST) consisting of ‘N’ nodes. Each node of this BST has some integer data.
You are given a pointer to the root node of this BST, and an integer ‘X’. Print "True" if there is a node in BST having data equals to ‘X’, otherwise print "False".
A binary search tree (BST) is a binary tree data structure that has the following properties.

    Example:

    4
    2 6
    1 3 5 7
    -1 -1 -1 -1 -1 -1 -1 -1
    Explanation :
    Level 1 :
    The root node of the tree is 4

    Level 2 :
    Left child of 4 = 2
    Right child of 4 = 6

    Level 3 :
    Left child of 2 = 1
    Right child of 2 = 3
    Left child of 6 = 5
    Right child of 6 = 7

    Level 4 :
    Left child of 1 = null (-1)
    Right child of 1 = null (-1)
    Left child of 3 = null (-1)
    Right child of 3 = null (-1)
    Left child of 5 = null (-1)
    Right child of 5 = null (-1)
    Left child of 7 = null (-1)
    Right child of 7 = null (-1)

    The first not-null node (of the previous level) is treated as the parent of the first two nodes of the current level. The second not-null node (of the previous level) is treated as the parent node for the next two nodes of the current level and so on.

    The input ends when all nodes at the last level are null (-1).
*/

/*
    Following is the Binary Tree node structure:

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
*/

bool searchInBST(BinaryTreeNode<int> *root, int x) {
    //Base case
    if(root == NULL)
        return false;
    
    if(root -> data == x)
        return true;
    
    if( root -> data < x )
        searchInBST(root -> right, x);
    else
        searchInBST(root -> left, x);

}


// ITREATIVE method
bool searchInBST(BinaryTreeNode<int> *root, int x) {

    BinaryTreeNode<int> *temp = root;
    
    while(temp != NULL)
    {
        if(temp -> data == x)
            return true;
        if(temp -> data > x)
            temp = temp -> left;
        else
            temp = temp -> right;
    }
    
    return false;
}