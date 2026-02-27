/*
Spiral_Matrix_II_Leetcode_59

Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.

    Example 1:
    Input: n = 3
    Output: [[1,2,3],[8,9,4],[7,6,5]]

    Example 2:
    Input: n = 1
    Output: [[1]]
*/


class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        
        int row = n;
        int col = n;
        int count = 1;
        int startingRow = 0;
        int startingCol = 0;
        int endingRow = row-1;
        int endingCol = col-1;
        
        vector<vector<int>> ans(n, vector<int> (n));
        
        while(startingRow <= endingRow && startingCol <= endingCol)
        {
            // starting row;
            for(int index = startingCol; index <= endingCol && startingRow <= endingRow; index++)
                ans[startingRow][index] = count++;
            startingRow++;

            // ending column
            for(int index = startingRow; index <= endingRow && startingCol <= endingCol; index++)
                ans[index][endingCol] = count++;
            endingCol--;

            // ending Row -- > right to left
            for(int index = endingCol; index >= startingCol && startingRow <= endingRow;index--) 
                ans[endingRow][index] = count++;
            endingRow--;
            
            // ending col -- > bottom to up
            for(int index = endingRow; index >= startingRow && startingCol <= endingCol;index--)
                ans[index][startingCol] = count++;
            startingCol++;
        }
        
        return ans;
    }
};