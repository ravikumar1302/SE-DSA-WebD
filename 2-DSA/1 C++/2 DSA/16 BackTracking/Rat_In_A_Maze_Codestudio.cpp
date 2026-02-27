/*
Rat_In_A_Maze_Codestudio

You are given a starting position for a rat which is stuck in a maze at an initial point (0, 0) (the maze can be thought of as a 2-dimensional plane). The maze would be given in the form of a square matrix of order 'N' * 'N' where the cells with value 0 represent the maze’s blocked locations while value 1 is the open/available path that the rat can take to reach its destination. The rat's destination is at ('N' - 1, 'N' - 1). Your task is to find all the possible paths that the rat can take to reach from source to destination in the maze. The possible directions that it can take to move in the maze are 'U'(up) i.e. (x, y - 1) , 'D'(down) i.e. (x, y + 1) , 'L' (left) i.e. (x - 1, y), 'R' (right) i.e. (x + 1, y).
Note:
Here, sorted paths mean that the expected output should be in alphabetical order.
    
    For Example:
    Given a square matrix of size 4*4 (i.e. here 'N' = 4):
    1 0 0 0
    1 1 0 0
    1 1 0 0
    0 1 1 1 
    Expected Output:
    DDRDRR DRDDRR 
    i.e. Path-1: DDRDRR and Path-2: DRDDRR

    The rat can reach the destination at (3, 3) from (0, 0) by two paths, i.e. DRDDRR and DDRDRR when printed in sorted order, we get DDRDRR DRDDRR.

*/

bool isSafe(int newx, int newy, vector< vector<bool> > &vis, vector < vector < int >> & arr, int n)
{
    if( (newx>=0 && newx<n) && (newy>=0 && newy<n) && vis[newx][newy] != 1 && arr[newx][newy] == 1 )
        return true;
    else
        return false;
}

void solve(int x, int y, vector < vector < int >> & arr, int n, vector<string> &ans, vector< vector<bool> > &vis, string path)
{
    // Base case
    if(x == n-1 && y == n-1)
    {
        ans.push_back(path);
        return;
    }
    
    // 4 movement
    // D, L, R, U
    
    vis[x][y] = 1;
    // Down
    if( isSafe(x+1, y, vis, arr, n) )
        solve(x+1, y, arr, n, ans, vis, path + 'D');
    
    // Left
    if( isSafe(x, y-1, vis, arr, n) )
        solve(x, y-1, arr, n, ans, vis, path + 'L');
    
    // Right
    if( isSafe(x, y+1, vis, arr, n) )
        solve(x, y+1, arr, n, ans, vis, path + 'R');

    // Up
    if( isSafe(x-1, y, vis, arr, n) )
        solve(x-1, y, arr, n, ans, vis, path + 'U');

    vis[x][y] = 0;  // Back Tracking
}

vector < string > searchMaze(vector < vector < int >> & arr, int n) {
    
    vector<string> ans;
    vector< vector<bool> > visited (n, vector<bool> (n,0) );
    string path = "";
    
    // Edge Case
    if(arr[0][0] == 0)
        return ans;
    
    solve(0, 0, arr, n, ans, visited, path);
    return ans;
}

// T.C. : 4^(n*n) (4 to the power n square)
// S.C. : O(n*n) //as visied all cell of matrix