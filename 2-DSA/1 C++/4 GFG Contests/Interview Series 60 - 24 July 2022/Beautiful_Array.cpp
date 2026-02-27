/* 
Make the Beautiful Array

Given an array of positive and negative integers. You have to make the array beautiful. An array is beautiful if two adjacent integers,arr[i] and arr[i+1] have the same sign.
And you can do the following operation any number of times untill the array becomes beautiful.
    If two adjacent integers have differnet signs, remove them.
Return the beautiful array.

Note: An empty array is also beautiful arrray. Removve adjacent intgers with differnet signs from left to right

*/

// All cases Passed

class Solution {
  public:
    vector<int> makeBeautiful(vector<int> arr) {
        
        int n = arr.size();
        vector<int> ans;
        // Edge case
        if(n == 1)
        {
            ans.push_back(arr[0]);
            return ans;
        }
        
        stack<int> s;
        s.push(arr[0]);
        
        for(int i=1; i<n; i++)
        {
            if(s.empty())
                s.push(arr[i]);

            else if(s.top() >= 0 && arr[i] >= 0)
                s.push(arr[i]);
            else if(s.top() < 0 && arr[i] < 0)
                s.push(arr[i]);   
            else
                s.pop();
        }
        
        while(!s.empty())
        {
            ans.push_back(s.top());
            s.pop();
        }
        
        reverse(ans.begin(), ans.end());
        return ans;
    }
};