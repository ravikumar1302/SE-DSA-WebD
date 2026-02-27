/*
Determine_if_Two_Trees_are_Identical_GFG

Given two binary trees, the task is to find if both of them are identical or not. 


Example 2:

Input:
     1          1
   /   \      /   \
  2     3    2     3
Output: Yes
Explanation: There are two trees both having 3 nodes and 2 edges, both trees are identical having the root as 1, left child of 1 is 2 and right child of 1 is 3.

*/

/*A binary tree node


struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};
*/


   
class Solution
{
    public:
    //Function to check if two trees are identical.
    bool isIdentical(Node *r1, Node *r2)
    {
        if(r1 == NULL && r2 == NULL)
            return true;
        if(r1 == NULL && r2 != NULL)
            return false;
        if(r1 != NULL && r2 == NULL)
            return false;
            
        bool left = isIdentical(r1 -> left, r2 -> left);
        bool right = isIdentical(r1 -> right, r2 -> right);
        bool value = r1-> data == r2 -> data;
        
        if(left && right && value)
            return true;
        else
            return false;
    }
};

// T.C. : O(N) as we are visiting each node only once