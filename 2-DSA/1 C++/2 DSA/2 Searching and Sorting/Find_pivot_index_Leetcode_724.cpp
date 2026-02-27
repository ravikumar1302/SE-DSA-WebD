/*
Find_pivot_index_Leetcode_724
Find the Middle Index in Array_Leetcode_1991

Given an array of integers nums, calculate the pivot index of this array.
The pivot index is the index where the sum of all the numbers strictly to the left of the index is equal to the sum of all the numbers strictly to the index's right.
If the index is on the left edge of the array, then the left sum is 0 because there are no elements to the left. This also applies to the right edge of the array.
Return the leftmost pivot index. If no such index exists, return -1.
*/

// Approach-1

class Solution
{
public:
    int pivotIndex(vector<int> &nums)
    {
        if (nums.size() == 0)
            return -1;

        int n = nums.size();
        int totalsum = 0, leftsum = 0;

        for (int i : nums)
            totalsum += i;

        for (int i = 0; i < n; i++)
        {
            if (leftsum == (totalsum - nums[i]))
                return i;
            else
            {
                leftsum += nums[i];
                totalsum -= nums[i];
            }
        }

        return -1;
    }
};

// Approach-2 : Using Recursion

class Solution
{
public:
    int helper(vector<int> &nums, int index, int leftsum, int totalsum)
    {

        if (index == nums.size())
            return -1;

        if (leftsum == totalsum - leftsum - nums[index])
            return index;

        return helper(nums, index + 1, leftsum + nums[index], totalsum);
    }

    int pivotIndex(vector<int> &nums)
    {

        int totalSum = 0;
        for (int x : nums)
            totalSum += x;

        return helper(nums, 0, 0, totalSum);
    }
};
