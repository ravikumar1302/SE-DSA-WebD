/*
Peak_index_in_a_mountain_array_Leetcode_852
Bitonic Point_GFG

Let's call an array arr a mountain if the following properties hold:

1. arr.length >= 3
2. There exists some i with 0 < i < arr.length - 1 such that:
    arr[0] < arr[1] < ... arr[i-1] < arr[i]
    arr[i] > arr[i+1] > ... > arr[arr.length - 1]
Given an integer array arr that is guaranteed to be a mountain, return any i such that arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1].
*/

class Solution
{
public:
    int peakIndexInMountainArray(vector<int> &arr)
    {
        int s = 0, e = arr.size() - 1;
        int mid = s + (e - s) / 2;
        while (s < e)
        {
            if (arr[mid] < arr[mid + 1])
                s = mid + 1;
            else
                e = mid;

            mid = s + (e - s) / 2;
        }
        return s;
    }
};

/*

class Solution {
public:

    //Using Recursion

    int peak(vector<int>& arr, int n, int s, int e){
        int mid=s+(e-s)/2;
        if((mid == 0 || arr[mid-1] <= arr[mid]) && (mid == n-1 || arr[mid] >= arr[mid+1]))
            return mid;
        else if(mid>0 && arr[mid-1]>=arr[mid])  //On decreasing line
            return peak(arr, n, s, mid-1);
        else
            return peak(arr, n, mid+1, e);
    }

    int peakIndexInMountainArray(vector<int>& arr) {
        int s=0;
        int n=arr.size();
        int e=n-1;
        int p=peak(arr, n, s, e);
        return p;
    }
};
*/