/*
Flood_fill_Algorithm_GFG 

An image is represented by a 2-D array of integers, each integer representing the pixel value of the image.
Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.
To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.

    Example 1:
    Input: image = {{1,1,1},{1,1,0},{1,0,1}}, sr = 1, sc = 1, newColor = 2.
    Output: {{2,2,2},{2,2,0},{2,0,1}}
    Explanation: From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected by a path of the same color as the starting pixel are colored with the new color.Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.

Expected Time Compelxity: O(n*m)
Expected Space Complexity: O(n*m)
 
*/

class Solution {
public:

    void dfs(vector<vector<int>>& ans, vector<vector<int>>& image, int row, int col, int newColor, int oldcolor, int delrow[], int delcol[])
    {
        ans[row][col] = newColor;
        int n = image.size();
        int m = image[0].size();
        
        for(int i=0; i<4; i++)
        {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];
            
            if( (nrow >= 0 && nrow < n) && (ncol >= 0 && ncol < m) && image[nrow][ncol] == oldcolor && ans[nrow][ncol] != newColor )
                dfs(ans, image, nrow, ncol, newColor, oldcolor, delrow, delcol);
        }
        
    }
    
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        
        int n = image.size();
        int m = image[0].size();
        int oldcolor = image[sr][sc];
        
        // Copying given matrix to ans
        vector<vector<int>> ans = image;
        
        // write top, bottom, left, right coordinates
        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, 1, 0, -1};
        
        dfs(ans, image, sr, sc, newColor, oldcolor, delrow, delcol);
        
        return ans;
    }
};


// Time : O(n*m) + O(4*n*m) = O(n*m)
// Space : O(n*m) + O(n*m) = O(n*m), for ans and stack space