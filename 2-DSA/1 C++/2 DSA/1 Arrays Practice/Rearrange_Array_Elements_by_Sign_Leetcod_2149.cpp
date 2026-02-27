/*
Rearrange_Array_Elements_by_Sign_Leetcod_2149
Rearrange array in alternating positive & negative items with O(1) extra space_GFG

You are given a 0-indexed integer array nums of even length consisting of an equal number of positive and negative integers.

You should rearrange the elements of nums such that the modified array follows the given conditions:
    Every consecutive pair of integers have opposite signs. 
    For all integers with the same sign, the order in which they were present in nums is preserved.
    The rearranged array begins with a positive integer

Return the modified array after rearranging the elements to satisfy the aforementioned conditions.


    Example 1:

    Input: nums = [3,1,-2,-5,2,-4]
    Output: [3,-2,1,-5,2,-4]
    Explanation : The positive integers in nums are [3,1,2]. The negative integers are [-2,-5,-4]. The only possible way to rearrange them such that they satisfy all conditions is [3,-2,1,-5,2,-4].
    Other ways such as [1,-2,2,-5,3,-4], [3,1,2,-2,-5,-4], [-2,3,-5,1,-4,2] are incorrect because they do not satisfy one or more conditions.  

*/


// Brute force Approach : Copy positive and negative number in separate arrays and then enter elements alternatively in ans vecctor
// Time and space: O(N)

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
       
        vector <int> pos,neg;
        for(int i=0; i<nums.size(); i++)
        {
            if(nums[i]<0)
                neg.push_back(nums[i]);
             else 
                pos.push_back(nums[i]);
            
        }
        
        int p=0, n=0;
        vector<int>ans;
        while(p < pos.size() && n < neg.size())
        {
            ans.push_back(pos[p++]);
            ans.push_back(neg[n++]);
        }
        return ans;
    }
};


// Optimized Approach
// This approach will inly work if equal no of positive and negative are there
// Time : O(N)
// Space : O(1) // excluding space taken by ans vector

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int pos_index = 0;  
        int neg_index = 1;
        vector<int> ans(nums.size());
        for(int i=0; i<nums.size(); i++)
        {
            if(nums[i] > 0)
            {
                ans[pos_index] = nums[i];
                pos_index = pos_index+2;
            }
            if(nums[i] < 0)
            {
                ans[neg_index] = nums[i];
                neg_index = neg_index+2;
            }
        }
        
        return ans;
    }
};