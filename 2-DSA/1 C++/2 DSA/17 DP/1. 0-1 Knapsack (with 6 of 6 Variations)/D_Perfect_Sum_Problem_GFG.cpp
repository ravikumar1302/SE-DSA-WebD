/*
Perfect_Sum_Problem_GFG
OR Count_of_Subsets_Sum_with_a_Given_Sum

Given an array arr[] of non-negative integers and an integer sum, the task is to count all subsets of the given array with a sum equal to a given sum.

Note: Answer can be very large, so, output answer modulo 109+7

    Example 1:
    Input: N = 6, arr[] = {2, 3, 5, 6, 8, 10}, sum = 10
    Output: 3
    Explanation: {2, 3, 5}, {2, 8}, {10}

Expected Time Complexity: O(N*sum)
Expected Auxiliary Space: O(N*sum)
*/

// Bottom Approach
class Solution
{
	public:
    
	int perfectSum(int arr[], int n, int sum)
	{
        int dp[n+1][sum+1];
        int mod = 1000000007;
        
        // Initialisation
        dp[0][0] = 1;
        //for(int i=0; i<n+1; i++)
            for(int j=1; j<sum+1; j++)
            {
                //if(i==0)    dp[i][j]=0;
                //if(j==0)    dp[i][j]=1;
                dp[0][j] = 0;
            }
        
        // Choice Diagram
        for(int i=1; i<n+1; i++)
            for(int j=0; j<sum+1; j++)
            {
                if(arr[i-1] > j)
                    dp[i][j] = (dp[i-1][j])%mod;
                else
                    dp[i][j] = (dp[i-1][j-arr[i-1]] + dp[i-1][j])%mod;
            }
        return dp[n][sum];
	}
};


// Memoized Approach

class Solution{

	public:
    int mod = pow(10, 9) + 7;
    int solve(int arr[], int n, int sum, vector<vector<int>> &dp)
    {
        // Base cases
	    if(n==0 && sum==0) return 1;
        if(sum==0) return 1;
        if(n==0) return 0;
	    
	    if(dp[n][sum] != -1)
	        return dp[n][sum];
	   
	   // Choice Diagram
	   if(arr[n-1] > sum)
	        return dp[n][sum] = ( solve(arr, n-1, sum, dp) )%mod;
	   else
	        return dp[n][sum] = ( solve(arr, n-1, sum, dp) + solve(arr, n-1, sum - arr[n-1], dp) )%mod;
    }
    
	int perfectSum(int arr[], int n, int sum)
	{
	    // Memoized Approach
	    vector<vector<int>> dp (n+1, vector<int> (sum+1, -1));
	    sort(arr, arr+n, greater<int> ());
	    return solve(arr, n, sum, dp);
	    
	}
	  
};


// Recursive Approach 
class Solution{

	public:
	//int dp[n+1][sum+1];
    int mod = pow(10, 9) + 7;
    int solve(int arr[], int n, int sum)
    {
        // Base cases
	    if(n==0 && sum==0) return 1;
        if(sum==0) return 1;
        if(n==0) return 0;
	    
	   
	   // Choice Diagram
	   if(arr[n-1] > sum)
	        return ( solve(arr, n-1, sum) )%mod;
	   else
	        return ( solve(arr, n-1, sum) + solve(arr, n-1, sum - arr[n-1]) )%mod;
    }
    
	int perfectSum(int arr[], int n, int sum)
	{

	    sort(arr, arr+n, greater<int> ());
	    return solve(arr, n, sum);
	    
	}
	  
};