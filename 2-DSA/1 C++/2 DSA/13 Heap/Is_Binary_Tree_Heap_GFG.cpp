/*
Is_Binary_Tree_Heap_GFG

Given a binary tree. The task is to check whether the given tree follows the max heap property or not.
Note: Properties of a tree to be a max heap - Completeness and Value of node greater than or equal to its child.

    Example 1:

    Input:
        5
        /  \
    2    3
    Output: 1
    Explanation: The given tree follows max-heap property since 5, is root and it is greater than both its children.
Expected Time Complexity: O(N)
Expected Space Complexity: O(N)
*/

// Structure of node
/*struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};*/

class Solution {
  public:
  int countnodes(struct Node* root)
  {
      if(root == NULL)
        return 0;
    
    int ans = 1 + countnodes(root -> left) + countnodes(root ->right);
    return ans;
  }
  
  bool isCBT(struct Node* root, int i, int count)
  {
    if(root == NULL)
        return true;
        
    if(i > count)
        return false;
    
    else
    {
        bool left = isCBT(root->left, 2*i +1, count);
        bool right = isCBT(root->right, 2*i +2, count);
        return (left && right);
    }
  }
  
  bool isMaxOrder(struct Node* root)
  {
    // Reaching here means BT is CBT
    // So, only 3 cases are possible, both child exist, only left exist, and leaf nodes
    // Now, check parent node value is greater than chil nodes or not
      
    // leaf nodes : they are already a heap
    if(root ->left == NULL && root ->right == NULL)
        return true;
        
    // Only Left exist
    if(root->right == NULL)
        return (root->data > root->left->data);
        
    // Both child exist
    else
    {
        bool left = isMaxOrder(root -> left);
        bool right = isMaxOrder(root -> right);
        
        return (left && right &&
        root->data > root->left->data && root->data > root->right->data);
    }
  }
  
bool isHeap(struct Node* tree) {
        
        // Approach : Max-Heap has two properties: CBT and parent node greater than child
        // So, we will check these two properties
        
        int index = 0;
        int totalcount = countnodes(tree);
        
        if(isCBT(tree, index, totalcount) && isMaxOrder(tree) )
            return true;
        else
            return false;
}
        
    };