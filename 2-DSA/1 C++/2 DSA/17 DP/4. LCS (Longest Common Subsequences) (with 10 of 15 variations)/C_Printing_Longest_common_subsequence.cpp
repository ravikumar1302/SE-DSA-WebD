/*
Printing_Longest_common_subsequence

Given two sequences, print the longest subsequence present in both of them.

Example:
LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” (of length 3) 

*/


// 1. DP
// T.C. : O(mn)
// S.C. : O(mn)


class Solution 
{
public:
    int longestCommonSubsequence(string text1, string text2) 
    {
        // DP Solution
        
        int n = text1.length();
        int m = text2.length();
        
        int dp[n+1][m+1];
        // Initialisation
        for(int i=0; i<n+1; i++)    // 1st column
            dp[i][0] = 0;
        for(int j=0; j<m+1; j++)    // 1st row
            dp[0][j] = 0;
        
        // Choice Diagram
        for(int i=1; i<n+1; i++)
            for(int j=1; j<m+1; j++)
            {
                if(text1[i-1] == text2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max( dp[i-1][j], dp[i][j-1] );
            }
        
        
        // Now, Using DP table, To print the LCS, 
        string ans = "";

        int i=n, j=m;
        while(i>0 && j>0)
        {
            if(text1[i-1] == text2[j-1])
            {
                ans.push_back(text1.[i-1]);
                i--;
                j--;
            }
            else
            {
                if(dp[i][j-1] > dp[i-1][j])
                    j--;
                else
                    i--;
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;  
    }
};