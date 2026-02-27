/*
Median_in_a_row_wise_sorted_Matrix_GFG
Given a row wise sorted matrix of size RxC where R and C are always odd, find the median of the matrix.

    Input:
    R = 3, C = 3
    M = [[1, 3, 5], 
        [2, 6, 9], 
        [3, 6, 9]]

    Output: 5

    Explanation:
    Sorting matrix elements gives us {1,2,3,3,5,6,6,9,9}. Hence, 5 is median. 
*/

class Solution{   
public:
    int median(vector<vector<int>> &matrix, int r, int c){
        int ans;
        vector<int> ans1;
        for(int i=0; i<r;i++)
        {
            for(int j=0;j<c;j++)
                ans1.push_back(matrix[i][j]);
        }
        sort(ans1.begin(),ans1.end());
        ans=ans1[(r*c)/2];
        return ans;
        
    }
};