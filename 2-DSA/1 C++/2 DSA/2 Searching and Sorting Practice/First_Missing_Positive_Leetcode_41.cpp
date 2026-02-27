/*
First_Missing_Positive_Leetcode_41

Given an unsorted integer array nums, return the smallest missing positive integer.
You must implement an algorithm that runs in O(n) time and uses constant extra space.

    Example 1:
    Input: nums = [1,2,0]
    Output: 3
    Explanation: The numbers in the range [1,2] are all in the array.

    Example 2:
    Input: nums = [3,4,-1,1]
    Output: 2
    Explanation: 1 is in the array but 2 is missing.

    Example 3:
    Input: nums = [7,8,9,11,12]
    Output: 1
    Explanation: The smallest positive integer 1 is missing.
*/

// Appraoch : Using Cycle sort 
// Cyclic Sort is used when O(N) time, O(1) space is given along with some range like [1,n]
// Time : O(N)
// Space : O(1)

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
     

        
        int n = nums.size();
        int i=0;
        
        // Cycle Sort Algorithm Variation
        while(i<n){
                if(nums[i] == i+1 || nums[i] <= 0 || nums[i] > n) 
                    i++;
            else if(nums[nums[i]-1] != nums[i]) 
                swap(nums[i], nums[nums[i]-1]);
            else        // Used when both the values are same, eg. {1,1,1}
                i++;
        }

        // finding ans
        for(int i=0; i<n; i++)
            if(nums[i] != i+1)
                return i+1;
        
        return n+1;
    }
};
