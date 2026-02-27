/*
Print_shortest_common_Supersequence_Leetcode_1092

Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.

A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.

    Example 1:

    Input: str1 = "abac", str2 = "cab"
    Output: "cabac"
    Explanation: 
    str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
    str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
    The answer provided is the shortest such string that satisfies these properties.
*/

// T.C. : O(n^2)
// S.C. : O(n^2)

/* Approach : 
    1. Make DP table using LCS
    2. Print LCS algo, with changes, like we have to print the element even if letter is not common
    3. Print remaining letter of other string, even if one of the string ends
*/


class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        
        int n = str1.length();
        int m = str2.length();
        int dp[n+1][m+1];
        
        // Step -1 :

        // Initialisation
        for(int i=0; i<m+1; i++)    // 1st row
            dp[0][i] = 0;
        for(int j=0; j<n+1; j++)    // 1st column
            dp[j][0] = 0;
        
        // Choice diagram
        for(int i=1; i<n+1; i++)
            for(int j=1; j<m+1; j++)
            {
                if(str1[i-1] == str2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        
        // dp[m][n] stores LCS length
        // Shortest Common SuperSequence length : (m + n- LCS)
        
        // Step - 2 : 
        string ans = "";
        int i=n, j=m;
        while(i>0 && j>0)
        {
            if(str1[i-1] == str2[j-1])
            {
                ans.push_back(str1[i-1]);
                i--;
                j--;
            }
            else
            {
                if(dp[i][j-1] > dp[i-1][j])
                {
                    ans.push_back(str2[j-1]);
                    j--;
                }
                else
                {
                    ans.push_back(str1[i-1]);
                    i--;
                }
            }
            
        }

        // Step - 3 : 

        while(i > 0)
        {
            ans.push_back(str1[i-1]);
            i--;
        }
        while(j > 0)
        {
            ans.push_back(str2[j-1]);
            j--;
        }
        
        reverse(ans.begin(), ans.end());
        return ans;
        
    }
};