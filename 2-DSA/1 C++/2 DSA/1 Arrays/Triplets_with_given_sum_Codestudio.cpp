/*
Triplets_with_given_sum_Codestudio
3Sum_Codestudio
3Sum_Leetcode_15
Triplet Sum in Array GFG
Find triplets with zero sum GFG

You are given an array/list ARR consisting of N integers.
Your task is to find all the distinct triplets present in the array which adds up to a given number K.
An array is said to have a triplet {ARR[i], ARR[j], ARR[k]} with sum = 'K' if there exists three indices i, j and k such that i!=j, j!=k and i!=j and ARR[i] + ARR[j] + ARR[k] = 'K'.
*/

// Approach : sort the array and then for every element find remaning pair using two-pointers
// Time : O(N^2)
// Space : O(1)

#include <bits/stdc++.h>
vector<vector<int>> findTriplets(vector<int> arr, int n, int K)
{

    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());
    int left, right;

    for (int i = 0; i < n - 2; i++)
    {
        left = i + 1;
        right = n - 1;
        while (left < right)
        {
            if (arr[left] + arr[right] + arr[i] == K)
            {
                ans.push_back({arr[i], arr[left], arr[right]});
                int x = arr[left];
                int y = arr[right];
                while (left < right && arr[left] == x)
                    left++; // To avoid having same triplet

                while (left < right && arr[right] == y)
                    right--; // To avoid having same triplet
            }
            else if (arr[left] + arr[right] + arr[i] < K)
                left++;

            else
                right--;
        }
        while (i + 1 < n && arr[i] == arr[i + 1])
            i++; // To avoid having same triplet
    }
    return ans;
}