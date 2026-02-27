/*
Count_Ways_To _Reach_N-th_Stairs_Codestudio

You have been given a number of stairs. Initially, you are at the 0th stair, and you need to reach the Nth stair. 
Each time you can either climb one step or two steps. 
You are supposed to return the number of distinct ways in which you can climb from the 0th step to Nth step.

    Example :
    N=3
    We can climb one step at a time i.e. {(0, 1) ,(1, 2),(2,3)} or we can climb the first two-step and then one step i.e. {(0,2),(1, 3)} or we can climb first one step and then two step i.e. {(0,1), (1,3)}.
*/

// Method-1 : Normal Recursion : TLE

#include <bits/stdc++.h> 
int countDistinctWays(int nStairs) {
    
    // Base Cases
    if(nStairs < 0)  return 0;
    if(nStairs == 0)    return 1;
    
    // Calculation & Recursive call
    int ans = countDistinctWays(nStairs -1) + countDistinctWays(nStairs -2);
    
    return ans;
}

// Method-2 : Memoization

#include <bits/stdc++.h> 
int mod = 1e9 + 7;
int solve(int n, vector<int> &dp)
{
    // Base Cases
    if(n == 0 || n == 1)    
        dp[n] = 1;
    if(dp[n] != -1)
        return dp[n];
    
    // Calculation & Recursive call
    int ans = (solve(n -1, dp) + solve(n -2, dp))%mod;
    
    return dp[n] = ans;
}

int countDistinctWays(int nStairs) {
    
    vector<int> dp(nStairs +1, -1);
    return solve(nStairs, dp);
}



// Method-3 : Bottom-Up

#include <bits/stdc++.h> 
int mod = 1e9 + 7;

int countDistinctWays(int nStairs) {
    
    vector<int> dp(nStairs +1, -1);
    dp[0] = dp[1] = 1;
    
    for(int i=2; i<= nStairs; i++)
        dp[i] = (dp[i-1] + dp[i-2])%mod;
    
    return dp[nStairs];
}