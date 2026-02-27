/*
Top_View_of_Binary_Tree_GFG

Given below is a binary tree. The task is to print the top view of binary tree. Top view of a binary tree is the set of nodes visible when the tree is viewed from the top. For the given below tree

       1
    /     \
   2       3
  /  \    /   \
4    5  6   7

Top view will be: 4 2 1 3 7
Note: Return nodes from leftmost node to rightmost node.

Example 1:

Input:
      1
   /    \
  2      3
Output: 2 1 3

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(N)
*/

/*
struct Node
{
    int data;
    Node* left;
    Node* right;
};
*/
class Solution
{
    public:
    //Function to return a list of nodes visible from the top view 
    //from left to right in Binary Tree.
    vector<int> topView(Node *root)
    {
        vector<int> ans;
        if(root == NULL)    //Base case
            return ans;
            
        map<int,int> m;
        queue< pair<Node*, int> > q;
        q.push(make_pair(root, 0));
        
        while(!q.empty())
        {
            pair<Node*, int> temp = q.front();
            q.pop();
            Node* frontNode = temp.first;
            
            int hd = temp.second;   //hd = horizontal distance
            
            //if one value is present for hd, do nothing
            if(m.find(hd) == m.end())
                m[hd] = frontNode -> data;
            
            if(frontNode -> left)
                q.push(make_pair(frontNode -> left, hd-1)); 
            if(frontNode -> right)
                q.push(make_pair(frontNode -> right, hd+1)); 
        }
        for(auto i: m)
           ans.push_back(i.second); 
        return ans;
    }

};