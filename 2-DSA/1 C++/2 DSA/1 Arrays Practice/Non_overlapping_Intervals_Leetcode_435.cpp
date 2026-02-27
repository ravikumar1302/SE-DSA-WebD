/*
Non_overlapping_Intervals_Leetcode_435

Given an array of intervals intervals where intervals[i] = [starti, endi], 
return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
*/


/*
Approach : we have to sort the intervals on the basis of thier end points, then use a greeady approach to find the answer.

Key Concept : pick interval with smallest end, because smallest end can hold most intervals. keep track of current element end. if next start is more than global end, remove that next element

    1. sort by ending.
    2. keep track of previous end
    3. if the next start > previous end, remove element
    
    example:
    arr : [[1,2],[2,3],[3,4],[1,3]]
    sorted by end: [[1, 2], [2, 3], [1, 3], [3, 4]]

Intervals with lowest end will allow us to fit more intervals
If the previous end is more than the next start, remove it.
Because this means that the interval has a smaller start than previous, but a bigger end which means that its interval is bigger and hence we should remove it
*/

// Time : O(NlogN), due to sorting
// Space : O(1)

bool comp(vector<int> &a, vector<int> &b) 
{
	return a[1] < b[1];
}

class Solution {
public:
	int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        
		int ans=-1;      
		if(intervals.size() == 0) 
            return 0;       
        
		sort(intervals.begin(), intervals.end(), comp);      //custom comperator is used.
		vector<int> prev = intervals[0];

		for(vector<int> i : intervals) 
        {
			if(prev[1] > i[0]) 
				ans++;                //we dont update previous, because i[1] will be grater then prev[1]
			else 
                prev=i;           // we want the end point to be minimum
		}
		return ans;                 //ans was initially made -1 because our prev and intervals[0] will always match
	}
};



// A small variation of Above Code:

static int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        
        if (intervals.size() <= 1) 
            return 0;     
        
		sort(intervals.begin(), intervals.end(), [](const auto& l, const auto& r) { 
            return l[1] < r[1]; 
        });     
		
        int prevIndex = 0;
        int eraseCount = 0;
        
		for (int i = 1; i < intervals.size(); ++i) 
        {
			if (intervals[prevIndex][1] > intervals[i][0]) 
                ++eraseCount;
		    else 
                prevIndex = i;
		}
        
		return eraseCount;
	}