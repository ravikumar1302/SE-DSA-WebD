/*
Minimum Subset Sum Difference
OR
Partition a set into two subsets such that the difference of subset sums is minimum

Given a set of integers, the task is to divide it into two sets S1 and S2 such that the absolute difference between their sums is minimum.
If there is a set S with n elements, then if we assume Subset1 has m elements, Subset2 must have n-m elements and the value of abs(sum(Subset1) – sum(Subset2)) should be minimum.

    Example:
    Input:  arr[] = {1, 6, 11, 5} 
    Output: 1
    Explanation:
    Subset1 = {1, 5, 6}, sum of Subset1 = 12 
    Subset2 = {11}, sum of Subset2 = 11 

*/

/***********************************************************************************************************************/

// Method - 1 : Recursive
// T.C.: O(2^n) 

int findMinRec(int arr[], int i, int sumCalculated, int sumTotal)
{
	if (i == 0)
		return abs((sumTotal - sumCalculated) - sumCalculated);

	return min( findMinRec(arr, i - 1, sumCalculated + arr[i - 1], sumTotal), findMinRec(arr, i - 1, sumCalculated, sumTotal));
}

int findMin(int arr[], int n)
{
	// Compute total sum of elements
	int sumTotal = 0;
	for (int i = 0; i < n; i++)
		sumTotal += arr[i];

	return findMinRec(arr, n, 0, sumTotal);
}

/***********************************************************************************************************************/

// Method - 2 : DP 
// T.C.: O(sum*n) 
// S.C.: O(sum*n)

int findMin(int arr[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += arr[i];

	bool dp[n + 1][sum + 1];

	for (int i = 0; i <= n; i++)
		dp[i][0] = true;

	for (int i = 1; i <= sum; i++)
		dp[0][i] = false;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= sum; j++) 
		{
			dp[i][j] = dp[i - 1][j];

			if (arr[i - 1] <= j)
				dp[i][j] |= dp[i - 1][j - arr[i - 1]];
		}


	int diff = INT_MAX;

	// Find the largest j such that dp[n][j] is true where j loops from sum/2 t0 0 (in the last row of dp table, where full array is taken)
	for (int j = sum / 2; j >= 0; j--) 
	{
		if (dp[n][j] == true) 
		{
			diff = sum - 2 * j;
			break;
		}
	}
	return diff;
}

/***********************************************************************************************************************/

// Method - 2 : DP (Dynamic Programming Solution (Space Complexity Optimized))
// T.C.: O(sum*n) 
// S.C.: O(sum)

int minDifference(int arr[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += arr[i];
	int y = sum / 2 + 1;
	
	// dp[i] gives whether is it possible to get i as sum of elements dd is helper variable we use dd to ignoring duplicates
	bool dp[y], dd[y];

	// Initialising dp and dd
	for (int i = 0; i < y; i++)
		dp[i] = dd[i] = false;

	// sum = 0 is possible
	dd[0] = true;
	for (int i = 0; i < n; i++) {
		// updating dd[k] as true if k can be formed using elements from 1 to i+1
		for (int j = 0; j + arr[i] < y; j++) 
			if (dp[j])
				dd[j + arr[i]] = true;

		// updating dd
		for (int j = 0; j < y; j++) 
		{
			if (dd[j])
				dp[j] = true;
			dd[j] = false; // reset dd
		}
	}
	// checking the number from sum/2 to 1 which is possible to get as sum

	for (int i = y - 1; i >= 0; i--) {
		if (dp[i])
			return (sum - 2 * i);
		// since i is possible to form then another number is sum-i so mindifference is sum-i-i
	}
}