/*
Product_array_puzzle_GFG

Given an array nums[] of size n, construct a Product Array P (of same size n) such that P[i] is equal to the product of all the elements of nums except nums[i].

    Example 1:
    Input: n = 5, nums[] = {10, 3, 5, 6, 2}
    Output: 180 600 360 300 900
    Explanation: 
    For i=0, P[i] = 3*5*6*2 = 180.
    For i=1, P[i] = 10*5*6*2 = 600.
    For i=2, P[i] = 10*3*6*2 = 360.
    For i=3, P[i] = 10*3*5*2 = 300.
    For i=4, P[i] = 10*3*5*6 = 900.

    Example 2:
    Input: n = 2, nums[] = {12,0}
    Output: 0 12

Note: Try to solve this problem without using the division operation.
 
Expected Time Complexity: O(n)
Expected Auxiliary Space: O(n)
*/


class Solution{
  public:
    // nums: given vector
    // return the Product vector P that hold product except self at each index
    vector<long long int> productExceptSelf(vector<long long int>& nums, int n) {
       
         vector<long long int> prefix(n+1, 1);
         vector<long long int> suffix(n+1, 1);
         
         prefix[0] = 1;
         suffix[n] = 1;
         
         for(int i=0; i<n; i++)
        {
            prefix[i+1] = prefix[i]*nums[i];
            suffix[n - i - 1] = suffix[n-i]*nums[n-i-1]; 
        }
        
        vector<long long int> ans;
        for(int i=0; i<n; i++)
            ans.push_back(prefix[i]*suffix[i+1]);
        
        return ans;
    }
};