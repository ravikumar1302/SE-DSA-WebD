/*
Find_Minimum_Number_Of_Coins_Codestudio

Given a value V and array coins[] of size M, the task is to make the change for V cents, given that you have an infinite supply of each of coins{coins1, coins2, ..., coinsm} valued coins. 
Find the minimum number of coins to make the change. If not possible to make change then return -1.

    Example 1:
    Input: V = 30, M = 3, coins[] = {25, 10, 5}
    Output: 2
    Explanation: Use one 25 cent coin and one 5 cent coin
*/

// Time : O(V)
// Space : O(1)

int findMinimumCoins(int amount) 
{
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
    int M = 9;
    sort(coins, coins + M);
        
    int ans = -1;
    int count = 0;
    for(int i=M-1; i>=0; i--)
    {
        while(amount >= coins[i])
        {
            amount -= coins[i];
            count++;
        }
    }
    if(count > 0)
        ans = count;
    return ans;
}
