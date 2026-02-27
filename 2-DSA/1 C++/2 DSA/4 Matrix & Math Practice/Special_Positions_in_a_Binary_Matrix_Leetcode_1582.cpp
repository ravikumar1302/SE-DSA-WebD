/*
Special_Positions_in_a_Binary_Matrix_Leetcode_1582

Given an m x n binary matrix mat, return the number of special positions in mat.

A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).

        Example 1
        Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
        Output: 1
        Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.

        Example 2:
        Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
        Output: 3
        Explanation: (0, 0), (1, 1) and (2, 2) are special positions.


Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 100
mat[i][j] is either 0 or 1.

*/
class Solution
{
public:
    int numSpecial(vector<vector<int>> &mat)
    {

        // Time = O(n*n)

        int m = mat.size();    // no of rows
        int n = mat[0].size(); // no of columns
        int ans = 0;

        // count '1' in each row and column
        vector<int> rowCount(m, 0); // Initialize row count vector with 0s
        vector<int> colCount(n, 0);

        for (int row = 0; row < m; row++)
            for (int col = 0; col < n; col++)
                if (mat[row][col] == 1)
                {
                    rowCount[row]++; // Increment row count when '1' is encountered in the row
                    colCount[col]++; // Increment column count when '1' is encountered in the column
                }

        // Checking foe "special" elements
        for (int row = 0; row < m; row++)
            for (int col = 0; col < n; col++)
                if (mat[row][col] == 1)
                    if (rowCount[row] == 1 && colCount[col] == 1) // If the row and column containing this '1' have exactly one '1' (i.e., the element is "special")
                        ans++;
        return ans;
    }
};