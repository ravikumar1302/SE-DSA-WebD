/*
Subsets_Leetcode_78
Given an integer array nums of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

    Example 1:
    Input: nums = [1,2,3]
    Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
*/

class Solution {
public:
    void solve(vector<int>& nums, vector<int> output, int index, vector<vector<int>> &ans)
    {
        if(index >= nums.size())    //base case, subsets created
        {
            ans.push_back(output);
            return ;
        }
        
        //Exclude
        solve(nums, output, index+1, ans);
        //Include
        int element =nums[index];
        output.push_back(element);
        solve(nums, output, index+1, ans);
        
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> output;
        int index = 0;
        solve(nums, output, index, ans);
        return ans;
    }
};

/* Using bit manupilation 
        //Striver Video Solution: https://www.youtube.com/watch?v=b7AYbpM5YrE
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > ans;
        int n=nums.size();
        int total=1<<n;
        for(int k=0;k<total;k++)
        {
            vector<int> curr;
            for(int i=0;i<n;i++)
            {
                if(k & (1<<i))
                   curr.push_back(nums[i]); 
            }
            ans.push_back(curr);
        }
        
        return ans;
    }
};
*/