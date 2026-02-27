/*
ZigZag_Tree_Traversal_GFG
Binary Tree Right Side View Leetcode_103

Given a Binary Tree. Find the Zig-Zag Level Order Traversal of the Binary Tree.

    Example 1 : 
    Input:
            3
        /   \
        2     1
    Output : 3 1 2

    Example 2:

    Input:
            7
            /     \
        9       7
        /  \     /   
        8    8   6     
    /  \
    10   9 
    Output: 7 7 9 8 8 6 9 10 

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(N)

*/

/*Structure of the node of the binary tree is as
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

class Solution{
    public:
    //Function to store the zig zag order traversal of tree in a list.
    vector <int> zigZagTraversal(Node* root)
    {
    	vector<int> result;
    	if(root == NULL)
    	    return result;
    	 
    	queue<Node*> q;
    	q.push(root);
    	
    	bool leftToRight = true;
    	
    	while(!q.empty())
    	{
    	    int size = q.size();
    	    vector<int> ans(size);  //temporary array
    	    
    	    //level process
    	    for(int i = 0; i<size; i++)
    	    {
    	        Node* temp = q.front();
    	        q.pop();
    	        
    	        //Normal or reverse insert
    	        int index = leftToRight ? i : size - i - 1;
    	        ans[index] = temp -> data;
    	        
    	        if(temp -> left)
    	            q.push(temp -> left);
    	        if(temp -> right)
    	            q.push(temp -> right);
    	    }
    	    
    	    //Direction change
    	    leftToRight = !leftToRight;
    	    
    	    for(auto i : ans)
    	        result.push_back(i);
 
    	}
    	   return result;
    }
};

// T.C. : O(N)
// S.C : O(N)



// Leetcode Solution 
// Diffence from above code : return type of the function,  so 2 changes were needed for that (declaration of result, pushing temporary ans in result)

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        
        vector<vector<int> > result;
    	if(root == NULL)
    	    return result;
    	 
    	queue<TreeNode*> q;
    	q.push(root);
    	
    	bool leftToRight = true;
    	
    	while(!q.empty())
    	{
    	    int size = q.size();
    	    vector<int> ans(size);  //temporary array
    	    
    	    //level process
    	    for(int i = 0; i<size; i++)
    	    {
    	        TreeNode* temp = q.front();
    	        q.pop();
    	        
    	        //Normal or reverse insert
    	        int index = leftToRight ? i : size - i - 1;
    	        ans[index] = temp -> val;
    	        
    	        if(temp -> left)
    	            q.push(temp -> left);
    	        if(temp -> right)
    	            q.push(temp -> right);
    	    }
    	    
    	    //Direction change
    	    leftToRight = !leftToRight;
    	    
    	    result.push_back(ans);
 
    	}
    	   return result;
    }
};