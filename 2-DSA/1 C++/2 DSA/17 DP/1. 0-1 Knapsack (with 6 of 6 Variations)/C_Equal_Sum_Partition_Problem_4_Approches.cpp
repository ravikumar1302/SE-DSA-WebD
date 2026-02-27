/*
Equal_Sum_Partition_Problem_4_Approches

Partition problem is to determine whether a given set can be partitioned into two subsets such that the sum of elements in both subsets is same.
    
    Examples:
    arr[] = {1, 5, 11, 5}
    Output: true 
    The array can be partitioned as {1, 5, 5} and {11}
*/

// Method -1 : Recursion
// T.C.: O(2^n)

bool isSubsetSum(int arr[], int n, int sum)
{
	if (sum == 0)
		return true;
	if (n == 0 && sum != 0)
		return false;

	if (arr[n - 1] > sum)
		return isSubsetSum(arr, n - 1, sum);
    else
	    return isSubsetSum(arr, n - 1, sum) || isSubsetSum(arr, n - 1, sum - arr[n - 1]);
}

bool findPartiion(int arr[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += arr[i];

	// If sum is odd, there cannot be two subsets with equal sum
	if (sum % 2 != 0)
		return false;

	return isSubsetSum(arr, n, sum / 2);
}


/***********************************************************************************************************************/

// Method - 2 : Top-Down: Memoization
// T.C.: O(sum*n) 
// S.C.: O(sum*n)

bool isSubsetSum(int arr[], int n, int sum, vector<vector<int> >& dp)
{
	if (sum == 0)
		return true;
	if (n == 0 && sum != 0)
		return false;

	if (dp[n][sum] != -1) 
		return dp[n][sum];

	if (arr[n - 1] > sum)
		return isSubsetSum(arr, n - 1, sum, dp);

	return dp[n][sum] = isSubsetSum(arr, n - 1, sum, dp) || isSubsetSum(arr, n - 1, sum - arr[n - 1], dp);
}

bool findPartiion(int arr[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += arr[i];

	// If sum is odd, there cannot be two subsets with equal sum
	if (sum % 2 != 0)
		return false;

	vector<vector<int> > dp(n + 1, vector<int>(sum + 1, -1));

	return isSubsetSum(arr, n, sum / 2, dp);
}


/***********************************************************************************************************************/

// Method - 3 : DP (Bottom-Up: Tabulation)
// T.C.: O(sum*n) 
// S.C.: O(sum*n)

bool findPartiion(int arr[], int n)
{
	int sum = 0;
	int i, j;

	for (i = 0; i < n; i++)
		sum += arr[i];

	if (sum % 2 != 0)
		return false;

	bool part[sum / 2 + 1][n + 1];

	// initialize top row as true
	for (i = 0; i <= n; i++)
		part[0][i] = true;

	// initialize leftmost column, except part[0][0], as 0
	for (i = 1; i <= sum / 2; i++)
		part[i][0] = false;

	// Choice diagram
	for (i = 1; i <= sum / 2; i++) 
    {
		for (j = 1; j <= n; j++) 
        {
			part[i][j] = part[i][j - 1];
			if (i >= arr[j - 1])
				part[i][j] = part[i][j] || part[i - arr[j - 1]][j - 1];
		}
	}
	return part[sum / 2][n];
}


/***********************************************************************************************************************/

// Method - 3 : Bottom - UP Solution (Space Complexity Optimized))
// T.C.: O(sum*n) 
// S.C.: O(sum)

bool findPartiion(int arr[], int n)
{
	int sum = 0;
	int i, j;

	// Calculate sum of all elements
	for (i = 0; i < n; i++)
		sum += arr[i];

	if (sum % 2 != 0)   // If sum is odd, can't be divided in equal sum partition
		return false;

	bool part[sum / 2 + 1];

	// Initialize the part array as 0
	for (i = 0; i <= sum / 2; i++)
		part[i] = 0;


	for (i = 0; i < n; i++) {
		// the element to be included in the sum cannot be  greater than the sum
		for (j = sum / 2; j >= arr[i]; j--) 
        { 
            // check if sum - arr[i] could be formed from a subset using elements before index i
			if (part[j - arr[i]] == 1 || j == arr[i])
				part[j] = 1;
		}
	}
	return part[sum / 2];
}