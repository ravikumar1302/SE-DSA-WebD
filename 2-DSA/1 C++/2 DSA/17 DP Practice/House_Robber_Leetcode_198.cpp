/*
House_Robber_Leetcode_198
Stickler Thief_GFG

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, 
the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

    Example 1:
    Input: nums = [1,2,3,1]
    Output: 4
    Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3). Total amount you can rob = 1 + 3 = 4.

    Example 2:
    Input: nums = [2,7,9,3,1]
    Output: 12
    Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).Total amount you can rob = 2 + 9 + 1 = 12.

Expected Time Complexity:O(N).
Expected Space Complexity:O(N).
*/

// Method-1

// Bottom-UP
// Time Complexcity : O (n)
// Space Complexcity : O(n)

class Solution {
public:
    
    int rob(vector<int>& nums) {
        
        // Bottom-Up 
        
        int size = nums.size();
        
        // Base cases
        if(size == 1)
            return nums[0];
        
        int dp[size+1];
        
        dp[0]=nums[0];
        dp[1]=max(nums[0],nums[1]);     // as we need i-2 value
        
        for(int i=2; i < size; i++)
            dp[i]=max(dp[i-1],dp[i-2]+nums[i]);
        
        return dp[size-1];

    }
};


// Memoization
// Time Complexcity : O (n)
// Space Complexcity : O(n)

class Solution {
public:
    
    int dp[100+1];
    int solve(vector<int>& nums, int index)
    {
        // Base cases
        if(index >= nums.size()) 
            return 0;
        if(dp[index] != -1)
            return dp[index];
        
        // Choice Diagram : either odd index or even index
        int even_index = nums[index] + solve(nums, index + 2);
        int odd_index =  solve(nums, index + 1);
        
        return dp[index] = max( odd_index, even_index);
    }
    
    int rob(vector<int>& nums) {
        
        // Memoization 
        
        memset(dp, -1, sizeof(dp));
        return solve(nums, 0);
    }
};



// Recursive Solution : TLE
// Time: O(2^n)
// Space: O(n),  for recursive calls

class Solution {
public:
    
    int solve(vector<int>& nums, int index)
    {
        // Base cases
        if(index >= nums.size()) 
            return 0;
        
        // Choice Diagram : either odd index or even index
        int even_index = nums[index] + solve(nums, index + 2);
        int odd_index =  solve(nums, index + 1);
        return max( odd_index, even_index);
    }
    
    int rob(vector<int>& nums) {
        
        return solve(nums, 0);
    }
};



/******************************************************************************/

// Method-2 : By Love Babbar


// Recursive : TLE
class Solution {
public:
    
    int solve(vector<int> &nums, int n)
    {
        if(n < 0)
            return 0;
        if(n == 0)      // If one sized array
            return nums[0];
        
        int include = solve(nums, n-2) + nums[n];
        int exclude = solve(nums, n-1) + 0;
        
        return max(include, exclude);
    }
    
    int rob(vector<int>& nums) {
        
        int n = nums.size();
        int ans = solve(nums, n-1);
        return ans;
    }
};


// Memoization
// Time : O(N)      // As we have visited every no
// Space : O(N) + O(N)
class Solution {
public:
    
    int dp[100+1];
    int solve(vector<int> &nums, int n)
    {
        if(n < 0)
            return 0;
        if(n == 0)      // If one sized array
            return nums[0];
        if(dp[n] != -1)
            return dp[n];
        
        int include = solve(nums, n-2) + nums[n];
        int exclude = solve(nums, n-1) + 0;
        
        return dp[n] = max(include, exclude);
    }
    
    int rob(vector<int>& nums) {
        
        int n = nums.size();
        memset(dp, -1, sizeof(dp));
        int ans = solve(nums, n-1);
        return ans;
    }
};


// Bottom-up
// Time : O(N)
// Space : O(N)

class Solution {
public:
    int rob(vector<int>& nums) {
        
        int n = nums.size();
        if(n==1)
            return nums[0];
        vector<int> dp(n,0);
        
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for(int i=2; i<n; i++)
        {
            int inc = dp[i-2] + nums[i];
            int excl = dp[i-1] + 0;
            
            dp[i] = max(inc, excl);
        }
        
        return dp[n-1];
    }
};



// Bottom- UP : Space Optimized
// Approach : as dp[i] is dependent on inc and excl and they depends on only last 2 element, so we need only two variables
// Time : O(N)
// Space : O(1)

class Solution {
public:
    
    int rob(vector<int>& nums) {
        
        int n = nums.size();
        if(n==1)
            return nums[0];
        
        int prev2 = 0;              // used in place of base condition, n < 0
        int prev1 =  nums[0];        // used in place of n==0 condition
        
        for(int i=1; i<n; i++)
        {
            int inc = prev2 + nums[i];          // in place of dp[i-2], use prev2
            int excl = prev1 + 0;             // in place of dp[i-1], use prev1
            
            int ans = max(inc, excl);
            
            // Now move the prev1 and prev2 ahead
            prev2 = prev1;
            prev1 = ans;
        }
        
        return prev1;
    }
};