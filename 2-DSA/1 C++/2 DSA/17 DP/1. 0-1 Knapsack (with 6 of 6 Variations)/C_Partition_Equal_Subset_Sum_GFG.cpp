/*
Partition_Equal_Subset_Sum_GFG
Partition Equal Subset Sum Leetcode_416

Given an array arr[] of size N, check if it can be partitioned into two parts such that the sum of elements in both parts is the same.

    Example 1:
    Input: N = 4
    arr = {1, 5, 11, 5}
    Output: YES
    Explanation: 
    The two parts are {1, 5, 5} and {11}.

Expected Time Complexity: O(N*sum of elements)
Expected Auxiliary Space: O(N*sum of elements)

*/

// Bottom-UP Approach

class Solution{
public:
    int equalPartition(int N, int arr[])
    {
        int sum = 0;
        for(int i=0; i<N; i++)
            sum += arr[i];
        
        // if sum is odd, array can't be divided into 2 parts
        if(sum %2 == 1)
            return 0;
        
        sum = sum/2;
        bool dp[N+1][sum+1];
        
        // Initialisation
        for(int i=0; i<N+1; i++)
            for(int j=0; j<sum+1; j++)
            {
                if(i==0)    dp[i][j]=false;
                if(j==0)    dp[i][j]=true;
            }
        
        // Choice diagram
        for(int i=1; i<N+1; i++)
            for(int j=1; j<sum+1; j++)
            {
                if(arr[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = dp[i-1][j - arr[i-1]] || dp[i-1][j];
            }
        
        return dp[N][sum];
    }
};



// Memoization

class Solution {
public:
    int dp[200 + 1][20000 +1];
    bool solve(vector<int>& nums, int n, int sum)
    {
        // Base Cases
        if(sum == 0)
            return true;
        if(n == 0 && sum != 0)
            return false;
        if(dp[n][sum] != -1)
            return dp[n][sum];
        
        // Choice Diagram
        if(nums[n-1] > sum)
            return dp[n][sum] = solve(nums, n-1, sum);
        else
            return dp[n][sum] = solve(nums, n-1, sum) || solve(nums, n-1, sum - nums[n-1]);
            
    }
    
    bool canPartition(vector<int>& nums) {
        
        // Memoization Approach
        // Problem is similar to KnapSack, where we have to find a subset having a taget sum
        
        int n = nums.size();
        int sum = 0;
        for(int i=0; i<n; i++)
            sum = sum + nums[i];
        
        if(sum%2 != 0)      // if sum is odd, we cannot divide in two equal parts
            return false;
        memset(dp, -1, sizeof(dp));
        
        return solve(nums, n, sum/2);
    }
};


// Recursive : TLE

class Solution {
public:
    bool solve(vector<int>& nums, int n, int sum)
    {
        // Base Cases
        if(sum == 0)
            return true;
        if(n == 0 && sum != 0)
            return false;
        
        // Choice Diagram
        if(nums[n-1] > sum)
            return solve(nums, n-1, sum);
        else
            return solve(nums, n-1, sum) || solve(nums, n-1, sum - nums[n-1]);
            
    }
    
    bool canPartition(vector<int>& nums) {
        
        // Recursive Approach
        // Problem is similar to KnapSack, where we have to find a subset having a taget sum
        
        int n = nums.size();
        int sum = 0;
        for(int i=0; i<n; i++)
            sum = sum + nums[i];
        
        if(sum%2 != 0)      // if sum is odd, we cannot divide in two equal parts
            return false;
        
        return solve(nums, n, sum/2);
    }
}; 