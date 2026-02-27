/*
Find_All_K-Distant_Indices_in_an_Array_Leetcode_2200

You are given a 0-indexed integer array nums and two integers key and k. A k-distant index is an index i of nums for which there exists at least one index j such that |i - j| <= k and nums[j] == key.
Return a list of all k-distant indices sorted in increasing order.

    Example 1:

    Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
    Output: [1,2,3,4,5,6]
    Explanation: Here, nums[2] == key and nums[5] == key.
    - For index 0, |0 - 2| > k and |0 - 5| > k, so there is no j where |0 - j| <= k and nums[j] == key. Thus, 0 is not a k-distant index.
    - For index 1, |1 - 2| <= k and nums[2] == key, so 1 is a k-distant index.
    - For index 2, |2 - 2| <= k and nums[2] == key, so 2 is a k-distant index.
    - For index 3, |3 - 2| <= k and nums[2] == key, so 3 is a k-distant index.
    - For index 4, |4 - 5| <= k and nums[5] == key, so 4 is a k-distant index.
    - For index 5, |5 - 5| <= k and nums[5] == key, so 5 is a k-distant index.
    - For index 6, |6 - 5| <= k and nums[5] == key, so 6 is a k-distant index.
    Thus, we return [1,2,3,4,5,6] which is sorted in increasing order.
*/

class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        
        int count = 0;
        int n = nums.size();
        vector<int> indices;    //for storing indexes of nums[j] == key
        vector<int> ans;
        
        for(int i = 0; i < n; i++)
            if(nums[i] == key)
                indices.push_back(i); 
        
        int len = indices.size();
        
        // Now, the calulation part
        for(int i = 0; i < n; i++)
        {
            for(int j =0; j < len; j++)
            {
                if( abs(i - indices[j]) <= k )
                {
                    ans.push_back(i);
                    break;              //so that same indicx don't appear again
                }
            }
        }
        
        return ans;
        
    }
};