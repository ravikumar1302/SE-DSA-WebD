/*
Pair_Sum_Codestudio

You are given an integer array 'ARR' of size 'N' and an integer 'S'.
Your task is to return the list of all pairs of elements such that each sum of elements of each pair equals 'S'.
*/

// Approach-1
// Time : O(N*N)
#include <bits/stdc++.h>
vector<vector<int>> pairSum(vector<int> &arr, int s)
{
    vector<vector<int>> ans;
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[i] + arr[j] == s)
            {
                vector<int> temp;
                temp.push_back(min(arr[i], arr[j]));
                temp.push_back(max(arr[i], arr[j]));
                ans.push_back(temp);
            }
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

// Approach-2
// Time : O(N*N)
#include <bits/stdc++.h>
vector<vector<int>> pairSum(vector<int> &arr, int s)
{
    vector<vector<int>> ans;
    int n = arr.size();
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++)
    {
        int temp = arr[i];
        for (int j = n - 1; j >= 0 && j > i; j--)
        {
            if (temp + arr[j] == s)
                ans.push_back({temp, arr[j]});
            else if (temp + arr[j] > s)
                continue;
            else
                break;
        }
    }
    return ans;
}