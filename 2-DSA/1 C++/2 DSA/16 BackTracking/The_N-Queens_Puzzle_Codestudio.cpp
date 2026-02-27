/*
The_N-Queens_Puzzle_Codestudio

The N Queens puzzle is the problem of placing N chess queens on an N * N chessboard such that no two queens attack each other.
Given an integer ‘N’, print all distinct solutions to the ‘N’ queen puzzle.
Two queens on the same chessboard can attack each other if any of the below condition satisfies:  
1. They share a row. 
2. They share a column. 
3. They share a diagonal.

*/

void addSolution(vector< vector<int> > &board, vector<vector<int>> &ans, int n)
{
    vector<int> temp;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            temp.push_back(board[i][j]);
    ans.push_back(temp);
}

// This below function takes O(N) time to check, to reduce it to O(1), use hash map map<int, bool> to store which row and diagonal elements
bool isSafe(int row, int col, vector< vector<int> > &board, int n) 
{
    int x = row;
    int y = col;
    
    // Check for same row (only left side, as we haven't filled data on right side)
    while(y>=0)
    {
        if(board[x][y] == 1)
            return false;
        y--;
    }
    // No need to check column, as we are only placing one element in a column and then moving to next column
    
    // Checking Diagonal (only left side)
    // Upper left digonal, row and column both reduces by 1 value 
    x = row;
    y = col;
    while(x>=0 && y>=0)
    {
        if(board[x][y] == 1)
            return false;
        x--;
        y--;
    }
    // Bottom left digonal, row increases and col decreases
    x = row;
    y = col;
    while(x<n && y>=0)
    {
        if(board[x][y] == 1)
            return false;
        x++;
        y--;
    }
    return true;
}

void solve(int col, vector<vector<int>> &ans, vector< vector<int> > &board, int n)
{
    // Base case
    if(col == n)
    {
        addSolution(board, ans, n);
        return;
    }
    
    // Solve 1 case, rest recursion will take care
    for(int row=0; row<n; row++)
    {
        if( isSafe(row, col, board, n) )
        {
            board[row][col] = 1;
            solve(col+1, ans, board, n);
            board[row][col] = 0;    // Backtracking
        }
    }
}

vector<vector<int>> nQueens(int n)
{
    vector< vector<int> > board(n, vector<int>(n, 0)) ;
    vector<vector<int>> ans;
    
    solve(0, ans, board, n);
    return ans;
}

// T.C. : O(N!)
// S.C.: O(N*N)

// Optimized solution in which hashmap is used to check in isSafe function, also takes O(N!) time