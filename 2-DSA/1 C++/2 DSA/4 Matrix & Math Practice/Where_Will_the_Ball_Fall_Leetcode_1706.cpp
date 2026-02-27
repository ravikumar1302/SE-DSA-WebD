/*
Where_Will_the_Ball_Fall_Leetcode_1706

You have a 2-D grid of size m x n representing a box, and you have n balls. The box is open on the top and bottom sides.

Each cell in the box has a diagonal board spanning two corners of the cell that can redirect a ball to the right or to the left.
    A board that redirects the ball to the right spans the top-left corner to the bottom-right corner and is represented in the grid as 1.
    A board that redirects the ball to the left spans the top-right corner to the bottom-left corner and is represented in the grid as -1.

We drop one ball at the top of each column of the box. Each ball can get stuck in the box or fall out of the bottom. A ball gets stuck if it hits a "V" shaped pattern between two boards or if a board redirects the ball into either wall of the box.

Return an array answer of size n where answer[i] is the column that the ball falls out of at the bottom after dropping the ball from the ith column at the top, or -1 if the ball gets stuck in the box.

    Example 1:
    Input: grid = [[1,1,1,-1,-1],[1,1,1,-1,-1],[-1,-1,-1,1,1],[1,1,1,1,-1],[-1,-1,-1,-1,-1]]
    Output: [1,-1,-1,-1,-1]
    Explanation: This example is shown in the photo.
    Ball b0 is dropped at column 0 and falls out of the box at column 1.
    Ball b1 is dropped at column 1 and will get stuck in the box between column 2 and 3 and row 1.
    Ball b2 is dropped at column 2 and will get stuck on the box between column 2 and 3 and row 0.
    Ball b3 is dropped at column 3 and will get stuck on the box between column 2 and 3 and row 0.
    Ball b4 is dropped at column 4 and will get stuck on the box between column 2 and 3 and row 1.

    Example 2:
    Input: grid = [[-1]]
    Output: [-1]
    Explanation: The ball gets stuck against the left wall.

    Example 3:
    Input: grid = [[1,1,1,1,1,1],[-1,-1,-1,-1,-1,-1],[1,1,1,1,1,1],[-1,-1,-1,-1,-1,-1]]
    Output: [0,1,2,3,4,-1]

*/


/* 
Approach-1 : 
Suppose there're total n columns, then there're total n balls, dropping from (0, j), j in range of [0, n). 
For each ball, it starts at position (row = 0, col = j). 
At current grid, grid[row][col], it will decide this ball's next position. 
If grid[row][col] == 1, this ball's next position will be (row+1, col+1) OR If grid[row][col] == -1, this ball's next position will be (row+1, col-1).

There're two situations where this ball cannot reach the last row:
    1. This ball stucks at the wall. which means this ball needs to go to (row+1, col+1), but col+1 >= n; or this ball needs to go  to (row+1, col-1), but col - 1 < 0.
    2, This ball stucks at V shape, which means this grid[row][col] == 1 and grid[row][col+1] == -1; Or grid[row][col] == -1 and grid[row][col-1] == 1.

If this ball stucks, push back -1 into ans and break the while loop; If this ball reaches the last row, push back current col into ans.
*/

// Time : O(N^2)


class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        
        int m = grid.size();
        int n = grid[0].size();
        vector<int> ans;
        
        for (int j = 0; j < n; j++) 
        {
            int row = 0, col = j;
            while (row < m) 
            {
                if (grid[row][col] == 1) 
                {
                    if (col+1 >= n || grid[row][col+1] == -1) 
                    {
                        ans.push_back(-1);
                        break;
                    }
                    col++;
                } 
                else if (grid[row][col] == -1) 
                {
                    if (col-1 < 0 || grid[row][col-1] == 1) 
                    {
                        ans.push_back(-1);
                        break;
                    }
                    col--;
                }
				row++;
              }   // While loop ends
            
            if (row == m) 
                ans.push_back(col);
          }   // for loop ends
        
          return ans;
    }
};


// Other Approaches to explore : Using DFS, Using Dynamic Programming