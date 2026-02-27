/*
Count_Leaf_Nodes_Codestudio

Problem Statement
You are given a Binary tree. You have to count and return the number of leaf nodes present in it.
A binary tree is a tree data structure in which each node has at most two children, which are referred to as the left child and the right child
A node is a leaf node if both left and right child nodes of it are NULL.

*/

/**********************************************************

    Following is the Binary Tree Node class structure:

    template <typename T>
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
    
***********************************************************/
int count(BinaryTreeNode<int> *root, int cnt)
{
    queue<BinaryTreeNode<int>*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty())
    {
        BinaryTreeNode<int>* temp = q.front();
        q.pop();
        if(temp == NULL)
        {
            //one level is completed
            if(!q.empty())    //some child elements left
                q.push(NULL);
        }
        else
        {
            if(temp ->left) {
                q.push(temp ->left);
            }

            if(temp ->right) {
                q.push(temp ->right);
            }
            
            if(temp -> left == NULL && temp -> right == NULL)
                cnt++;
            
        }
    }
    return cnt;
}
int noOfLeafNodes(BinaryTreeNode<int> *root){
    return count(root, 0);
    
}

// other method

void inorder(BinaryTreeNode<int> * root, int &count) {
    //base case
    if(root == NULL) {
        return ;
    }

    inorder(root->left, count);
   	
    //leaf node
    if(root->left == NULL && root->right == NULL) {
        count++;
    }
    
    inorder(root->right, count);

}


int noOfLeafNodes(BinaryTreeNode<int> *root){
    int cnt = 0;
    inorder(root, cnt);
    return cnt;
}