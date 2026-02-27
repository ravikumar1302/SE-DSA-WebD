/*
Subarray_Sum_Equals_K_Leetcode_560

Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.

    Example 1:
    Input: nums = [1,1,1], k = 2
    Output: 2

    Example 2:
    Input: nums = [1,2,3], k = 3
    Output: 2
*/


// Optimized Approach : Concept of Prefix 
// Time : O(N)
// Space: O(N)

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        
        int n = nums.size();
        
        int prefix[n];      // prefix array to store prefix sum
        prefix[0] = nums[0]; 
        
        for(int i = 1; i < n; i++)
            prefix[i] = nums[i] + prefix[i - 1];
        
        unordered_map<int,int> mp; 
        int ans = 0;
        
        for(int i = 0; i < n; i++)
        {
            if(prefix[i] == k)      // if it already becomes equal to k, then increment ans
                ans++;
            
            // Find whether (prefix[i] - k) present in map or not
            if(mp.find(prefix[i] - k) != mp.end())
                ans += mp[prefix[i] - k];       // if yes, then add it our answer
            
            mp[prefix[i]]++; 
        }
        
        return ans;
    }
};

// Variation of above code, without prefix array

int subarraySum(vector<int>& nums, int k) {
        
        int sum=0;
        int count=0;
        
        unordered_map<int,int>m;
        
        for(int i=0;i<nums.size();i++)
        {
            sum+=nums[i];
            if(sum==k)
                count++;
            if(m.find(sum-k)!=m.end())
                count+=m[sum-k];
            m[sum]++;
        }
        return count;
    }

/***********************************************************************************/

// Brute force : TLE will occur
// Time : O(N^2)
// Space : O(1)

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        
        int n = nums.size();
        int count = 0; 
        
        for(int i = 0; i < n; i++) 
        {
            int sum = nums[i];
            
            if(sum == k)    // if element itself equal to k, then also increment count
                count++;
            
            for(int j = i + 1; j < n; j++) 
            {
                sum += nums[j];     
                
                if(sum == k)    // if at any point they become equal to k, increment answer
                    count++; 
            }
        }
        
        return count; 
    }
};