/*
Partitions_With_Given_Difference_Codestudio

Problem Statement
Given an array ‘ARR’, partition it into two subsets (possibly empty) such that their union is the original array. Let the sum of the elements of these two subsets be ‘S1’ and ‘S2’.
Given a difference ‘D’, count the number of partitions in which ‘S1’ is greater than or equal to ‘S2’ and the difference between ‘S1’ and ‘S2’ is equal to ‘D’. 
Since the answer may be too large, return it modulo ‘10^9 + 7’.

OR Given an array Arr[] and a difference diff, find the number of subsets that array can be divided so that each the difference between the two subset is the given diff.
*/

int countPartitions(int n, int d, vector<int> &arr) 
{
        int sum=0;
        for(int i=0; i<n; i++)
            sum += arr[i];

        if(d > sum || (sum + d) % 2 == 1)    
            return 0;

        /*
            Let there be two subsets with sum s1 and s2 respectively
            s1 + s2 = arr_sum 
            s1 - s2 = diff

            s1 = (diff + arr_sum)/2 (adding above equations, we get)
            Therefore, we will find number of subsets with sum as s1
        */

       int s1 = (sum+d)/2;
       int dp[n+1][s1+1];
       int mod = 1000000007;

       // Initialisation
       dp[0][0] = 1;
       for (int i = 1; i < s1+1; i++)
           dp[0][i] = 0;
      for (int i = 1; i < n+1; i++)
           dp[i][0] = 0;
           
       // Choice Diagram
       for(int i=1; i<n+1; i++)
            for(int j=0; j<s1+1; j++)
            {
                if(arr[i-1] > j)
                    dp[i][j] = (dp[i-1][j])%mod;
                else
                    dp[i][j] = (dp[i-1][j - arr[i-1]] + dp[i-1][j])%mod;
            }
    return dp[n][s1];
}