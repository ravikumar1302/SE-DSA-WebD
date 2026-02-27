/*
Is_Subsequence_Leetcode_392
OR Sequence Pattern Matching

Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true

Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109, and you want to check one by one to see if t has its subsequence. 
In this scenario, how would you change your code?
*/

// Approach : dp[n][w] = length of LCS, it should be equal to s, smaller string


class Solution {
public:
    bool isSubsequence(string s, string t) {
        
        int n = s.length();
        int m = t.length();
        
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
                if(s[i-1] == t[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max( dp[i-1][j], dp[i][j-1] );
            }
        
        // dp[n][w] = length of LCS, it should be equal to s, smaller string
        if(dp[n][m] == n)
            return true;
        else
            false;
        
        return false;
    }
};