/*
Bottom_View_of_Binary_Tree_GFG

Given a binary tree, print the bottom view from left to right.
A node is included in bottom view if it can be seen when we look at the tree from bottom.

                      20
                    /    \
                  8       22
                /   \        \
              5      3       25
                    /   \      
                  10    14

For the above tree, the bottom view is 5 10 3 14 25.
If there are multiple bottom-most nodes for a horizontal distance from root, then print the later one in level traversal. For example, in the below diagram, 3 and 4 are both the bottommost nodes at horizontal distance 0, we need to print 4.

                      20
                    /    \
                  8       22
                /   \     /   \
              5      3 4     25
                     /    \      
                 10       14

For the above tree the output should be 5 10 4 14 25.

    Example 1:

    Input:
        1
        /   \
        3     2
    Output: 3 1 2
    Explanation : First case represents a tree with 3 nodes and 2 edges where root is 1, left child of 1 is 3 and right child of 1 is 2.

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(N).
*/

class Solution {
  public:
    vector <int> bottomView(Node *root) {
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
            
            m[hd] = frontNode -> data;  //The only change is here, as compared to top view

            
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