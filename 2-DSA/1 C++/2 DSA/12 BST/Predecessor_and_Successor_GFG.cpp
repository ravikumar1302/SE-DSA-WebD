/*
Predecessor_and_Successor_GFG

There is BST given with root node with key part as an integer only. You need to find the in-order successor and predecessor of a given key. If either predecessor or successor is not found, then set it to NULL.

Input:
The first line of input contains an integer T denoting the number of test cases. Then T test cases follow. Each test case contains n denoting the number of edges of the BST. The next line contains the edges of the BST. The last line contains the key.

Output:
Find the predecessor and successor of the key in BST and sets pre and suc as predecessor and successor, respectively Otherwise, set to NULL.

    Example:
    Input:
    2
    6
    50 30 L 30 20 L 30 40 R 50 70 R 70 60 L 70 80 R
    65
    6
    50 30 L 30 20 L 30 40 R 50 70 R 70 60 L 70 80 R
    100

    Output:
    60 70
    80 -1
*/

/* BST Node
struct Node
{
	int key;
	struct Node *left, *right;
};
*/

// This function finds predecessor and successor of key in BST.
// It sets pre and suc as predecessor and successor respectively

Node* inpre(Node* root) //on left and then extreme right
{
    Node* p = root -> left;
    
    while( p->right )
        p = p->right;
    return p;
}

Node* insuc(Node* root) //on right and then extreme left
{
    Node* p = root -> right;
    
    while( p->left )
        p = p->left;
    return p;
}

void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
{

    if(root == NULL)
        return;
    
    if(root -> key == key)
    {
        if(root -> left) 
            pre = inpre(root);
        if(root -> right)
            suc = insuc(root);
        return;
    }
    
    if(key > root -> key)
    {
        pre = root;
        findPreSuc(root -> right, pre, suc, key);
    }
    if(key < root -> key)
    {
        suc = root;
        findPreSuc(root -> left, pre, suc, key);
    }
}

// T.C. : O(height)
// S.C. : O(1)