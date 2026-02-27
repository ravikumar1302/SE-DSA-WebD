/*
Rotten_Oranges_GFG

Given a grid of dimension nxm where each cell in the grid can have values 0, 1 or 2 which has the following meaning:
    0 : Empty cell
    1 : Cells have fresh oranges
    2 : Cells have rotten oranges

We have to determine what is the minimum time required to rot all oranges. A rotten orange at index [i,j] can rot other fresh orange at indexes [i-1,j], [i+1,j], [i,j-1], [i,j+1] (up, down, left and right) in unit time. 
 
    Example 1:
    Input: grid = {{0,1,2},{0,1,2},{2,1,1}}
    Output: 1
    Explanation: The grid is-
    0 1 2
    0 1 2
    2 1 1
    Oranges at positions (0,2), (1,2), (2,0) will rot oranges at (0,1), (1,1), (2,2) and (2,1) in unit time.

    Example 2:
    Input: grid = {{2,2,0,1}}
    Output: -1
    Explanation: The grid is-2 2 0 1
    Oranges at (0,0) and (0,1) can't rot orange at (0,3).


Expected Time Complexity: O(n*m)
Expected Auxiliary Space: O(n)
*/


// Approach-2

class Solution 
{
    public:
    //Function to find minimum time required to rot all oranges. 
    int orangesRotting(vector<vector<int>>& grid) {
       
       bool check=true;
       int ans=0;
       int m=grid.size();
       int n=grid[0].size();
       
       while(check)
       {
           check=false;
           ans++;
           for(int i=0;i<m;i++)
           {
               for(int j=0;j<n;j++)
               {
                   if(grid[i][j]==2)
                   {
                       // Marking them 12, to make them 2 in next loop, to record time consumed
                       if(i-1>=0 && grid[i-1][j]==1) grid[i-1][j]=12;
                       if(j-1>=0 && grid[i][j-1]==1) grid[i][j-1]=12;
                       if(j+1<n && grid[i][j+1]==1) grid[i][j+1]=12;
                       if(i+1<m && grid[i+1][j]==1) grid[i+1][j]=12;
                   }
               }
           }
           for(int i=0;i<m;i++)
           {
               for(int j=0;j<n;j++) 
                   if(grid[i][j]==12)
                   {
                       grid[i][j]=2;
                       check=true;
                   } 
           }
       }
       // If still some one left, return -1
       for(int i=0;i<m;i++)
           for(int j=0;j<n;j++)
               if(grid[i][j]==1) 
                    return -1;

       return ans-1;
    }
};



// Striver Approach : But not working

// Time : O(n*m) + O(4*N*M) = O(n*m)
// Space : O(n*m), for queue
class Solution 
{
    public:
    //Function to find minimum time required to rot all oranges. 
    int orangesRotting(vector<vector<int>>& grid) {
        
    // We will use BFS,  becaue it traverse level wise, and question is also demanding the same, as in one unit of time, it traverses it's neghbours or it's level only
    
        int n = grid.size();
        int m = grid[0].size();
        
        // { {row, col}, time}
        queue< pair<pair<int, int>, int >> q;
        int vis[n][m];
        int cntFresh = 0;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                if(grid[i][j] == 2)
                {
                    q.push( {{i,j}, 0});
                    vis[i][j] = 2;
                }
                else
                    vis[i][j] = 0;
                if(grid[i][j] == 1)
                    cntFresh++;
            }
        }
        
        // BFS code
        int tm = 0;
        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, 1, 0, -1};
        int cnt = 0;
        while(!q.empty())
        {
            int r = q.front().first.first;
            int c = q.front().first.second;
            int t = q.front().second;
            tm = max(tm, t);
            q.pop();
            
            for(int i=0; i<4; i++)
            {
                int nrow = r + delrow[i];
                int ncol = c + delcol[i];
                
                if( (nrow >= 0 && nrow < n) && (ncol >= 0 && ncol < m) && vis[nrow][ncol] != 2 && grid[nrow][ncol] == 1 )
                {
                    q.push({{nrow,ncol}, t+1});
                    vis[nrow][ncol] = 1;
                    cnt++;
                }
            }
        }
        
        // Check if all oranges are rotten or not
        if(cntFresh != cnt)
            return -1;
        return tm;   
    }
            
};

