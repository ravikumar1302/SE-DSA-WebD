/*
Minimum_sum_partition_GFG

Given an array arr of size N containing non-negative integers, the task is to divide it into two sets S1 and S2 such that the absolute difference between their sums is minimum and find the minimum difference

    Example 1:
    Input: N = 4, arr[] = {1, 6, 11, 5} 
    Output: 1
    Explanation: 
    Subset1 = {1, 5, 6}, sum of Subset1 = 12 
    Subset2 = {11}, sum of Subset2 = 11   

Expected Time Complexity: O(N*|sum of array elements|)
Expected Auxiliary Space: O(N*|sum of array elements|)

*/

// Bottom-Up approach (Tabulation Method)

class Solution
{
  public:
	int minDifference(int arr[], int n)  { 
	    
	    int sum=0;
	    for(int i=0; i<n; i++)
	        sum += arr[i];
	   
	   bool dp[n+1][sum+1];
        
       // Initialisation    
       for (int i = 0; i < n+1; i++)
           dp[i][0] = true;
       for (int i = 1; i < sum+1; i++)
           dp[0][i] = false;
           
	   // Choice Diagram
	   for(int i=1; i<n+1; i++)
	        for(int j=1; j<sum+1; j++)
	        {
	            if(arr[i-1] > j)
	                dp[i][j] = dp[i-1][j];
	            else
	                dp[i][j] = dp[i-1][j - arr[i-1]] || dp[i-1][j];
	        }
	   
	    for(int j=sum/2; j >= 0; j--)
	       if(dp[n][j] == true)
	           return (sum - 2*j);

	} 
};


// Recursive Method
// Will pass 1000/ 1020 cases
class Solution{

  public:
    int solve(int arr[], int n, int sum, int subset1)
    {
        // Base case
        if(n == 0)
            return abs( (sum - subset1) - subset1);   // Subset1 - subset2
        
        return min (solve(arr, n-1, sum, subset1 + arr[n-1]), solve(arr, n-1, sum, subset1));
    }
    
	int minDifference(int arr[], int n)  { 
	    int sum = 0;
	    for(int i=0; i<n; i++)
	        sum += arr[i];
	   
	   return solve(arr, n, sum, 0);
	} 
};