/*
N_meetings_in_one_room_GFG

There is one meeting room in a firm. There are N meetings in the form of (start[i], end[i]) where start[i] is start time of meeting i and end[i] is finish time of meeting i.
What is the maximum number of meetings that can be accommodated in the meeting room when only one meeting can be held in the meeting room at a particular time?

Note: Start time of one chosen meeting can't be equal to the end time of the other chosen meeting.

    Example 1:
    Input: N = 6, start[] = {1,3,0,5,8,5}, end[] =  {2,4,6,7,9,9}
    Output: 4
    Explanation: Maximum four meetings can be held with given start and end timings. The meetings are - (1, 2),(3, 4), (5,7) and (8,9)

    Example 2:
    Input: N = 3,  start[] = {10, 12, 20},  end[] = {20, 25, 30}
    Output: 1
    Explanation: Only one meetings can be held with given start and end timings.

Expected Time Complexity : O(N*LogN)
Expected Auxilliary Space : O(N)
*/

// Approach : The sooner the meeting completes, more meeting can happen, so sort the data on basis of end time
// Time : O(N) + O(NlogN) + O(N) = O(NlogN)     // saving in data structure, sorting, traversing
// Space : O(N)     // To store data in other DS

class Solution
{
    public:
    static bool comp(pair<int,int> a, pair<int,int> b)
    {
        if(a.second == b.second)
        {
            return a.first < b.first;
        }
        return a.second < b.second;
    }
    
    int maxMeetings(int start[], int end[], int n)
    {
        
        // Step-1 : Store the given data
        vector<pair<int,int>> temp(n);
        for(int i=0; i<n; i++)
            temp[i] = {start[i], end[i]};
        
        // Step-2 :  Sort on basis of end time
        sort(temp.begin(), temp.end(), comp);
        
        // Step-3 : Caclulatig ans
        int count = 1;
        int limit = temp[0].second;
        for(int i=1; i<n; i++)
        {
            if(limit < temp[i].first)
            {
                limit = temp[i].second;
                count++;
            }
        }
        
        return count;
    }
};