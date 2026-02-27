/*
Merge_Intervals_Leetcode_56

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

    Example 1:
    Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
    Output: [[1,6],[8,10],[15,18]]
    Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        int n = intervals.size();
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
        
        int l = intervals[0][0] , r = intervals[0][1];
        
        for(int i=1 ; i<n ; i++) 
        {
            if(intervals[i][0] <= r) 
            {
                if(intervals[i][1] >= r) 
                    r = intervals[i][1];
            } 
            
            else 
            {
                ans.push_back({l , r});
                l = intervals[i][0];
                r = intervals[i][1];
            }
        }
        ans.push_back({l , r});
        return ans;
    }