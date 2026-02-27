/*
DFS_of_Graph_GFG

Given a connected undirected graph. Perform a Depth First Traversal of the graph.
Note: Use recursive approach to find the DFS traversal of the graph starting from the 0th vertex from left to right according to the graph..

    Example 1:
    Input:In GFG picture
    Output: 0 1 2 4 3
    Explanation: 
    0 is connected to 1, 2, 4.
    1 is connected to 0.
    2 is connected to 0.
    3 is connected to 4.
    4 is connected to 0, 3.
    so starting from 0, it will go to 1 then 2, then 4, and then from 4 to 3. Thus dfs will be 0 1 2 4 3.

    Example 2:
    Input:In GFG picture
    Output: 0 1 2 3
    Explanation:
    0 is connected to 1 , 3.
    1 is connected to 2. 
    2 is connected to 1.
    3 is connected to 0. 
    so starting from 0, it will go to 1 then 2, then back to 0 then 0 to 3, thus dfs will be 0 1 2 3. 

Expected Time Complexity: O(V + E)
Expected Auxiliary Space: O(V)
*/


class Solution {
  private :
  void dfs(int node, vector<int> adj[], int vis[], vector<int> &ls)
  {
      vis[node] = 1;
      ls.push_back(node);

      // Traversing all its neighbours
      for(auto it : adj[node])
      {
          if(!vis[it])
              dfs(it, adj, vis, ls);
      }
  }

  public:
    // Function to return a list containing the DFS traversal of the graph.
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        
        // Given a Connected Undirected Graph and also 0 based indexing
        int vis[V] = {0};
        int start = 0;
        vector<int> ls;

        dfs(start, adj, vis, ls);

        return ls;
    }
};

// Time : O(N) + O(2E)
// Space : O(N)