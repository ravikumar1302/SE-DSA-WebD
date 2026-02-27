/*
Vertical_Traversal_of_Binary_Tree_GFG

Given a Binary Tree, find the vertical traversal of it starting from the leftmost level to the rightmost level.
If there are multiple nodes passing through a vertical line, then they should be printed as they appear in level order traversal of the tree.

Example 1:

Input:
           1
         /   \
       2       3
     /   \   /   \
   4      5 6      7
              \      \
               8      9           
Output: 
4 2 1 5 6 3 8 7 9 

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(N)

*/

class Solution
{
    public:
    //Function to find the vertical order traversal of Binary Tree.
    vector<int> verticalOrder(Node *root)
    {
        vector<int> ans;
        queue< pair <Node*, int> > q;
        map<int, vector<int> > m;
        int h = 0;
        
        q.push(make_pair(root, h));
        while(!q.empty())
        {
            Node* temp = q.front().first;
            h = q.front().second;
            q.pop();
            
            m[h].push_back(temp -> data);
            
            if(temp -> left)
                q.push(make_pair(temp -> left, h-1));
            if(temp -> right)
                q.push(make_pair(temp -> right, h+1));
        }
        for(auto it : m)
            for(auto i : it.second)
                ans.push_back(i);
        
        return ans;
    }
};



// Another approach
class Solution
{
    public:
    //Function to find the vertical order traversal of Binary Tree.
    vector<int> verticalOrder(Node *root)
    {
        vector<int> ans;
        
        map< int, map<int, vector<int> > >nodes;
        queue< pair<Node*, pair<int, int> > > q;   //first int shows horizontal distance and other one shows level
        
        if(root == NULL)
            return ans;
        
        q.push(make_pair( root, make_pair(0,0) ) );
        
        while(!q.empty())
        {
            pair<Node*, pair<int, int> > temp = q.front();
            q.pop();
            
            Node* frontnode = temp.first;
            int hd = temp.second.first;
            int lvl = temp.second.second;
            
            nodes[hd][lvl].push_back(frontnode -> data);
            
            if(frontnode -> left)
                q.push(make_pair( frontnode -> left, make_pair(hd-1,lvl +1) ));
            if(frontnode -> right)
                q.push(make_pair( frontnode -> right, make_pair(hd+1,lvl +1) ));
        }
        
        for(auto i : nodes)
        {
            for(auto j : i.second)
            {
                for(auto k : j.second)
                    ans.push_back(k);
            }
        }
        
        return ans; 
    }
};