/*
Spiral_matrix_Leetcode_54

Given an m x n matrix, return all elements of the matrix in spiral order.

    Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
    Output: [1,2,3,6,9,8,7,4,5]
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
        vector<int> ans;
        int row = matrix.size();
        int col = matrix[0].size();
        
        int count = 0;
        int total = row*col;
        
        //index initialization
        int startrow=0;
        int startcol=0;
        int endrow=row-1;
        int endcol=col-1;
        
        while(count < total)
        {
            //print start row
            for(int index = startcol; count < total && index <= endcol; index++)
            {
                ans.push_back(matrix[startrow][index]);
                count++;
            }
            startrow++;
            
            //print end col
            for(int index=startrow; count<total && index<=endrow;index++)
            {
                ans.push_back(matrix[index][endcol]);
                count++;
            }
            endcol--;
            
            //print end row
            for(int index=endcol; count<total && index>=startcol;index--)
            {
                ans.push_back(matrix[endrow][index]);
                count++;
            }
            endrow--;
            
            //print start col
            for(int index=endrow; count<total && index>=startrow;index--)
            {
                ans.push_back(matrix[index][startcol]);
                count++;
            }
            startcol++;
        }
                
        return ans;
    }
};

//Time Coplexity: O(n*m) as every element is traversed only once