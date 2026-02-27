/*
Sudoku_Solver_Codestudio

You have been given a 9x9 2d integer matrix 'MAT' representing a Sudoku puzzle. The empty cells of the Sudoku are filled with zeros, and the rest of the cells are filled with integers from 1 to 9. Your task is to fill all the empty cells such that the final matrix represents a Sudoku solution.
Note:
A Sudoku solution must satisfy all the following conditions-
1. Each of the digits 1-9 must occur exactly once in each row.
2. Each of the digits 1-9 must occur exactly once in each column.
3. Each of the digits 1-9 must occur exactly once in each of the 9, 3x3 sub-grids of the grid.

You can also assume that there will be only one sudoku solution for the given matrix.

        Sample Input 1
        3 0 6 5 0 8 4 0 0
        5 2 0 0 0 0 0 0 0
        0 8 7 0 0 0 0 3 1
        0 0 3 0 1 0 0 8 0
        9 0 0 8 6 3 0 0 5
        0 5 0 0 9 0 6 0 0
        1 3 0 0 0 0 2 5 0
        0 0 0 0 0 0 0 7 4
        0 0 5 2 0 6 3 0 0

        Sample Output 1
        3 1 6 5 7 8 4 9 2
        5 2 9 1 3 4 7 6 8
        4 8 7 6 2 9 5 3 1
        2 6 3 4 1 5 9 8 7
        9 7 4 8 6 3 1 2 5
        8 5 1 7 9 2 6 4 3
        1 3 8 9 4 7 2 5 6
        6 9 2 3 5 1 8 7 4
        7 4 5 2 8 6 3 1 9

        Explanation For Sample Output 1
        In the output:
        In each row, each of the digits 1-9 is occurring exactly once.
        In each column, each of the digits 1-9 is occurring exactly once.
        In each 3x3 sub-grids of the grid, each of the digits is occurring exactly once.

*/

bool isSafe(int row, int col, vector<vector<int>>& sudoku, int val, int n)
{
    for(int i=0; i<n; i++)
    {
        // Row check
        if(sudoku[row][i] == val)
            return false;
        // Column check
        if(sudoku[i][col] == val)
            return false;
        // 3*3 matrix check
        if( sudoku[3*(row/3) + i/3][3*(col/3) + i%3] == val)
            return false;
      }      
        return true;
}

bool solve(vector<vector<int>>& sudoku)
{
    int n = sudoku[0].size();
    
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            // Cell empty
            if(sudoku[row][col] == 0)
            {
                for(int val=1; val<=9; val++)
                {
                    if( isSafe(row, col, sudoku, val, n) )
                    {
                        sudoku[row][col] = val;
                        // Recusrion
                        bool nextSolution = solve(sudoku);
                        if(nextSolution)
                            return true;
                        else    // Backtrack
                            sudoku[row][col] = 0;
                    }
                }
                return false;     // As no value satisfied from 1-9
            }
        }
    }
    return true;
}

void solveSudoku(vector<vector<int>>& sudoku)
{
	solve(sudoku);
}


// T.C. : O(9^m), where m is no empty cells
// S.C. : O(1)