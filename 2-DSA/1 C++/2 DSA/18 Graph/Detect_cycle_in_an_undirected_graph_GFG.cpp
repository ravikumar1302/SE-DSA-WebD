/*
Detect_cycle_in_an_undirected_graph_GFG

Given an undirected graph with V vertices and E edges, check whether it contains any cycle or not. 

    Example 1:
    Input:  V = 5, E = 5, adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}} 
    Output: 1
    Explanation: 1->2->3->4->1 is a cycle.

    Example 2:
    Input: V = 4, E = 2, adj = {{}, {2}, {1, 3}, {2}}
    Output: 0
    Explanation: No cycle in the graph.
 
NOTE: The adjacency list denotes the edges of the graph where edges[i] stores all other vertices to which ith vertex is connected.

Expected Time Complexity: O(V + E)
Expected Space Complexity: O(V)
*/


// Using BFS

class Solution {
  public:
    
    bool detect(int src, vector<int> adj[], int vis[])
    {
        vis[src] = 1;
        queue<pair<int, int>> q;
        q.push({src, -1});
        
        while(!q.empty())
        {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();
            
            for(auto adjacentNode : adj[node])
            {
                if(!vis[adjacentNode])
                {
                    vis[adjacentNode] = 1;
                    q.push({adjacentNode, node});
                }
                else if(parent != adjacentNode)
                    return true;
            }
        }
        return false;
    }
  
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        
        int vis[V] = {0};
        
        for(int i=0; i<V; i++)
        {
            if(!vis[i])
                if(detect(i, adj, vis) == true)
                    return true;
        }
        
        return false;
    }
};



// Using DFS

class Solution {
  public:
    
    bool detectDFS(int node, int parent, vector<int> adj[], int vis[])
    {
        vis[node] = 1;
        
        for(auto adjacentNode : adj[node])
        {
            if(!vis[adjacentNode])
            {
                if(detectDFS(adjacentNode, node, adj, vis) == true)
                    return true;
            }
            else if(adjacentNode != parent)
                return true;
        }
        return false;
    }
  
  
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        
        int vis[V] = {0};
        
        for(int i=0; i<V; i++)
        {
            if(!vis[i])
                if(detectDFS(i, -1, adj, vis) == true)
                    return true;
        }
        
        return false;
    }
};