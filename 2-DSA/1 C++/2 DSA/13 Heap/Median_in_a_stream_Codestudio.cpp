/*
Median_in_a_stream_Codestudio

Given that integers are read from a data stream. Your task is to find the median of the elements read so far.
Median is the middle value in an ordered integer list. If the size of the list is even there is no middle value. So the median is the floor of the average of the two middle values.
    
    For Example :
    [2,3,4] - median is 3.
    [2,3] - median is floor((2+3)/2) = 2.

*/

// Median needs sorted data
// But it will give TLE in last case
#include<bits/stdc++.h>
int solve(vector<int> &temp)
{
    int n = temp.size();
    if(n%2 == 1)    // odd
        return temp[n/2];
    else    //even
        return ( temp[n/2] + temp[n/2 - 1] )/2 ;
}

vector<int> findMedian(vector<int> &arr, int n){
	
    vector<int> result;
    vector<int> temp;
    
    for(int i=0; i<n; i++)  
    {
        temp.push_back(arr[i]);
        sort(temp.begin(), temp.end());     // O(NlogN)
        int ans = solve(temp);  
        result.push_back(ans);
    }
    return result;
}
// Overall after loop and sort : time O(N*N*logN)
// Space : O(N)

/************************************************************************************************/

// Optimized Approach
// Time : O(NlogN)
/*
    1. Signum (a,b)
        a == b, returns 0
        a > b, return 1
        a < b, return -1
    
    2. Three possible cases are, where left and right sizes are : (n,n), (n, n-1), (n-1, n),  where n > n-1. So, write switch cases according to that
       Using that push elements in minheap or maxheap

*/

#include<queue>
int signum(int a, int b)
{
    if(a == b) return 0;
    if(a > b) return 1;
    if(a < b) return -1;
}

int call_median(int element, priority_queue<int>& maxi, priority_queue<int, vector<int>, greater<int> >& mini, int &median)
{
    switch( signum(maxi.size(), mini.size()) )
    {
        case 0 :    if(element > median)
                    {
                        mini.push(element);
                        median = mini.top();
                    }
                    else
                    {
                        maxi.push(element);
                        median = maxi.top();
                    }
                    break;
        case 1 :    if(element > median)
                    {
                        mini.push(element);
                        median = ( mini.top() + maxi.top() )/2;
                    }
                    else
                    {
                        mini.push(maxi.top());
                        maxi.pop();
                        maxi.push(element);
                        median = ( mini.top() + maxi.top() )/2;
                    }
                    break;
        case -1 :   if(element > median)
                    {
                        maxi.push(mini.top());
                        mini.pop();
                        mini.push(element);
                        median = ( mini.top() + maxi.top() )/2;
                    }
                    else
                    {
                        maxi.push(element);
                        median = ( mini.top() + maxi.top() )/2;
                    }
                    break; 
    }
}

vector<int> findMedian(vector<int> &arr, int n){
	
    priority_queue<int> maxheap;
    priority_queue<int, vector<int>, greater<int> > minheap;
    int median = -1;
    vector<int> ans;
    
    for(int i=0; i<n; i++)
    {
        call_median(arr[i], maxheap, minheap, median);
        ans.push_back(median);
    }
    return ans;
}
// Time : O(NlogN)