/*
Longest_Common_Substring_GFG

Given two strings. The task is to find the length of the longest common substring.

    Example 1:

    Input: S1 = "ABCDGH", S2 = "ACDGHR"
    Output: 4
    Explanation: The longest common substring is "CDGH" which has length 4.

Expected Time Complexity: O(n*m).
Expected Auxiliary Space: O(n*m).
*/


class Solution{
    public:
    
    int longestCommonSubstr (string S1, string S2, int n, int m)
    {
         int dp[n+1][m+1];
         int ans = 0;
         
         // Initialisation
         for(int i=0; i<n+1; i++)   // 1st column
            dp[i][0] = 0;
        for(int j=0; j<m+1; j++)    // 1st row
            dp[0][j] = 0;
         
         // Choice Diagram
         for(int i=1; i<n+1; i++)
            for(int j=1; j<m+1; j++)
            {
                if(S1[i-1] == S2[j-1])
                {
                    dp[i][j] = 1 + dp[i-1][j-1];
                    ans = max(ans, dp[i][j]);
                }
                else
                    dp[i][j] = 0;   // If don't matches, then start from 0
            }
            
        return ans;
    }
};