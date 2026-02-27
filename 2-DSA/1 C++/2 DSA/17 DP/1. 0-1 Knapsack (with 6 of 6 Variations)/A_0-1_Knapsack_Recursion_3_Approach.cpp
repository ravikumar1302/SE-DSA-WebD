/* 
	0-1_Knapsack_Recursion_3_Approach
	A Naive recursive implementation of 0-1 Knapsack problem 

 Example:
 Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack. 
 In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items respectively. Also given an integer W which represents knapsack capacity, 
 find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W. 
 You cannot break an item, either pick the complete item, or don’t pick it (0-1 property).
*/

/***********************************************************************************************************************/

/*
Recursive Approach : Binary Tree

The recursive approach computes the same sub-problems again and again. 
See the following recursion tree, K(1, 1) is being evaluated twice.

The recursion tree is for following sample inputs = wt[] = {1, 1, 1}, W = 2, val[] = {10, 20, 30}7

                       K(n, W)
                       K(3, 2)  
                   /            \ 
                 /                \               
            K(2, 2)                  K(2, 1)
          /       \                  /    \ 
        /           \              /        \
       K(1, 2)      K(1, 1)        K(1, 1)     K(1, 0)
       /  \         /   \              /        \
     /      \     /       \          /            \
K(0, 2)  K(0, 1)  K(0, 1)  K(0, 0)  K(0, 1)   K(0, 0)

Recursion tree for Knapsack capacity 2 units and 3 items of 1 unit weight.
*/

/***********************************************************************************************************************/

// Code for all 3 approaches: Recursion => Memoization (Top down) => DP (Bottom Up)

//1. Recursive Approach
// T.C. : O(2^n), as two choices for all
// S.C. : O(N), Used by Recursion stack

int knapSack(int w, int wt[], int val[], int n) 
{ 
	//Base Case
	if(n==0 || w==0) 
		return 0;
	
	//Choice Diagram Code 
	//1. Choice to include item or not
	if(wt[n-1] <= w)
		return max(val[n-1] + knapSack(w-wt[n-1], wt, val, n-1), 0 + knapSack(w,wt,val,n-1));

	//2. No choice
	else if(wt[n-1] > w)
		return 0 + knapSack(w,wt,val,n-1);
}

/***********************************************************************************************************************/

//2. Memoization (top-down)
// T.C. : O(n*W)
// S.C. : O(n*W), Used by 2-D matrix

int t[1001][1001];
int fun(int w, int wt[], int val[], int n, vector<vector<int>>& t) 
{ 
	//Base Case
	if(n<=0 || w<=0) return 0;
	
	//Check if result exists already
	if(t[n][w] != -1) return t[n][w];
	
	//If result doesn't exist, Choice Diagram Code 
	//1. Choice to include item or not
	if(wt[n-1] <= w)
	{
		t[n][w] = max(val[n-1] + fun(w-wt[n-1], wt, val, n-1, t), 0+fun(w,wt,val,n-1, t));
		return t[n][w];
	}
	
	//2. No choice
	else if(wt[n-1] > w)
	{
		t[n][w] = 0 + fun(w,wt,val,n-1, t);
		return t[n][w];
	}     
}

int knapSack(int w, int wt[], int val[], int n)
{
	memset(t, -1, sizeof(t));
	return fun(w, wt, val, n, t);
}

/***********************************************************************************************************************/

//3. Bottom Up Approach - Dynamic Programming
// T.C. : O(n*W)
// S.C. : O(n*W), Used by 2-D matrix

int knapSack(int w, int wt[], int val[], int n) 
{
	int t[n+1][w+1];
	
	//Initialize matrix
	for(int i=0; i<w+1; i++) t[0][i] = 0;
	for(int j=0; j<n+1; j++) t[j][0] = 0;
	
	//Choice Diagram to code
	for(int i = 1; i<n+1; i++)
	{
		for(int j=1; j<w+1; j++)
		{
			//1. In case of choice
			if(wt[i-1] <= j)
				t[i][j] = max(val[i-1] + t[i-1][j-wt[i-1]], 0+t[i-1][j]);
			
			//2. No choice
			else if(wt[i-1] > j)
				t[i][j] = 0+t[i-1][j];
		}
	}
	return t[n][w];
}