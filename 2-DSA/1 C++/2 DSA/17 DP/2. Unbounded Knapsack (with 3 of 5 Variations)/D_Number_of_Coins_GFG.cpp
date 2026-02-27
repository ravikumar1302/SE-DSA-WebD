/*
Number_of_Coins_GFG
OR Coin change problem: Minimum number of coins

Given a value V and array coins[] of size M, the task is to make the change for V cents, given that you have an infinite supply of each of coins{coins1, coins2, ..., coinsm} valued coins. Find the minimum number of coins to make the change. If not possible to make change then return -1.

    Example 1:
    Input: V = 30, M = 3, coins[] = {25, 10, 5}
    Output: 2
    Explanation: Use one 25 cent coin and one 5 cent coin

Expected Time Complexity: O(V*M)
Expected Auxiliary Space: O(V)
*/

// This is also similar to the coins change max no of ways, But in this we need to consider the initialization part a bit carefully
    // 1st condition : If we have no coins and sum!=0 then we need infinite coins(theoratically assuming).
    // 2nd condition : If we have only one coin x then the minimum coins required to make sum will have two conditions
        // 2.a : if sum%x == 0 then min no of coins = sum/x
        // 2.b : if sum%x != 0 then min no of coins will be infinte coins (theoratically assuming)


class Solution{

	public:
	int minCoins(int coins[], int M, int V) 
	{ 
	    int dp[M+1][V+1];
        
        // Initialisation
        for(int i=0; i<M+1; i++)
	        dp[i][0]=0;
	    
	    for(int j=1; j<V+1; j++)
	        dp[0][j]=INT_MAX-1;
        
        // row 1
        for(int j=1; j<V+1; j++)
        {
            if(j%coins[0] == 0)
                dp[1][j] = j/coins[0];
            else
                dp[1][j] = INT_MAX-1;
        }
        
        // Choice Diagram
        for(int i=2; i<M+1; i++)
            for(int j=1; j<V+1; j++)
            {
                if(coins[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = min( 1 + dp[i][j-coins[i-1]], 0 + dp[i-1][j]);
            }
        
        // Return ans
        if(dp[M][V] == INT_MAX-1)
            return -1;
        else
            return dp[M][V];
	}   
};