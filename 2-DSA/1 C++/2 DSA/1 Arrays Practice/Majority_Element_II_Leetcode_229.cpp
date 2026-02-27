/*
Majority_Element_II_Leetcode_229
Majority Element III_Codestudio
Given an array of size n and a number k, find all elements that appear more than n/k times_GFG


Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Example 1:
Input: nums = [3,2,3]
Output: [3]


Follow up: Could you solve the problem in linear time and in O(1) space? 
*/

// Time : O(N)
// Space : O(N)

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
       
        unordered_map<int, int> mp;
        vector<int> ans;
        
        // Pushing all elemnts in map
        for(int i=0; i<nums.size(); i++)
            mp[nums[i]]++;
        
        // Traversing map
        for (auto it : mp)
            if(it.second > nums.size()/3)
                ans.push_back(it.first);
        
        return ans;
    }
};


/********************************************************************************/

// Optimized Approach : Boyer-Moore Majority Vote algorithm
// Time : O(N)
// Space : O(1)
