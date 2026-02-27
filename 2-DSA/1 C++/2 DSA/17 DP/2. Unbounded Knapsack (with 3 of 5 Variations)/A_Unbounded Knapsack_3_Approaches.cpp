/* 
	A_Unbounded Knapsack_3_Approaches
	Unbounded Knapsack (Repetition of items allowed) 

Given a knapsack weight W and a set of n items with certain value vali and weight wti, we need to calculate minimum amount that could make up this quantity exactly. 
This is different from classical Knapsack problem, here we are allowed to use unlimited number  of instances of an item.
Examples:

Input : W = 100
       val[]  = {1, 30}
       wt[] = {1, 50}
Output : 100
There are many ways to fill knapsack.
1) 2 instances of 50 unit weight item.
2) 100 instances of 1 unit weight item.
3) 1 instance of 50 unit weight item and 50 instances of 1 unit weight items. We get maximum value with option 2.

/***********************************************************************************************************************/

// Code for all 3 approaches: Recursion => Memoization (Top down) => DP (Bottom Up)

// 1. Recursive Approach

int unboundedKnapsack(int W, int wt[], int val[], int idx)
{
	// Base Case
	// if we are at idx 0.
	if (idx == 0) 
		return (W / wt[0]) * val[0];

	// There are two cases either take element or not take. If not take then
	int notTake = 0 + unboundedKnapsack(W, wt, val, idx - 1);
	
    // if take then weight = W-wt[idx] and index will remain same.
	int take = INT_MIN;
	if (wt[idx] <= W) 
		take = val[idx]	+ unboundedKnapsack(W - wt[idx], wt, val, idx)
	
    return max(take, notTake);
}


/***********************************************************************************************************************/

// 2. Memoize above recursive code (top-down)
// T.C. : O(n*W)
// S.C. : O(N*W) + O(N)’


int unboundedKnapsack(int W, int wt[], int val[], int idx,	vector<vector<int> >& dp)
{
	// Base Case
	// if we are at idx 0.
	if (idx == 0) 
		return (W / wt[0]) * val[0];
	
	if (dp[idx][W] != -1)
		return dp[idx][W];
	
    // There are two cases either take element or not take. If not take then

	int notTake	= 0 + unboundedKnapsack(W, wt, val, idx - 1, dp);
	// if take then weight = W-wt[idx] and index will remain same.
	int take = INT_MIN;
	if (wt[idx] <= W) 
        	take = val[idx]+ unboundedKnapsack(W - wt[idx], wt, val, idx, dp);
	
	return dp[idx][W] = max(take, notTake);
}

/***********************************************************************************************************************/

// 3. Bottom Up Approach - Dynamic Programming
// T.C. : O(W*N) where W is the total weight(capacity)
// S.C. : O(W) where W is the total weight.


int unboundedKnapsack(int W, int n, int val[], int wt[])
{
	int dp[W+1];
	memset(dp, 0, sizeof dp);

	for (int i=0; i<=W; i++)
        for (int j=0; j<n; j++)
            if (wt[j] <= i)
                dp[i] = max(dp[i], dp[i-wt[j]] + val[j]);

	return dp[W];
}