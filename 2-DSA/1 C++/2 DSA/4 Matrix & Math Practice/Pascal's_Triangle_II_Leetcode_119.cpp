/*
Pascal's_Triangle_II_Leetcode_119

Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

    Example 1:
    Input: rowIndex = 3
    Output: [1,3,3,1]

    Example 2:
    Input: rowIndex = 0
    Output: [1]

    Example 3:
    Input: rowIndex = 1
    Output: [1,1]

Follow up: Could you optimize your algorithm to use only O(rowIndex) extra space?
*/


// Approach-1 : Creating a 2-D matrix and Calculating
// Time: O(N^2)
// Space : O(N^2)

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        
        vector<vector<int>> ans(34, vector<int> (34, 1) );
        int row = 2;
        
        for(int i=2; i <= rowIndex; i++)
        {
            for(int j=1; j < row; j++)
                ans[i][j] = ans[i-1][j-1] + ans[i-1][j];
            
            // Incresing row size
            row++;
        }
        
        vector<int> res;
        for(int i=0; i< rowIndex+1; i++)
            res.push_back(ans[rowIndex][i]);
        
        return res;
    }
};


// Approach-2 : Using only 1-D vector, and updating it again and again
// Time: O(N^2)
// Space : O(N) or O(rowIndex)

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        
        vector<int> ans(rowIndex+1, 1);
        
        for(int i=1; i < rowIndex; i++)
            for(int j=i; j>0; j--)
                ans[j] = ans[j] + ans[j-1];
        
        return ans;
    }
};