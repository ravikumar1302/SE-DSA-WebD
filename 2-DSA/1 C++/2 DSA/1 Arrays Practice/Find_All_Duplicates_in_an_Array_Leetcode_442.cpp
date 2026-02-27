/*
Find_All_Duplicates_in_an_Array_Leetcode_442

Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears once or twice, return an array of all the integers that appears twice.

You must write an algorithm that runs in O(n) time and uses only constant extra space.

    Example 1:
    Input: nums = [4,3,2,7,8,2,3,1]
    Output: [2,3]
*/

vector<int> findDuplicates(vector<int> &nums)
{
    vector<int> ans;
    int n = nums.size();
    int freq[100001] = {0};

    for (int i = 0; i < n; i++)
        freq[nums[i]]++;

    for (int i = 0; i < 100000; i++)
        if (freq[i] == 2)
            ans.push_back(i);

    return ans;
}

// Approach 2
// Better than above solution (as space not using 100001)
vector<int> findDuplicates(vector<int> &nums)
{
    vector<int> ans;

    unordered_map<int, int> freq;
    for (auto val : nums)
        freq[val]++;

    for (auto val : freq)
        if (val.second == 2)
            ans.push_back(val.first);

    return ans;
}