/*
Coin_Change_Leetcode_322


You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

    Example 1:
    Input: coins = [1,2,5], amount = 11
    Output: 3
    Explanation: 11 = 5 + 5 + 1

    Example 2:
    Input: coins = [2], amount = 3
    Output: -1

    Example 3:
    Input: coins = [1], amount = 0
    Output: 0
*/

// Bottom-Up
// Time: O(n.m)
// Space: O(n.m)

class Solution {
public:
    int dp[12+1][10000 + 1];

    int coinChange(vector<int>& coins, int amount) {
        
        // Bottom-Up
        // Problem similar to Unbounded KnapSack
        
        int size = coins.size();
        // i representing size and j representing amount
        for(int i=0; i<size+1; i++)
            for(int j=0; j<amount+1; j++)
            {
                if(i == 0)  dp[0][j] = INT_MAX - 1;
                if(j == 0)  dp[i][0] = 0;   // First Column 
            }
        
        // Choice Diagram
        for(int i=1; i<size+1; i++)
            for(int j=1; j<amount+1; j++)
            {
                if(coins[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = min(0 + dp[i-1][j], 1 + dp[i][j - coins[i-1]]);
            }
        int ans =  dp[size][amount];
        
        if(ans == INT_MAX -1)
            return -1;
        else
            return ans;
    }
};



// Memoization 
// Time: O(n.m)
// Space: O(n.m)

class Solution {
public:
    int dp[12+1][10000 + 1];
    int solve(vector<int>& coins, int amount, int size)
    {
        // Base cases
        if(amount == 0)     
            return 0;
        if(amount < 0)       // If amount is less than 0, then no possible solution
            return INT_MAX -1;
        
        if(size <= 0)        // If there are np coins and amount > 0, then no solution exist
            return INT_MAX -1;
        
        // Checking Memoization table
        if(dp[size][amount] != -1)
            return dp[size][amount];
        
        int ans = -1;
        // Choice diagram : Including , Excluding
        if(coins[size - 1] > amount)
        {
            int not_taken = 0 +  solve(coins, amount, size-1);
            dp[size][amount] = ans = not_taken;
        }
        else
        {
            int taken = 1 + solve(coins, amount- coins[size-1], size) ;
            int not_taken = 0 + solve(coins, amount, size-1);
            dp[size][amount] = ans = min(taken, not_taken);
        }
        
        return dp[size][amount] = ans;
    }
    
    int coinChange(vector<int>& coins, int amount) {
        
        // Memoization
        // Problem similar to Unbounded KnapSack
        
        memset(dp, -1, sizeof(dp));
        sort(coins.begin(), coins.end());   // To return minimum no of coins, end elements will be bigger after sorting
        int size = coins.size();
        int ans = solve(coins, amount, size);
        
        if(ans == INT_MAX -1)
            return -1;
        else
            return ans;
    }
};



// Recursive Solution : TLE
// Time: O(2^n)
// Space: O(n),  for recursive calls

class Solution {
public:
    int solve(vector<int>& coins, int amount, int size)
    {
        // Base cases
        if(amount == 0)     
            return 0;
        if(amount < 0)       // If amount is less than 0, then no possible solution
            return INT_MAX -1;
        
        if(size <= 0)        // If there are np coins and amount > 0, then no solution exist
            return INT_MAX -1;
        
        int ans = -1;
        // Choice diagram : Including , Excluding
        if(coins[size - 1] > amount)
        {
            int not_taken = 0 +  solve(coins, amount, size-1);
            ans = not_taken;
        }
        else
        {
            int taken = 1 + solve(coins, amount- coins[size-1], size) ;
            int not_taken = 0 + solve(coins, amount, size-1);
            ans = min(taken, not_taken);
        }
        
        return ans;
    }
    
    int coinChange(vector<int>& coins, int amount) {
        
        // Recursive
        // Problem similar to Unbounded KnapSack
        
        sort(coins.begin(), coins.end());   // To return minimum no of coins, end elements will be bigger after sorting
        int size = coins.size();
        int ans = solve(coins, amount, size);
        
        if(ans == INT_MAX -1)
            return -1;
        else
            return ans;
    }
};