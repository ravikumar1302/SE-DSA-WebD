/*
Rat_in_a_Maze_Problem_-_I

Consider a rat placed at (0, 0) in a square matrix of order N * N. It has to reach the destination at (N - 1, N - 1). Find all possible paths that the rat can take to reach from source to destination. The directions in which the rat can move are 'U'(up), 'D'(down), 'L' (left), 'R' (right). Value 0 at a cell in the matrix represents that it is blocked and rat cannot move to it while value 1 at a cell in the matrix represents that rat can be travel through it.
Note: In a path, no cell can be visited more than one time. If the source cell is 0, the rat cannot move to any other cell.

    Example 1:

    Input : N = 4
    m[][] = {{1, 0, 0, 0},
            {1, 1, 0, 1}, 
            {1, 1, 0, 0},
            {0, 1, 1, 1}}
    Output : DDRDRR DRDDRR
    Explanation : The rat can reach the destination at (3, 3) from (0, 0) by two paths - DRDDRR and DDRDRR, when printed in sorted order we get DDRDRR DRDDRR.
*/

//Segmentation fault is coming 

class Solution{
    private:
    bool issafe(int x, int y, int n, vector<vector<int>> visited, vector<vector<int>>& m)
    {
        if( (x > 0 && x < n) && (y > 0 && y < n) && visited[x][y] == 0 && m[x][y] == 1)
            return true;
        else 
            false;
    }
    
    void solve(vector<vector<int>> m, int n, vector<string>& ans, vector<vector<int>> visited, int x, int y, string path)
    {
        //we are at position x, y now
        if(x == n-1 && y == n-1)  //base case
            {
                ans.push_back(path);
                return ;
            }
        visited[x][y] = 1;  //marking visited position true
        
        // 4 choices of path : D, L, R, U
        
        //Down
        int newx = x + 1;
        int newy = y;
        if(issafe(newx, newy, n, visited, m))
        {
            path.push_back('D');
            solve(m, n, ans, visited, newx, newy, path);
            path.pop_back();
        }
        
        //Left
        newx = x;
        newy = y - 1;
        if(issafe(newx, newy, n, visited, m))
        {
            path.push_back('L');
            solve(m, n, ans, visited, newx, newy, path);
            path.pop_back();
        }
        
        //Right
        newx = x;
        newy = y + 1;
        if(issafe(newx, newy, n, visited, m))
        {
            path.push_back('R');
            solve(m, n, ans, visited, newx, newy, path);
            path.pop_back();
        }
        
        //Up
        newx = x - 1;
        newy = y;
        if(issafe(newx, newy, n, visited, m))
        {
            path.push_back('U');
            solve(m, n, ans, visited, newx, newy, path);
            path.pop_back();
        }
        
        visited[x][y] = 0;  // backtracking, so making it 0, as many paths possible
    }
    
    public:
    vector<string> findPath(vector<vector<int>> &m, int n) {
        
        vector<string> ans;
        if(m[0][0] == 0)
            return ans;
        
        int srcx = 0; 
        int srcy = 0;
        vector<vector<int>> visited;
        
        for(int i = 0; i < n; i++)  //initiliazing with zero 
            for(int j = 0; j < n; j++)
                visited[i][j] = 0;
        
        string path ="";
        solve(m, n, ans, visited, srcx, srcy, path);
        //sort(ans.begin(), ans.end());
        return ans;
    }
};

