/*
0-1_Knapsack_Problem_GFG

You are given weights and values of N items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack. Note that we have only one quantity of each item.
In other words, given two integer arrays val[0..N-1] and wt[0..N-1] which represent values and weights associated with N items respectively. Also given an integer W which represents knapsack capacity, 
find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W.
You cannot break an item, either pick the complete item or dont pick it (0-1 property).

    Example 1:
    Input:
    N = 3
    W = 4
    values[] = {1,2,3}
    weight[] = {4,5,1}
    Output: 3

Expected Time Complexity: O(N*W).
Expected Auxiliary Space: O(N*W)
*/


// Recursive
// It will give TLE in last some cases
class Solution
{
    public:
    //Function to return max value that can be put in knapsack of capacity W.
    int knapSack(int W, int wt[], int val[], int n) 
    { 
        // Base case
        if(n==0 || W==0)
           return 0;
        
        // If we have option to select or not
        if(wt[n-1] <= W)
            return max( val[n-1] + knapSack( W-wt[n-1], wt, val, n-1) , knapSack( W, wt, val, n-1) );
        // If we have no option
        else if(wt[n-1] > W)
            return knapSack( W, wt, val, n-1) ;
    }
};

// Memoization Approach

class Solution
{
    // Memoization
    public:
    int dp[1001][1001];
    int knap(int W,int wt[],int val[],int n)
    {
        if(n == 0 || W == 0)
        return 0;
       
       //choice Diagram
       if(dp[n][W] != -1)
        return dp[n][W];
       
       if(wt[n-1]<=W)
           return dp[n][W] = max(val[n-1] + knap(W-wt[n-1],wt,val,n-1),knap(W,wt,val,n-1));

       else
           return dp[n][W] = knap(W,wt,val,n-1);
    }
   
   int knapSack(int W, int wt[], int val[], int n) 
   { 
      memset(dp, -1, sizeof(dp));
      return knap(W,wt,val,n);
   }
};


// Bottom-Up Approach
class Solution
{
    public:
    int dp[1001][1001];
    int knapSack(int W, int wt[], int val[], int n) 
    { 
        //int dp[1001+1][1001+1];  // Initialize outside
        
        // Initilisation
        for(int i=0; i<n+1; i++)
            for(int j=0; j<W+1; j++)
                if(i==0 || j== 0)
                    dp[i][j] = 0;
        
        // Choice Diagram
        for(int i=1; i<n+1; i++)
            for(int j=1; j<W+1; j++)
            {
                // When choice is there
                if(wt[i-1] <= j)
                    dp[i][j] = max( val[i-1] + dp[i-1][j - wt[i-1]], dp[i-1][j]);
                // When choice is not there
                else
                    dp[i][j] = dp[i-1][j];
            }
        return dp[n][W];
    }
};