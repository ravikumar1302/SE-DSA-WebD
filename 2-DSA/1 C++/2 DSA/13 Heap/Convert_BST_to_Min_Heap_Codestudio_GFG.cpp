/*
Convert_BST_to_Min_Heap_Codestudio_GFG

You are given a 'ROOT' of a binary search tree of integers. The given BST is also a complete binary tree.
Your task is to convert the given binary search tree into a Min Heap and print the preorder traversal of the updated binary search tree.

    A Binary Heap is a Binary Tree with the following property:

    It’s a complete tree (all levels are filled except possibly the last level and the last level has all keys as left as possible). This property of Binary Heap makes them suitable to be stored in an array.

    A Binary Heap is either Min Heap or Max Heap. In a Min Binary Heap, the key at the root must be minimum among all keys present in Binary Heap. The same property must be recursively true for all nodes in Binary Tree. Max Binary Heap is similar to Min Heap.

For example:
    Given:- BST’s ‘ROOT’ = 4 2 6 -1 -1 -1 -1 
    Then the min-heap in pre-order fashion would be 2 4 6.

Time Complexity: O(n) 
Auxiliary Space: O(n)   

*/

/*************************************************************
    
    Following is the Binary Tree node structure:

	class BinaryTreeNode {
		
	public :
		int data;
		BinaryTreeNode* left;
		BinaryTreeNode* right;

		BinaryTreeNode(int data) {
		this -> left = NULL;
		this -> right = NULL;
		this -> data = data;
		}
	};

*************************************************************/
void inorder(BinaryTreeNode* root, vector<int> &in)
{
    // Inorder : LNR
    if(root == NULL)
        return;
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}

void preorder(BinaryTreeNode* root, vector<int> &in, int &i)
{
    // Preorder : NLR
    if(root == NULL)
        return;
    
    root-> data = in[i++];
    preorder(root->left, in, i);
    preorder(root->right, in, i);
}

BinaryTreeNode* convertBST(BinaryTreeNode* root)
{
    /*
    1. Perform the inorder traversal of the BST and copy the node values in the arr[] (inorder of BST is sorted)
    2. Now perform the preorder traversal,  While traversing the root during the preorder traversal, one by one copy the values from the array arr[] to the nodes.
    */
	BinaryTreeNode* temp = root;
    
    vector<int> in;
    inorder(root, in);
    
    int index = 0;
    preorder(root, in, index);
    
    return root;
}