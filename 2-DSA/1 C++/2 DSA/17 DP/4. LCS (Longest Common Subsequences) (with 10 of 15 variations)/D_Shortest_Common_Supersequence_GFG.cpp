/*
Shortest_Common_Supersequence_GFG

Given two strings X and Y of lengths m and n respectively, find the length of the smallest string which has both, X and Y as its sub-sequences.
Note: X and Y can have both uppercase and lowercase letters.

    Example 1

    Input:
    X = abcd, Y = xycd
    Output: 6
    Explanation: Shortest Common Supersequence would be abxycd which is of length 6 and has both the strings as its subsequences.

Expected Time Complexity: O(Length(X) * Length(Y)).
Expected Auxiliary Space: O(Length(X) * Length(Y)).
*/

// Approach : (m + n - LCS)
class Solution
{
    public:
    //Function to find length of shortest common supersequence of two strings.
    int shortestCommonSupersequence(string X, string Y, int m, int n)
    {
        int dp[m+1][n+1];
        
        // Initialisation
        for(int i=0; i<n+1; i++)    // 1st row
            dp[0][i] = 0;
        for(int j=0; j<m+1; j++)    // 1st column
            dp[j][0] = 0;
        
        // Choice diagram
        for(int i=1; i<m+1; i++)
            for(int j=1; j<n+1; j++)
            {
                if(X[i-1] == Y[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        
        // dp[m][n] stores LCS length
        // Shortest Common SuperSequence is (m-n- LCS)
        return (m + n - dp[m][n]);
    }
};