/*
Subset_Sum_Problem_3_Approaches

Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.
Example:

Input:  set[] = {3, 34, 4, 12, 5, 2}, sum = 9
Output:  True  //There is a subset (4, 5) with sum 9.

*/

// Method - 1 : Recursion
// Complexity Analysis: The above solution may try all subsets of given set in worst case. So, time complexity will be exponential. 
// The problem is in-fact NP-Complete (There is no known polynomial time solution for this problem)

bool isSubsetSum(int set[], int n, int sum)
{
	// Base Cases
	if (sum == 0)
		return true;
	if (n == 0)
		return false;

	// Choice Diagram
	if (set[n - 1] > sum)
		return isSubsetSum(set, n - 1, sum);

	return isSubsetSum(set, n - 1, sum) || isSubsetSum(set, n - 1, sum - set[n - 1]);
}

/***********************************************************************************************************************/

// Method - 2 : Bottom Up Approach : DP
// T.C.: O(sum*n)
// S.C.: O(sum*n), as the size of 2-D array is sum*n. + O(n) for recursive stack space

bool isSubsetSum(int set[], int n, int sum)
{
	bool dp[n + 1][sum + 1];

	// Initialisation
	for (int i = 0; i <= n; i++)
		dp[i][0] = true;

	for (int i = 1; i <= sum; i++)
		dp[0][i] = false;

	for (int i = 1; i <= n; i++) 
    {
		for (int j = 1; j <= sum; j++) 
        {
			if (j < set[i - 1])
				dp[i][j] = dp[i - 1][j];
			if (j >= set[i - 1])
				dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
		}
	}

	return dp[n][sum];
}

/***********************************************************************************************************************/

// Method - 3 : Memoization 
// T.C.: O(sum*n)
// S.C.: O(sum*n) + O(n) as the size of 2-D array is sum*n. + O(n) for recursive stack space

int dp[2000][2000];    		// Taking the matrix as globally
memset(dp, -1, sizeof(dp));   // Memset runs only if written in main function, or other function, but global is not allowed like written here

int subsetSum(int a[], int n, int sum)
{
	// If the sum is zero it means, we got our expected sum
	if (sum == 0)
		return 1;
		
	if (n <= 0)
		return 0;
	
	// If the value is not -1 it means it already call the function with the same value, it will save us from the repetition.
	if (dp[n - 1][sum] != -1)
		return dp[n - 1][sum];
	
	if (a[n - 1] > sum)
		return dp[n - 1][sum] = subsetSum(a, n - 1, sum);
	else
		return dp[n - 1][sum] = subsetSum(a, n - 1, sum) || subsetSum(a, n - 1, sum - a[n - 1]);
}