/*
Count_number_of_subset_with_a_given_difference

Given an array Arr[] and a difference diff, find the number of subsets that array can be divided so that each the difference between the two subset is the given diff.

    Example1:
    Input:
    Arr[] : 1,1,2,3
    diff: 1
    Output: 3 . 
*/

// Memoizzation Approach
// T.C.: O(sum*n)
// S.C.: O(sum*n)

#include <bits/stdc++.h>
using namespace std;
int dp[20001][20001];

int countSubsets(int arr[], int n, int sum)
{
	if (dp[n][sum] != -1)
		return dp[n][sum];
	// base case
	if (sum == 0)
		return 1;
	if (n == 0)
		return 0;
	if (arr[n - 1] <= sum)
		return dp[n][sum] = countSubsets(arr, n - 1, sum - arr[n - 1]) + countSubsets(arr, n - 1, sum);
		
	return dp[n][sum] = countSubsets(arr, n - 1, sum);
}

int main()
{
	memset(dp, -1, sizeof(dp));

	int n, diff; 
	cin >> n >> diff;
	int arr[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	int arr_sum = 0;
	for (int i = 0; i < n; i++)
		arr_sum += arr[i];
    /*
    Let there be two subsets with sum s1 and s2 respectively
	s1 + s2 = arr_sum 
    s1 - s2 = diff

	s1 = (diff + arr_sum)/2 (adding above equations, we get)
	Therefore, we will find number of subsets with sum as s1
    */
	int sum = (diff + arr_sum) / 2;
	
	return countSubsets(arr, n, sum);
	
	return 0;
}