/*
Distance_of_nearest_cell_having_1_GFG

Given a binary grid of n*m. Find the distance of the nearest 1 in the grid for each cell.
The distance is calculated as |i1  - i2| + |j1 - j2|, where i1, j1 are the row number and column number of the current cell, and i2, j2 are the row number and column number of the nearest cell having value 1.

    Example 1:
    Input: grid = {{0,1,1,0},{1,1,0,0},{0,0,1,1}}
    Output: {{1,0,0,1},{0,0,1,1},{1,1,0,0}}
    Explanation: The grid is-
    0 1 1 0 
    1 1 0 0 
    0 0 1 1 
    0's at (0,0), (0,3), (1,2), (1,3), (2,0) and (2,1) are at a distance of 1 from 1's at (0,1), (0,2), (0,2), (2,3), (1,0) and (1,1) respectively.

    Example 2:
    Input: grid = {{1,0,1},{1,1,0},{1,0,0}}
    Output: {{0,1,0},{0,0,1},{0,1,2}}
    Explanation: The grid is-
    1 0 1
    1 1 0
    1 0 0
    0's at (0,1), (1,2), (2,1) and (2,2) are at a distance of 1, 1, 1 and 2 from 1's at (0,0), (0,2), (2,0) and (1,1) respectively.

Expected Time Complexity: O(n*m)
Expected Auxiliary Space: O(n*m)
*/


// Approach : From one we are moving to 0's and tracing distance
// Using BFS, as we have to move all adjacent 0's at once (or level wise)

// Time : O(n*m*4) = O(n*m)
// Space : O(n*m)

class Solution 
{
    public:
    //Function to find distance of nearest 1 in the grid for each cell.
	vector<vector<int>>nearest(vector<vector<int>>grid)
	{
	    int n = grid.size();
	    int m = grid[0].size();
	    
	    vector<vector<int>> dist(n, vector<int> (m, 0));
	    vector<vector<int>> vis(n, vector<int> (m, 0));
	    queue<pair< pair<int,int>, int >> q; 
	    
	    // Storing initial position of one's 
	    for(int i=0; i<n; i++)
	    {
	        for(int j=0; j<m; j++)
	        {
	            if(grid[i][j] == 1)
	            {
	                q.push({{i, j}, 0});
	                vis[i][j] = 1;
	            }
	            else
    	            vis[i][j] = 0;
	        }
	    }
	    
	    int delrow[] = {-1, 0, 1, 0};
	    int delcol[] = {0, 1, 0, -1};
	    // Remaning Calculation
	    // Time : n*m*4
	    while(!q.empty())
	    {
	        int row = q.front().first.first;
	        int col = q.front().first.second;
	        int steps = q.front().second;
	        q.pop();
	        dist[row][col] = steps;
	        
	        for(int i=0; i<4; i++)
	        {
	            int nrow = row + delrow[i];
	            int ncol = col + delcol[i];
	            if( (nrow >= 0 && nrow < n) && (ncol >=0 && ncol < m) && vis[nrow][ncol] == 0 )
	            {
	                vis[nrow][ncol] = 1;
	                q.push( {{nrow, ncol}, steps+1} );
	            }
	        }
	    }
	    
	    return dist;
	}
};