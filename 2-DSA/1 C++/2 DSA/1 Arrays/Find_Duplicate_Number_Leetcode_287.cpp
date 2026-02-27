/*
Find_Duplicate_Number_Leetcode_287

Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.
There is only one repeated number in nums, return this repeated number.
You must solve the problem without modifying the array nums and uses only constant extra space.

Constraint : All the integers in nums appear only once except for precisely one integer which appears two or more times.
*/

class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {

        int n = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            int x = nums[i] % n;
            if (nums[x] > n)
                return nums[i] % n;
            nums[x] += n;
        }
        return 0;
    }
};

// Here bit approach didn't work bcz they played in constraint, the repeated number can be repeated many times. While the bit approach work only for  even no of repetition