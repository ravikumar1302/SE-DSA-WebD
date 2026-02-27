/*
Subarray_with_given_sum_GFG

Given an unsorted array A of size N that contains only non-negative integers, find a continuous sub-array which adds to a given number S.

In case of multiple subarrays, return the subarray which comes first on moving from left to right.

    Example 1:
    Input : N = 5, S = 12, A[] = {1,2,3,7,5}
    Output: 2 4
    Explanation: The sum of elements from 2nd position to 4th position is 12.
    
    Example 2:
    Input : N = 10, S = 15, A[] = {1,2,3,4,5,6,7,8,9,10}
    Output: 1 5
    Explanation: The sum of elements  from 1st position to 5th position is 15.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)

*/

/*
Approach -1 : O(N^2)
Using two for loop check the subarray sum for each value
*/

// Approach-2

class Solution
{
    public:
    //Function to find a continuous sub-array which adds up to a given number.
    vector<int> subarraySum(int arr[], int n, long long s)
    {
        int i=0;    // right pointer
        int j=0;    // left pointer
        long long sum=0L;
        vector<int>res;
        
        while(sum!=s && j<n)
        {
            if(sum<s)   // Move right pointer and add sum
            {
                sum+=arr[i];
                i++;
            }
            
            else if(sum>s)  // move left pointer and subtract sum
            {
                sum-=arr[j];
                j++;
            }
            
            if(sum==s)  // Push values
            {
                res.push_back(j+1);
                res.push_back(i);
                return res;
            }
        }
        
        res.push_back(-1);
        return res;
    }
};