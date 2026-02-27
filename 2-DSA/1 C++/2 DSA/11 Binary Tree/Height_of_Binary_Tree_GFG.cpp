/*
Height_of_Binary_Tree_GFG

Given a binary tree, find its height.


Example 1:

Input:
     1
    /  \
   2    3
Output: 2

*/

/*
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
class Solution{
    private:

    int inorder(Node* node)
    {
        if(node == NULL)
            return 0;
        int cnt1 = inorder(node -> left);
        int cnt2 = inorder(node -> right);
        return (max(cnt1, cnt2) + 1);   // + 1 was done to add the root node
    }
    
    public:
    //Function to find the height of a binary tree.
    int height(struct Node* node){
        return inorder(node);
        
    }
};

// T.C. : O(N)
// S.C. : O(heights)