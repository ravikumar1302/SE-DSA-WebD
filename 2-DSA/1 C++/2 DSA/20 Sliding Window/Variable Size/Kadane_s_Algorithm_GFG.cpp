/*
Kadane_s_Algorithm_GFG

Given an array Arr[] of N integers. Find the contiguous sub-array(containing at least one number) which has the maximum sum and return its sum.

    Example 1:
    Input: N = 5, Arr[] = {1,2,3,-2,5}
    Output: 9
    Explanation: Max subarray sum is 9 of elements (1, 2, 3, -2, 5) which is a contiguous subarray.

    Example 2:
    Input: N = 4, Arr[] = {-1,-2,-3,-4}
    Output: -1
    Explanation: Max subarray sum is -1 of element (-1)

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)
*/


class Solution{
    public:
    // arr: input array
    // n: size of array
    //Function to find the sum of contiguous subarray with maximum sum.
    long long maxSubarraySum(int arr[], int n){
        
        // Your code here
        int max_so_far = arr[0];
        int max_ending_here = arr[0];

        for (int i = 1; i < n; i++)
        {
            if(arr[i] < (max_ending_here + arr[i]))
                max_ending_here = max_ending_here + arr[i];
            else
                max_ending_here = arr[i];
            if(max_so_far < max_ending_here)
                max_so_far = max_ending_here;
        }


        return max_so_far;
        
    }
};