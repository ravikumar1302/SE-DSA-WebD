/*
Palindromic_Partitioning_GFG

Given a string str, a partitioning of the string is a palindrome partitioning if every sub-string of the partition is a palindrome. Determine the fewest cuts needed for palindrome partitioning of the given string.

    Example 1:
    Input: str = "ababbbabbababa"
    Output: 3
    Explaination: After 3 partitioning substrings are "a", "babbbab", "b", "ababa".

    Example 2:
    Input: str = "aaabba"
    Output: 1
    Explaination: The substrings after 1 partitioning are "aa" and "abba".

Expected Time Complexity: O(n*n) [n is the length of the string str]
Expected Auxiliary Space: O(n*n)
*/


// Given a string, a partitioning of the string is a palindrome partitioning if every substring of the partition is a palindrome. 
// Example : “aba|b|bbabb|a|b|aba” is a palindrome partitioning of “ababbbabbababa”.

// Recursive 
// Time : Exponential
// Giving TLE after some cases

class Solution{
public:
    // Recursive Solution
    
    bool isPlanidrome(string s, int i, int j)
    {
        while(i<=j)
        {
            if(s[i] != s[j])
                return false;
            else
            {
                i++;
                j--;
            }
        }
        return true;
    }
    
    int solve(string str, int i, int j)
    {
        // Step 1 : Find i, j
        // Step 2 : Find right base case
        if(i >= j)
            return 0;
        if(isPlanidrome(str, i, j))
            return 0;
        
        // Step 3 : Find K-Loop Sequence (move k from i to j)
        int mini = INT_MAX;
        for(int k = i; k <= j-1; k++)
        {
            int temp = solve(str, i, k) + solve(str, k+1, j) + 1;
    
            // Step 4 : Calculate ans from temporary ans
            mini = min(mini, temp);
        }
    
        return mini; 
    }
    
    int palindromicPartition(string str)
    {
        int i = 0;
        int j = str.length()-1;
        
        return solve(str, i, j);
    }
};



/************************************************************************************/
// Memoization : Working and passing all test, Here I passed the string with refrence, without this TLE will come
// Time : O(N^3)
// Space : O(N^2) ignoring recursion stack space

class Solution{
public:
    int dp[501][501];
    
    bool isPlanidrome(string &s, int i, int j)
    {
        if(i==j)    return true;    // Single character
        if(i>j)     return true;    // Empty string
        while(i<j)
        {
            if(s[i] != s[j])
                return false;
            else
            {
                i++;
                j--;
            }
        }
        return true;
    }
    
    int solve(string &str, int i, int j)
    {
        // Step 1 : Find i, j
        // Step 2 : Find right base case
        if(i >= j)
            return 0;
        if(dp[i][j] != -1)
            return dp[i][j];
        if(isPlanidrome(str, i, j))
            return 0;
        
        
        // Step 3 : Find K-Loop Sequence (move k from i to j)
        int mini = INT_MAX;
        for(int k = i; k <= j-1; k++)
        {
            int temp = solve(str, i, k) + solve(str, k+1, j) + 1;
    
            // Step 4 : Calculate ans from temporary ans
            mini = min(mini, temp);

        }
    
        return dp[i][j] = mini; 
    }
    
    int palindromicPartition(string str)
    {
        int i = 0;
        int j = str.length()-1;
        memset(dp, -1, sizeof(dp));
        
        return solve(str, i, j);
    }
};


/************************************************************************************/
// Memoization : More Optimized, this works without passing the string by refrence
// Time : O(N^3)
// Space : O(N^2) ignoring recursion stack space


class Solution{
public:
    int dp[501][501];
    
    bool isPlanidrome(string s, int i, int j)
    {
        while(i<=j)
        {
            if(s[i] != s[j])
                return false;
            else
            {
                i++;
                j--;
            }
        }
        return true;
    }
    
    int solve(string str, int i, int j)
    {
        // Step 1 : Find i, j
        // Step 2 : Find right base case
        if(i >= j)
            return 0;
        if(dp[i][j] != -1)
            return dp[i][j];
        if(isPlanidrome(str, i, j))
            return 0;
        
        
        // Step 3 : Find K-Loop Sequence (move k from i to j)
        int mini = INT_MAX;
        for(int k = i; k <= j-1; k++)
        {
            int left = INT_MAX, right = INT_MAX;
            
            if(dp[i][k] != -1)
                left = dp[i][k];
            else{
                left = solve(str, i, k);
                dp[i][k] = left;
            }
            if(dp[k+1][j] != -1)
                right = dp[k+1][j];
            else{
                right = solve(str, k+1, j);
                dp[k+1][j] = right;
            }
            
            int temp = left + right + 1;
    
            // Step 4 : Calculate ans from temporary ans
            mini = min(mini, temp);

        }
    
        return dp[i][j] = mini; 
    }
    
    int palindromicPartition(string str)
    {
        int i = 0;
        int j = str.length()-1;
        memset(dp, -1, sizeof(dp));
        
        return solve(str, i, j);
    }
};