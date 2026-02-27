/*
Largest_Rectangle_in_Histogram_Leetcode_84

Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

    Example 1:
    Input : heights = [2,1,5,6,2,3]
    Output : 10
    Explanation : The above is a histogram where width of each bar is 1. The largest rectangle is shown in the red area, which has an area = 10 units.
*/

class Solution {
private:
    vector<int> nextSmaller(vector<int> heights, int n)
    {
        // IMPORTANT: go from right to left rather than left to right, to reduce itreations
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);

        for(int i=n-1; i>=0; i--)
        {
            int curr = heights[i];
            
            while(s.top() != -1 && heights[s.top()] >= curr)
                s.pop();
            
            //Now s.top() is smaller than curr
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }
    
    vector<int> prevSmaller(vector<int> heights, int n)
    {
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);

        for(int i=0; i<n; i++)      // Only this for loop condition are different from next smaller
        {
            int curr = heights[i];
            
            while(s.top() != -1 && heights[s.top()] >= curr)
                s.pop();
            
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }
    
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        
        vector<int> next(n);
        next = nextSmaller(heights, n);
        
        vector<int> prev(n);
        prev = prevSmaller(heights, n);
        
        int area = INT_MIN;
        for(int i =0; i<n; i++)
        {
            int l = heights[i];
            
            if(next[i] == -1)
                next[i] = n;
            
            int b = next[i] - prev[i] -1;
            int newArea = l*b;
            
            area = max(area, newArea);
        }
        return area;
    }
};

// T.C. : O(N)