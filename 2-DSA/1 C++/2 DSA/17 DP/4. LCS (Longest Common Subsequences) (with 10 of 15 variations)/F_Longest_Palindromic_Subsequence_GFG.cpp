/*
Longest_Palindromic_Subsequence_GFG

Given a String, find the longest palindromic subsequence.

    Example 1:
    Input:
    S = "bbabcbcab"
    Output: 7
    Explanation: Subsequence "babcbab" is the longest subsequence which is also a palindrome.


Expected Time Complexity: O(|S|*|S|).
Expected Auxiliary Space: O(|S|*|S|).
*/

// Approach : LCS need 2 string, so make a string which is reverse of give string and find the LCS of them
class Solution{
  public:
    int longestPalinSubseq(string A) {
        int n = A.length();
        string B = A;
        reverse(B.begin(), B.end());
        
        int dp[n+1][n+1];
        
        // Initialization
        for(int i=0; i<n+1; i++)    // 1st column
            dp[0][i] = 0;
        for(int i=0; i<n+1; i++)    // 1st row
            dp[i][0] = 0;
            
        // Choice Diagram
        for(int i=1; i<n+1; i++)
            for(int j=1; j<n+1; j++)    
            {
                if(A[i-1] == B[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                    
            }
        return dp[n][n];
    }
};