/*
Binary_Trees_With_Factors_Leetcode_823

Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.

We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.

Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.

    Example 1:
    Input: arr = [2,4]
    Output: 3
    Explanation: We can make these trees: [2], [4], [4, 2, 2]

    Example 2:
    Input: arr = [2,4,5,10]
    Output: 7
    Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].

*/


// YouTube Video Solution : https://www.youtube.com/watch?v=stDA8CJAFF4&t=442s

// Time: O(N^2)
// Space: O(N)

class Solution {
public:
    int mod = 1000000007;
    int numFactoredBinaryTrees(vector<int>& arr) {
        
        sort(arr.begin(), arr.end());
        map<long long, long long> dp;

        // Inititalizing each as 1, as single digit Tree is also an ans
        for(long long i=0; i<arr.size(); i++)
            dp[arr[i]] = 1;

        // Finding remaning possible ans
        for(int i=1; i<arr.size(); i++)
        {
            for(int j=i-1; j>=0; j--)
            {
                if(arr[i]%arr[j] == 0)
                {
                    int right = arr[i]/arr[j];
                    if(dp[right])
                        dp[arr[i]] = ( dp[arr[i]] + ( dp[arr[j]] * dp[right] ) )%mod;
                }
            }
        }

        // Calculating total value
        int sum = 0;
        for(long long i=0; i<arr.size(); i++)
            sum = (sum + dp[arr[i]])%mod;

        return sum;
    }
};