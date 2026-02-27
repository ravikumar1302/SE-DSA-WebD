/*
Egg_Dropping_Puzzle_GFG

You are given N identical eggs and you have access to a K-floored building from 1 to K.
There exists a floor f where 0 <= f <= K such that any egg dropped at a floor higher than f will break, and any egg dropped at or below floor f will not break. 

There are few rules given below. 
    An egg that survives a fall can be used again.
    A broken egg must be discarded.
    The effect of a fall is the same for all eggs.
    If the egg doesn't break at a certain floor, it will not break at any floor below.
    If the eggs breaks at a certain floor, it will break at any floor above.

Return the minimum number of moves that you need to determine with certainty what the value of f is.

Example 1:
Input : N = 1, K = 2
Output : 2
Explanation: 
1. Drop the egg from floor 1. If it breaks, we know that f = 0.
2. Otherwise, drop the egg from floor 2. If it breaks, we know that f = 1.
3. If it does not break, then we know f = 2.
4. Hence, we need at minimum 2 moves to determine with certainty what the value of f is.

Expected Time Complexity : O(N*(K^2))
Expected Auxiliary Space: O(N*K)
*/


// Recursive
// Time : Exponential
// Space : O(1)
// TLE will occur

class Solution
{
    public:
    int solve(int n, int k)
    {
        // Base cases
        if(k == 0 || k == 1)    return k;   // zero or one floor
        if(n == 1)              return k;   // One egg only
        
        int mn = INT_MAX;
        
        for(int f=1; f<=k; f++)
        {
            int temp = 1 + max( solve(n-1, f-1), solve(n, k-f) );
            mn = min(mn, temp);
        }
        
        return mn;
    }
    
    int eggDrop(int n, int k) 
    {
        return solve(n, k);
    }
};


// Memoization
// Time : O(N*(K^2))
// Works fine and Passes all test cases

class Solution
{
    public:
    //Function to find minimum number of attempts needed in 
    //order to find the critical floor.
    
    int dp[201][201];
    int solve(int n, int k)
    {
        // Base cases
        if(k == 0 || k == 1)    return k;   // zero or one floor
        if(n == 1)              return k;   // One egg only
        
        if(dp[n][k] != -1)
            return dp[n][k];
        
        int mn = INT_MAX;
        
        for(int f=1; f<=k; f++)
        {
            int temp = 1 + max( solve(n-1, f-1), solve(n, k-f) );
            mn = min(mn, temp);
        }
        
        return dp[n][k] = mn;
    }
    
    int eggDrop(int n, int k) 
    {
        memset(dp, -1, sizeof(dp));
        return solve(n, k);
    }
};


// Memoization - Optimized

class Solution
{
    public:
    //Function to find minimum number of attempts needed in 
    //order to find the critical floor.
    
    int dp[201][201];
    int solve(int n, int k)
    {
        // Base cases
        if(k == 0 || k == 1)    return k;   // zero or one floor
        if(n == 1)              return k;   // One egg only
        
        if(dp[n][k] != -1)
            return dp[n][k];
        
        int mn = INT_MAX;
        int low = 0, high = 0;
        for(int f=1; f<=k; f++)
        {
            // int temp = 1 + max( solve(n-1, f-1), solve(n, k-f) );
            
            if(dp[n-1][f-1] != -1)
                low = dp[n-1][f-1];
            else{
                low = solve(n-1, f-1);
                dp[n-1][f-1] = low;
            }
            
            if(dp[n][k-f] != -1)
                high = dp[n][k-f];
            else{
                high = solve(n, k-f);
                dp[n][k-f] = high;
            }
            
            int temp = 1 + max(low, high);
            
            mn = min(mn, temp);
        }
        
        return dp[n][k] = mn;
    }
    
    int eggDrop(int n, int k) 
    {
        memset(dp, -1, sizeof(dp));
        return solve(n, k);
    }
};