/*
Subset_Sum_Problem_GFG

Given an array of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum. 
    Example 1:
    Input:
    N = 6
    arr[] = {3, 34, 4, 12, 5, 2}
    sum = 9
    Output: 1 
    Explanation: Here there exists a subset with
    sum = 9, 4+3+2 = 9.
    
Expected Time Complexity: O(sum*N)
Expected Auxiliary Space: O(sum*N)
*/

// Bottom-Up Approach

class Solution{   
public:
    bool isSubsetSum(vector<int>arr, int sum)
    {
        int n=arr.size();
        bool dp[n+1][sum+1];
        
        // Initialisation
        for(int i=0; i<n+1; i++)
            for(int j=0; j<sum+1; j++)
            {
                if(i==0) dp[i][j] = false;
                if(j==0) dp[i][j] = true;
            }
        
        // Choice Diagram
        for(int i=1; i<n+1; i++)
            for(int j=1; j<sum+1; j++)
            {
                if(arr[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = dp[i-1][j-arr[i-1]] || dp[i-1][j];
            }
        
        return dp[n][sum];
    }
};

// Memoization Approach
// Memoized code not working on GFG

// Recursive Approach : TLE
class Solution{   
public:
    
    bool solve(vector<int>&arr, int sum, int n)
    {
        // Base cases
        if(sum == 0)
            return true;
        if(n == 0)
            return false;
        
        // Choice diagram
        if(arr[n-1] > sum)
            solve(arr, sum, n-1);
        
            solve(arr, sum, n-1) || solve(arr, sum-arr[n-1], n-1);
    }
    bool isSubsetSum(vector<int>arr, int sum){
        
        // Recursive solution
        int n = arr.size();
        
        return solve(arr, sum, n);
        
    }
};