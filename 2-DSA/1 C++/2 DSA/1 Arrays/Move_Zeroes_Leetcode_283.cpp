/*
Move_Zeroes_Leetcode_283
Move all zeroes to end of array GFG

Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

    Example 1:
    Input: nums = [0,1,0,3,12]
    Output: [1,3,12,0,0]

Follow up: Could you minimize the total number of operations done?
*/


class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        
        int i = 0, j = 0;
        
        while(j < nums.size())
        {
            if(nums[j] != 0)
                swap(nums[j++], nums[i++]);

            else
                j++;
        }
    }
};

/********************************************************************************/
// Using for loop

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i=0;
        for(int j=0;j<nums.size();j++)
        {
            if(nums[j]!=0)
            {
                swap(nums[j],nums[i]);  
                i++;
            }

            
        }
        
    }
};
