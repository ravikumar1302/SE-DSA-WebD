/*
K_Sum_Paths_GFG

Given a binary tree and an integer K. Find the number of paths in the tree which have their sum equal to K.
A path may start from any node and end at any node in the downward direction.

Example 1:

Input:      
Tree = 
          1                               
        /   \                          
       2     3
K = 3
Output: 2
Explanation:
Path 1 : 1 + 2 = 3
Path 2 : only leaf node 3

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(Height of Tree)
*/

/*
struct Node 
{
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
    void solve(Node* root, int k, int &count, vector<int> path)
    {
        if(root == NULL)    //Base case
            return ;
        
        path.push_back(root -> data);
        
        //left
        solve(root -> left, k, count, path);
        
        //right
        solve(root -> right, k, count, path);
        
        //checking sum
        int size = path.size();
        int sum = 0;
        for(int i = size-1; i>=0; i--)
            {
                sum += path[i];
                if(sum == k)
                    count++;
            }
        path.pop_back();
    }
    
    int sumK(Node *root,int k)
    {
        // Approach : find all paths and sum them and equate them with k
        vector<int> path;
        int count = 0;
        solve(root, k, count, path);
        return count;
    }
};