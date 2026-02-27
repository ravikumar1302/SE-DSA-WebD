
// Graph Representation Using 2 Approaches


//Using Matrix
// Space : O(M*N)

#include<iostream>
using namsespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    // Graph here
    int adj[n+1][m+1];
    
    for(int i=0; i<m; i++)
    {
        int u, v;
        cin >>u >> v;

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    return 0;
}


//Using List : Optimized Method
// Space : O(2E), E : no of edges

#include<iostream>
using namsespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> adj[n+1];
    
    for(int i=0; i<m; i++)
    {
        int u, v;
        cin >>u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return 0;
}