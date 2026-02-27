/*
Majority_Element_Leetcode_169
Majority_Element_GFG

Given an array nums of size n, return the majority element.
The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

    Example 1:
    Input: nums = [3,2,3]
    Output: 3

Follow-up: Could you solve the problem in linear time and in O(1) space?
*/


// Approach-3 : Best Solution : Linear time and O(1) Space 
                // Use 2 variables to count the frequency of elementts

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        
        int ans = nums[0], cnt = 1;
        for(int i=1; i<nums.size(); i++)
        {
            if(ans == nums[i])
                cnt++;
            else if(cnt == 0)
            {
                cnt++;
                ans = nums[i];
            }
            else    // means the nums[i] !=ans && cnt != 0
                cnt--;
        }
        
        // return ans;       // It will pass the Leetcode test case, But for GFG test cases, below written code is also needed
        
        // We have potential ans, let's verify it
        int temp = 0;
        for(int i=0; i<nums.size(); i++)

            if(nums[i] == ans)
                temp++;
        
        // Return ans
        if(temp <= nums.size()/2 )
            return -1;
            
        return ans;
        
    }
}; 



// Apprach-2 : Linear Time and O(N) Space : Use hashmap to store the frequency of each element and then return the ans with most frequenccy
int majorityElement(int a[], int size)
    {
        
        map<int, int> mp;
        for(int i=0; i<size; i++)
        {
            mp[a[i]]++;
            if(mp[a[i]] > size/2)
                return a[i];
        }
        return -1;
        
    }

// Approcah-1 : O(nlogn) time and O(1) space : Sort the array, as major element is MORE than N/2 time, it will be present at index N/2 or ans = nums[N/2]