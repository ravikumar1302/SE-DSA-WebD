/*
Kth_Ancestor_in_a_Tree_GFG

Given a binary tree of size  N, a node and a positive integer k., Your task is to complete the function kthAncestor(), the function should return the kth ancestor of the given node in the binary tree. If there does not exist any such ancestor then return -1.

Example 2:

Input:
k=1 
node=3
      1
    /   \
    2     3

Output : 1
Explanation : K=1 and node=3 ,Kth ancestor of node 3 is 1.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(N)

*/

/*
Structure of the node of the binary tree is as
struct Node
{
	int data;
	struct Node *left, *right;
};
*/
// your task is to complete this function
void solve(Node *root, int k, int node, int &ans, vector<int> path)
{
    if(root == NULL)
        return ;
    
    path.push_back(root -> data);
    
    solve(root -> left, k, node, ans, path);
    solve(root -> right, k, node, ans, path);
    
    //checking node
    if(root -> data == node)
    {
        int size = path.size();
        if(k >= size)
            { 
                ans = -1;
                return;
            }
        ans = path[size - k -1];
    }
    path.pop_back();
    
}
int kthAncestor(Node *root, int k, int node)
{
    int ans = -1;
    vector<int> path;
    solve(root, k, node, ans, path);
    return ans;
}




// Other solution
Node* solve(Node* root, int &k, int node) {
    //base case
    if(root == NULL)
        return NULL;
        
    if(root->data == node) 
        return root;
    
    Node* leftAns = solve(root->left, k, node);
    Node* rightAns = solve(root->right, k, node);

    //wapas
    if(leftAns != NULL && rightAns == NULL) 
    {
        k--;
        if(k<=0) 
        {
            //answer lock
            k = INT_MAX;
            return root;
        }
        return leftAns;
    }
    
    if(leftAns == NULL && rightAns != NULL) {
        k--;
        if(k<=0) 
        {
            //answer lock
            k = INT_MAX;
            return root;
        }
        return rightAns;
    }
    return NULL;
}

int kthAncestor(Node *root, int k, int node)
{
    Node* ans = solve(root, k, node);
    if(ans == NULL || ans->data == node)
        return -1;
    else
        return ans->data;
}