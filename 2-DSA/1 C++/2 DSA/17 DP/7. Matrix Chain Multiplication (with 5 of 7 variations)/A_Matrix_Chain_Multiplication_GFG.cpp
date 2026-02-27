/*
Matrix_Chain_Multiplication_GFG

Given a sequence of matrices, find the most efficient way to multiply these matrices together. The efficient way is the one that involves the least number of multiplications.

The dimensions of the matrices are given in an array arr[] of size N (such that N = number of matrices + 1) where the ith matrix has the dimensions (arr[i-1] x arr[i]).

    Example 1:

    Input: N = 5, arr = {40, 20, 30, 10, 30}
    Output: 26000
    Explaination: There are 4 matrices of dimension 40x20, 20x30, 30x10, 10x30. Say the matrices are named as A, B, C, D. 
    Out of all possible combinations, the most efficient way is (A*(B*C))*D.  The number of operations are - 20*30*10 + 40*20*10 + 40*10*30 = 26000.

Expected Time Complexity: O(N3)
Expected Auxiliary Space: O(N2)

*/

// Recursive 
// Time : Exponential
// Giving TLE after some cases

class Solution{
public:
    int solve(int arr[], int i, int j)
    {
        // Step 1 : Find i, j
        // Step 2 : Find right base case
        if(i >= j)
            return 0;
    
        // Step 3 : Find K-Loop Sequence (move k from i to j)
        int mini = INT_MAX;
        for(int k = i; k <= j-1; k++)
        {
            int temp = solve(arr, i, k) + solve(arr, k+1, j) + arr[i-1]*arr[k]*arr[j];
    
            // Step 4 : Calculate ans from temporary ans
            if(temp < mini)
                mini = temp;
            // mini = min(mini, temp);  // Same as above two line
        }
    
        return mini;
    }

    int matrixMultiplication(int N, int arr[])
    {
        int i = 1;
        int j = N-1;
        return solve(arr, i, j);
    }
};


/************************************************************************************/
// Memoization : Working and passing all test
// Time : O(N^3)
// Space : O(N^2) ignoring recursion stack space


class Solution{
public:
    int solve(int arr[], int i, int j, vector<vector<int>> &dp)
    {
        // Step 1 : Find i, j
        // Step 2 : Find right base case
        if(i >= j)
            return 0;
        
        if(dp[i][j] != -1)  // Change 1
            return dp[i][j];
        
        // Step 3 : Find K-Loop Sequence (move k from i to j)
        int mini = INT_MAX;
        for(int k = i; k <= j-1; k++)
        {
            int temp = solve(arr, i, k, dp) + solve(arr, k+1, j, dp) + arr[i-1]*arr[k]*arr[j];
    
            // Step 4 : Calculate ans from temporary ans
            mini = min(mini, temp);

        }
        return dp[i][j] = mini;     // Change 2
    }

    int matrixMultiplication(int N, int arr[])
    {
        int i = 1;
        int j = N-1;
        
        vector<vector<int>> dp(101, vector<int> (101,-1));
        
        return solve(arr, i, j, dp);
    }
};


/************************************************************************************/

// Memoization other solution : Working and passing all test
// It is same as above, just dp is decalred outside and mini is also passed from non-recurive function


class Solution{
public:
    
    int dp[101][101];
    int solve(int arr[], int i, int j,  int mini)
    {
        // Step 1 : Find i, j
        // Step 2 : Find right base case
        if(i >= j)
            return 0;
        
        if(dp[i][j] != -1)  // Change 1
            return dp[i][j];
        
        // Step 3 : Find K-Loop Sequence (move k from i to j)
        //int mini = INT_MAX;
        for(int k = i; k <= j-1; k++)
        {
            int temp = solve(arr, i, k,mini) + solve(arr, k+1, j,  mini) + arr[i-1]*arr[k]*arr[j];
    
            // Step 4 : Calculate ans from temporary ans
            mini = min(mini, temp);

        }
    
        return dp[i][j] = mini;     // Change 2
    }

    int matrixMultiplication(int N, int arr[])
    {
        int i = 1;
        int j = N-1;
        int mini = INT_MAX;
        memset(dp, -1, sizeof(dp));
        //vector<vector<int>> dp(101, vector<int> (101,-1)); // Passing this is not working, so declared the table outside the function
        
        return solve(arr, i, j,  mini);
    }
};