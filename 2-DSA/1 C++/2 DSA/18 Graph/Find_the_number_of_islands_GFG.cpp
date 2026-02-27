/*
Find_the_number_of_islands_GFG (Number of Islands | Number of Connected Components in Matrix )
Given a grid of size n*m (n is the number of rows and m is the number of columns in the grid) consisting of '0's (Water) and '1's(Land). Find the number of islands.
Note: An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically or diagonally i.e., in all 8 directions.

    Example 1:
    Input: grid = {{0,1},{1,0},{1,1},{1,0}}
    Output: 1
    Explanation:
    The grid is-
    0 1
    1 0
    1 1
    1 0
    All lands are connected.

    Example 2:
    Input: grid = {{0,1,1,1,0,0,0},{0,0,1,1,0,1,0}}
    Output: 2
    Expanation:
    The grid is-
    0 1 1 1 0 0 0
    0 0 1 1 0 1 0 
    There are two islands :- one is colored in blue and other in orange.

Expected Time Complexity: O(n*m)
Expected Space Complexity: O(n*m)
*/


class Solution {
    private:
    
    void bfs(int row, int col, vector<vector<char>>& grid, vector<vector<int>> &vis)
    {
        vis[row][col] = 1;
        queue<pair<int,int>> q;
        q.push({row, col});
        int n = grid.size();
        int m = grid[0].size();
        
        while(!q.empty())
        {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            // Traverse in the neighbours and mark them visited if not visited
            for(int delrow = -1; delrow <= 1; delrow++)
            {
                for(int delcol = -1; delcol <= 1; delcol++)
                {
                    int nrow = row + delrow;
                    int ncol = col + delcol;
                    
                    if( (nrow >= 0 && nrow < n) && (ncol >= 0 && ncol < m) && grid[nrow][ncol] == '1' && !vis[nrow][ncol] )
                    {
                        vis[nrow][ncol] = 1;
                        q.push({nrow, ncol});
                    }
                }
            }
        }
    }
    
  public:
    // Function to find the number of islands.
    int numIslands(vector<vector<char>>& grid) {
        
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int> (m, 0));
        int cnt = 0;
        
        for(int row = 0; row < n; row++)
        {
            for(int col=0; col < m; col++)
            {
                if(!vis[row][col] && grid[row][col] == '1')
                {
                    cnt++;
                    bfs(row, col, grid, vis);
                }
            }
        }
        return cnt;
    }
};

// Time : O(9*(N^2)) = O(N^2) (8 neighbour and one itself)
// Space : O(N^2) + O(N^2) + = O(N^2) (visited matrix, queue pair)