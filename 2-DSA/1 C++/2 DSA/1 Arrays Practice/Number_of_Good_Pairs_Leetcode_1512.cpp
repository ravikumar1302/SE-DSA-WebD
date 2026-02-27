
/*
Number_of_Good_Pairs_Leetcode_1512

Given an array of integers nums, return the number of good pairs.
A pair (i, j) is called good if nums[i] == nums[j] and i < j.

        Example 1:

        Input: nums = [1,2,3,1,1,3]
        Output: 4
        Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.
        Example 2:

        Input: nums = [1,1,1,1]
        Output: 6
        Explanation: Each pair in the array are good.
        Example 3:

        Input: nums = [1,2,3]
        Output: 0

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100

*/

// Method-1
// S.C. = O (1)
// T.C. = O (n^2)

class Solution
{
public:
    int numIdenticalPairs(vector<int> &nums)
    {

        int cnt = 0;
        for (int i = 0; i < nums.size(); i++)
            for (int j = i + 1; j < nums.size(); j++)
                if (nums[i] == nums[j])
                    cnt++;

        return cnt;
    }
};

// Method-2 : Time optimized
// S.C. = O (1)
// T.C. = O (n)

class Solution
{
public:
    int numIdenticalPairs(vector<int> &nums)
    {

        int cnt = 0;
        unordered_map<int, int> mp;

        for (int i : nums)
            cnt += mp[i]++;

        return cnt;
    }
};