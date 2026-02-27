/*
Predecessor_And_Successor_In_BST_Codestudio

You have been given a binary search tree of integers with ‘N’ nodes. You are also given 'KEY' which represents data of a node of this tree. Your task is to find the predecessor and successor of the given node in the BST.
*/

/*************************************************************

    Following is the Binary Tree node structure

    template <typename T>

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

        ~BinaryTreeNode() {
            if (left)
            {
                delete left;
            }
            if (right)
            {
                delete right;
            }
        }
    };

*************************************************************/
int inpre(BinaryTreeNode<int>* root) //on left and then extreme right
{
    BinaryTreeNode<int>* p = root -> left;
    
    while( p->right )
        p = p->right;
    return p -> data;
}

int insuc(BinaryTreeNode<int>* root) //on right and then extreme left
{
    BinaryTreeNode<int>* p = root -> right;
    
    while( p->left )
        p = p->left;
    return p -> data;
}

void findPreSuc(BinaryTreeNode<int>* root, int& pre, int& suc, int key)
{

    if(root == NULL)
        return;
    
    if(root -> data == key)
    {
        if(root -> left) 
            pre = inpre(root);
        if(root -> right)
            suc = insuc(root);
        return;
    }
    
    if(key > root -> data)
    {
        pre = root-> data;
        findPreSuc(root -> right, pre, suc, key);
    }
    if(key < root -> data)
    {
        suc = root-> data;
        findPreSuc(root -> left, pre, suc, key);
    }
}
pair<int,int> predecessorSuccessor(BinaryTreeNode<int>* root, int key)
{
    int a = -1;
    int b = -1;
    findPreSuc(root, a, b, key);
    return make_pair(a, b);
}

/***********************************************************************************************************************/
// Itrative solution : but it has runtime error

pair<int,int> predecessorSuccessor(BinaryTreeNode<int>* root, int key)
{
    BinaryTreeNode<int>* temp = root;
    int pred = -1;
    int succ = -1;
    
    while(temp -> data != key)
    {
        if(temp-> data > key)
        {
            succ = temp -> data;
            temp = temp -> left;
        }
        else
        {
            pred = temp -> data;
            temp = temp -> left;
        }
    }
    
    // pred ans succ
    // pred
    BinaryTreeNode<int>* leftTree = temp -> left;
    while(leftTree != NULL)
    {
        pred = leftTree -> data;
        leftTree = leftTree -> right;
    }
      
    // succ
    BinaryTreeNode<int>* rightTree = temp -> right;
    while(rightTree != NULL)
    {
        succ = rightTree -> data;
        rightTree = rightTree -> left;
    }
    
    pair<int,int> ans = make_pair(pred, succ);
    return ans;
}