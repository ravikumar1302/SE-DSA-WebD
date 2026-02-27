/*
Delete_Node_in_a_BST_Leetcode_450
Delete a node from BST GFG

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages: Search for a node to remove. If the node is found, delete the node.

    Example 1:
    Input: root = [5,3,6,2,4,null,7], key = 3
    Output: [5,4,6,2,null,null,7]
    Explanation: Given key to delete is 3. So we find the node with value 3 and delete it. One valid answer is [5,4,6,2,null,null,7], shown in the above BST. Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

    Example 2:
    Input: root = [5,3,6,2,4,null,7], key = 0
    Output: [5,3,6,2,4,null,7]
    Explanation: The tree does not contain a node with value = 0.

    Example 3:
    Input: root = [], key = 0
    Output: []

Constraints: Each node has a unique value.

Expected Time Complexity: O(Height of the BST).
Expected Auxiliary Space: O(Height of the BST).

Follow up: Could you solve it with time complexity O(height of tree)?
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        
        if(root == NULL)    // empty BST
            return NULL;
        
        else if(key < root->val)     // go left side
            root -> left = deleteNode(root->left, key);
        else if(key > root->val)     // go right side
            root -> right = deleteNode(root->right, key);
        
        else    // We are at node, with value == Key
        {
            if(root->left == NULL && root->right == NULL)   // No child
                return NULL;
            if (!root->left || !root->right)
                    return root->left ? root->left : root->right;    //One child contion -> replace the node with it's child
			

            // Two Child
            TreeNode* temp = root->left;                        //(or) TreeNode *temp = root->right;
            while(temp->right != NULL) temp = temp->right;     //      while(temp->left != NULL) temp = temp->left;
            root->val = temp->val;                            //       root->val = temp->val;
            root->left = deleteNode(root->left, temp->val);  //        root->right = deleteNode(root->right, temp);	
        }
        
        return root;
    }
};

// Time = O(height)

// The node has 2 children - In this case, in order to conserve the BST properties, we need to replace the node with it's inorder successor (The next node that comes in the inorder traversal) i.e; we need to replace it with either :
    // 1. The greatest value node in it's left subtree (or)
    //  2. The smallest value node in it's right subtree   and return the root