/*
Target_Sum_Leetcode_494

You are given an integer array nums and an integer target.
You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.

    Example 1:

    Input: nums = [1,1,1,1,1], target = 3
    Output: 5
    Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
    -1 + 1 + 1 + 1 + 1 = 3
    +1 - 1 + 1 + 1 + 1 = 3
    +1 + 1 - 1 + 1 + 1 = 3
    +1 + 1 + 1 - 1 + 1 = 3
    +1 + 1 + 1 + 1 - 1 = 3
*/


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) 
    {
        // Approach is exactly same as count the no of subset with given differnce
        
        int sum = 0;
        for(int i:nums)
            sum += i;
        
        // (sum+d should be even to divide it in two parts)  
        // sum + target > 0, so must check is there summation > 0
        if((sum + target) % 2 == 1 || target > sum || sum + target < 0) 
            return 0;
        
        int s1 = (sum + target)/2;
        int n = nums.size();
        int dp[n+1][s1+1];
        
        // Initialisation
        dp[0][0] = 1;
        //for(int i=1; i<n+1; i++)
          //  dp[i][0] = 0;
        for(int i=1; i<s1+1; i++)
            dp[0][i] = 0;
        
        // Choice Diagram
        for(int i=1; i<n+1; i++)
            for(int j=0; j<s1+1; j++)
            {
                if(nums[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = dp[i-1][j-nums[i-1]] + dp[i-1][j];
            }
        return dp[n][s1];
    }
};