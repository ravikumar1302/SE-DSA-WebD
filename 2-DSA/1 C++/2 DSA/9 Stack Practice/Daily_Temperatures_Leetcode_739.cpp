/*
Daily_Temperatures_Leetcode_739

Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

    Example 1:
    Input: temperatures = [73,74,75,71,69,72,76,73]
    Output: [1,1,4,2,1,1,0,0]
    Example 2:
    Input: temperatures = [30,40,50,60]
    Output: [1,1,1,0]
    Example 3:
    Input: temperatures = [30,60,90]
    Output: [1,1,0]


Constraints:

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
*/

// Time &Space : O(N)

vector<int> dailyTemperatures(vector<int> &temperatures)
{

    int n = temperatures.size();
    vector<int> ans(n, 0);
    deque<int> d;

    for (int i = n - 1; i >= 0; i--)
    {
        if (d.empty())
        {
            d.push_front(i);
            ans[i] = 0;
        }
        else
        {
            while (!d.empty() && temperatures[i] >= temperatures[d.front()])
                d.pop_front();
            if (d.empty())
                ans[i] = 0;
            else
                ans[i] = d.front() - i;

            d.push_front(i);
        }
    }
    return ans;
}