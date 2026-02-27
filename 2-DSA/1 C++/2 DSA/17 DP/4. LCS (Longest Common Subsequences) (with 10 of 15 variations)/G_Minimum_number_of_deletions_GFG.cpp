/*
Minimum_number_of_deletions_GFG
OR Minimum number of deletions to make a string palindrome

Given a string 'str' of size ‘n’. The task is to remove or delete the minimum number of characters from the string so that the resultant string is a palindrome. 
Find the minimum numbers of characters we need to remove.
Note: The order of characters should be maintained.

    Example 1:
    Input: n = 7, str = "aebcbda"
    Output: 2
    Explanation: We'll remove 'e' and 'd' and the string become "abcba".

Expected Time Complexity: O(|str|2)
Expected Auxiliary Space: O(|str|2)
*/

// Appraoch : length - LCS

int minDeletions(string str, int n) 
{ 
        string B = str;
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
                if(str[i-1] == B[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                    
            }
        
        // dp[n][n] represents the length of string that is palindrome, so total length - dp[n][n] are the letters we need to remove
        return (n - dp[n][n]);    
} 