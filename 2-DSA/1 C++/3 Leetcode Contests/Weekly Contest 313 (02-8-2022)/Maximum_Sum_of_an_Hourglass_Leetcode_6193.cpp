/*
Maximum_Sum_of_an_Hourglass_Leetcode_6193

You are given an m x n integer matrix grid.
We define an hourglass as a part of the matrix with the following form:
Return the maximum sum of the elements of an hourglass.

Note that an hourglass cannot be rotated and must be entirely contained within the matrix.

    Example 1:
    Input: grid = [[6,2,1,3],[4,2,1,5],[9,2,8,7],[4,1,2,9]]
    Output: 30
    Explanation: The cells shown above represent the hourglass with the maximum sum: 6 + 2 + 1 + 2 + 9 + 2 + 8 = 30.
*/

//Solution Help : https://www.geeksforgeeks.org/maximum-sum-hour-glass-matrix/


class Solution {
public:
    int maxSum(vector<vector<int>>& grid) {
    
    int R = grid.size();
    int C = grid[0].size();
    int max_sum = INT_MIN;
    for (int i=0; i<R-2; i++)
    {
        for (int j=0; j<C-2; j++)
        {
            
            int sum = (grid[i][j]+grid[i][j+1]+grid[i][j+2]) + (grid[i+1][j+1]) + (grid[i+2][j]+grid[i+2][j+1]+grid[i+2][j+2]);
 
            max_sum = max(max_sum, sum);
        }
    }
        
    return max_sum;
    }
};