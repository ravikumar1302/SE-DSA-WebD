/*
Contains_duplicate_Leetcode_217

Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

    Example 1:

    Input: nums = [1,2,3,1]
    Output: true
*/

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        
        unordered_map<int,int> mp;
        
        for(int i = 0; i < nums.size(); i++)
            mp[nums[i]]++;
        
        for(auto i = mp.begin(); i != mp.end(); i++)
            if(i ->second >= 2)
                return true;
        
        return false;
    }
};