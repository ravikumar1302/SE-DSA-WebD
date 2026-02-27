/*
Count_of_Subsets_Sum_with_a_Given_Sum_4_Approach

    Given an array arr[] of length N and an integer X, the task is to find the number of subsets with sum equal to X.
    
	Example:
    Input: arr[] = {1, 2, 3, 3}, X = 6
    Output: 3
    All the possible subsets are {1, 2, 3}, {1, 2, 3} and {3, 3}
*/

/***********************************************************************************************************************/

// 1. Brute force Approach
// T.C. : Exponential

void printSubsetsCount(int set[], int n, int val)
{
	int sum; // it stores the current sum
	int count = 0;
	for (int i = 0; i < (1 << n); i++) 
	{
		sum = 0;
		for (int j = 0; j < n; j++)
			if ((i & (1 << j)) > 0) 
				sum += set[j]; 		// elements are added one by one of a subset to the sum

		// It checks if the sum is equal to desired sum. If it is true then it prints the elements of the sum  to the output
		if (sum == val)
			count++;
	}
	// it means no subset is found with given sum
	if (count == 0) 
		cout<<"No subset is found";

	else 
		cout<<count;
}

/***********************************************************************************************************************/

// 2. Recursive
// T.C. : 
// S.C. : 

#define maxN 20
#define maxSum 50
#define minSum 50
#define base 50
 
// To store the states of DP
int dp[maxN][maxSum + minSum];
bool v[maxN][maxSum + minSum];

int findCnt(int* arr, int i, int required_sum, int n)
{
	// Base case
	if (i == n) 
	{
		if (required_sum == 0)
			return 1;
		else
			return 0;
	}

	// If the state has been solved before return the value of the state
	if (v[i][required_sum + base])
		return dp[i][required_sum + base];

	// Setting the state as solved
	v[i][required_sum + base] = 1;

	// Recurrence relation
	dp[i][required_sum + base] = findCnt(arr, i + 1, required_sum, n) + findCnt(arr, i + 1, required_sum - arr[i], n);
	
    return dp[i][required_sum + base];
}


/***********************************************************************************************************************/

// 3. Using Tabulation Method : This method is valid only for those arrays which contains positive elements
// T.C. : O(sum*n), where the sum is the ‘target sum’
// S.C. : O(sum*n), as the size of the 2-D array, is sum*n. 


int subsetSum(int a[], int n, int sum)
{
	int tab[n + 1][sum + 1];

    // Initializing the first value of matrix
	tab[0][0] = 1;
	for (int i = 1; i <= sum; i++)
		tab[0][i] = 0;
	
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= sum; j++)
		{
			if (a[i - 1] > j)
				tab[i][j] = tab[i - 1][j];
			else
				tab[i][j] = tab[i - 1][j] + tab[i - 1][j - a[i - 1]];
		}

	return tab[n][sum];
}


/***********************************************************************************************************************/

// 4. Space Optimisation
// T.C. : O(sum*n), where the sum is the ‘target sum’
// S.C. : O(sum)

// We can solve this problem by just taking care of last state and current state so we can wrap up this problem in O(target+1) space complexity

int CountSubsetSum(vector<int>& arr, int val, int n)
{
	int count = 0;
	vector<int> PresentState(val + 1, 0),
		LastState(val + 1, 0);
	
    // consider only last and present state we dont need the (present-2)th state and above and we know for val to be 0 if we dont pick the current index element we can achieve
	PresentState[0] = LastState[0] = 1;
	if (arr[0] <= val)
		LastState[arr[0]] = 1;
	for (int i = 1; i < n; i++) 
    {
		for (int j = 1; j <= val; j++)
			PresentState[j] = ((j >= arr[i]) ? LastState[j - arr[i]] : 0) + LastState[j];
		
        // this we will need in the next iteration so just swap current and last state.
		LastState = PresentState;
	}
	// Note after exit from loop we will having a present state which is nothing but the laststate itself;
	return PresentState[val];
}