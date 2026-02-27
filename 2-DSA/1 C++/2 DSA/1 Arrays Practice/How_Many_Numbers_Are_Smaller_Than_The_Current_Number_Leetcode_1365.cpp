/*
How_Many_Numbers_Are_Smaller_Than_The_Current_Number_Leetcode_1365

Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it. That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].
Return the answer in an array.

        Example 1:

        Input: nums = [8,1,2,2,3]
        Output: [4,0,1,1,3]
        Explanation:
        For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3).
        For nums[1]=1 does not exist any smaller number than it.
        For nums[2]=2 there exist one smaller number than it (1).
        For nums[3]=2 there exist one smaller number than it (1).
        For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).
        Example 2:

        Input: nums = [6,5,4,8]
        Output: [2,1,0,3]
        Example 3:

        Input: nums = [7,7,7,7]
        Output: [0,0,0,0]


        Constraints:

        2 <= nums.length <= 500
        0 <= nums[i] <= 100

*/

// Method-1
// T.C.: O(N^2)

class Solution
{
public:
    vector<int> smallerNumbersThanCurrent(vector<int> &nums)
    {

        vector<int> ans;
        for (int i = 0; i < nums.size(); i++)
        {
            int cnt = 0;
            for (int j = 0; j < nums.size(); j++)
            {
                if (nums[j] < nums[i] && i != j)
                    cnt++;
            }
            ans.push_back(cnt);
        }

        return ans;
    }
};

// Method-2
// T.C.: O(n*logn)

class Solution
{
public:
    vector<int> smallerNumbersThanCurrent(vector<int> &nums)
    {
        vector<int> ans = nums;
        unordered_map<int, int> m;
        sort(ans.begin(), ans.end());
        for (int i = nums.size() - 1; i >= 0; i--)
            m[ans[i]] = i;
        for (int i = 0; i < nums.size(); i++)
            nums[i] = m[nums[i]];
        return nums;
    }
};