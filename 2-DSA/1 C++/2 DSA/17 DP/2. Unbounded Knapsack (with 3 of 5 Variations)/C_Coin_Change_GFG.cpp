/*
Coin_Change_GFG
OR Coin change problem_ Maximum number of ways

Given a value N, find the number of ways to make change for N cents, if we have infinite supply of each of S = { S1, S2, .. , SM } valued coins.

    Example 1:
    Input : n = 4 , m = 3, S[] = {1,2,3}
    Output: 4
    Explanation: Four Possible ways are : {1,1,1,1},{1,1,2},{2,2},{1,3}.

Expected Time Complexity: O(m*n).
Expected Auxiliary Space: O(n).
*/

// Bottom-UP Solution
class Solution {
  public:
    long long int count(int S[], int m, int n) {

        long long int dp[m+1][n+1];
        
        // Initialisation    
        for(int i=0; i<m+1; i++)
            for(int j=0; j<n+1; j++)
                {
                    if(i==0) dp[i][j] = 0;
                    if(j==0) dp[i][j] = 1;
                }
        
        // Choice Diagram
        for(int i=1; i<m+1; i++)
            for(int j=1; j<n+1; j++)
            {
                if(S[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = dp[i][j-S[i-1]] + dp[i-1][j];
            }
        return dp[m][n];
    }
};