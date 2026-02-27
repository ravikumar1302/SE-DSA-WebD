/*
Next_Permutation_Leetcode_31

A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

For example, for arr = [1,2,3], the following are considered permutations of arr: [1,2,3], [1,3,2], [3,1,2], [2,3,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

    For example, the next permutation of arr = [1,2,3] is [1,3,2].
    Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
    While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
    Given an array of integers nums, find the next permutation of nums.

The replacement must be in place and use only constant extra memory.

    Example 1:
    Input: nums = [1,2,3]
    Output: [1,3,2]
*/


// The naive approach is find all posible sequence and then check and return next one. But time will be : O(N!*N) as there are N elements

// Optimized Approach : Time : O(N)

// Like for : (1 3 5 4 2) is (1 4 2 3 5)
// Step-1 : move from right and check a[i] < a[i+1], ans will be a[0] < a[1]
// Step-2 : then again loop from right and find a[index2] > a[index1], a[3] > a[1], let the value 3 we find in above step as index1
// Step-3 : swap value at index1 and index2, array will look like : (1 4 5 3 2)
// Step-4 : reverse from the right of index1 + 1, like from right of 4, i.e., reverse (5 3 2)


class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i, j;   // Declared outside because we need the index value
        
        // Step-1
        for(i=n-2; i>=0; i--)       // n-2 = (n-1) -1 as we will be checking i < i+1 cndition
            if(nums[i] < nums[i+1])
                break;   
        
        // Check : i<0 means there is no such point means last permutation, so just reverse the whole array
        if(i < 0)  
            reverse(nums.begin(), nums.end());
        
        // Step-2
        else
        {
            for(j=n-1; j>i; j--)
                if(nums[j] > nums[i])
                    break;
        
            // Step-3, 4 : Swap and reverse right of i
            swap(nums[i], nums[j]);
            reverse(nums.begin() + i + 1, nums.end());
        }
    }
};