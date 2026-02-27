/*
Longest_Common_Subsequence_Leetcode_1143

Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

 
    Example 1:
    Input: text1 = "abcde", text2 = "ace" 
    Output: 3  
    Explanation: The longest common subsequence is "ace" and its length is 3.

*/

/***********************************************************************************************************************/

// 1. Recursive
// T.C. : Exponential
// TLE will come in some case


class Solution 
{
public:
    int LCS(string X, string Y, int n, int m)
    {
        // base case
        if(n == 0 || m == 0)
            return 0;
        
        // Choice Diagram
        if(X[n-1] == Y[m-1])
            return 1 + LCS(X, Y, n-1, m-1);
        else
            return max( LCS(X, Y, n-1, m), LCS(X, Y, n, m-1) );
    }
    
    int longestCommonSubsequence(string text1, string text2) 
    {
        // Recursive solution
        
        int n = text1.length();
        int m = text2.length();
        
        return LCS(text1, text2, n, m);
    }
};


/***********************************************************************************************************************/

// 2. Memoization : top-down
// T.C. : O(mn) ignoring recursion stack space
// It will also give TLE, But if you pass the string in LCS function by refrence, it will pass all the cases


class Solution 
{
public:
    int dp[1001][1001];
    int LCS(string X, string Y, int n, int m)
    {
        // base case
        if(n == 0 || m == 0)
            return 0;
        
        if(dp[n][m] != -1)
            return dp[n][m];
        
        // Choice Diagram
        if(X[n-1] == Y[m-1])
            return dp[n][m] = 1 + LCS(X, Y, n-1, m-1);
        else
            return dp[n][m] = max( LCS(X, Y, n-1, m), LCS(X, Y, n, m-1) );
    }
    
    int longestCommonSubsequence(string text1, string text2) 
    {
        // Memoization solution
        
        int n = text1.length();
        int m = text2.length();
        // vector< vector<int>> dp(n+1, vector<int>(m+1, -1));
        memset(dp, -1, sizeof(dp));
        
        return LCS(text1, text2, n, m);
    }
};


/***********************************************************************************************************************/

// 3. DP
// T.C. : O(mn)


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
        
        return dp[n][m];
    }
};

// Method -2 to initialize

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) 
    {
        // DP Solution
        
        int n = text1.length();
        int m = text2.length();
        
        int dp[n+1][m+1];
        /*
        // Initialisation
        for(int i=0; i<n+1; i++)    // 1st column
            dp[i][0] = 0;
        for(int j=0; j<m+1; j++)    // 1st row
            dp[0][j] = 0;
        */
       
        // Choice Diagram
        for(int i=0; i<n+1; i++)
            for(int j=0; j<m+1; j++)
            {
                if(i == 0 || j==0)  // Initialisation
                    dp[i][j] = 0;
                
                else if(text1[i-1] == text2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max( dp[i-1][j], dp[i][j-1] );
            }
        
        return dp[n][m];
    }
};