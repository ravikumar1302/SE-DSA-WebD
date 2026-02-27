/*
Two_Sum_Leetcode_1

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

    Example 1:
    Input: nums = [2,7,11,15], target = 9
    Output: [0,1]
    Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 

Follow-up: Can you come up with an algorithm that is less than O(n^2) time complexity?
*/

// Time : O(N^2)
// Space : O(1)

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        int n=nums.size();
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(nums[i]+nums[j]==target)
                {
                    ans.push_back(i);
                    ans.push_back(j);
                    return ans;
                }
            }
        }
        return ans;
    }
};


/*****************************************************************************************************/
// Optimized Appraoch : Using Hashmap
// Time : O(N)
// Space : O(N)

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
     vector<int> ans;
     unordered_map<int,int> mp;
        
     for(int i=0; i<nums.size(); i++)
     {
         if(mp.find(target-nums[i]) != mp.end())
         {
             ans.push_back(mp[target-nums[i]]);
             ans.push_back(i);
             return ans;
         }
         
         // If not found, add in map
         mp[nums[i]] = i;
     } 
     return ans;  
    }
};