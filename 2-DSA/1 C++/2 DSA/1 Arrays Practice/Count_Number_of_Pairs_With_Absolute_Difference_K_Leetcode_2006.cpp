/*
Count_Number_of_Pairs_With_Absolute_Difference_K_Leetcode_2006
Given an integer array nums and an integer k, return the number of pairs (i, j) where i < j such that |nums[i] - nums[j]| == k.

    The value of |x| is defined as:
        x if x >= 0.
        -x if x < 0.
    
    Example 1:
    Input: nums = [1,2,2,1], k = 1
    Output: 4

*/

class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        
        int count = 0;
        int n = nums.size();
        for(int i = 0; i < n; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                int value = abs(nums[i] - nums[j]);
                if(value == k)
                    count++;
            }
        }
        return count;
    }
};

// S.C. = O (1)
// T.C. = O (n^2)

/*
//Using Recursion

class Solution {
public:
    void differ(vector<int>& nums, int k, int i, int& count, int n)
    {
        if(i+1 > n)   //base case
            return ;
        for(int j = i+1; j < n; j++)    //checking for 1st case
            {
                int value = abs(nums[i] - nums[j]);
                if(value == k)
                    count++;
            }
        differ(nums, k, i+1, count, n);    //Recursive call
    }
    
    int countKDifference(vector<int>& nums, int k) {
        
        int count = 0;
        int n = nums.size();
        differ(nums, k, 0, count, n);

        return count;
    }
};
*/