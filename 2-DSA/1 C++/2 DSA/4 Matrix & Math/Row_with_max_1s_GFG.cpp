/*
Row_with_max_1s_GFG
Given a boolean 2D array of n x m dimensions where each row is sorted. Find the 0-based index of the first row that has the maximum number of 1's.

    Example 1:
    Input: N = 4 , M = 4
    Arr[][] = {{0, 1, 1, 1},
            {0, 0, 1, 1},
            {1, 1, 1, 1},
            {0, 0, 0, 0}}
    Output: 2
    Explanation: Row 2 contains 4 1's (0-based indexing)
*/

class Solution{
public:
	int rowWithMax1s(vector<vector<int> > arr, int n, int m) {
	    
	    int col = m-1;
        int rowindex = -1;
        for (size_t i = 0; i < n; i++) {
            while (arr[i][col]) {
                col--;
                rowindex = i;
            }
        }
        return rowindex;
	}

};