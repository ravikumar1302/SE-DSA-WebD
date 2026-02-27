/*
First_&_Last_Position_of_an_Element_In_Sorted_Array_Codestudio
First and Last Position of an Element In Sorted Array

You have been given a sorted array/list ARR consisting of ‘N’ elements. You are also given an integer ‘K’.
Now, your task is to find the first and last occurrence of ‘K’ in ARR.

Note :
1. If ‘k’ is not present in the array, then the first and the last occurrence will be -1.
2. 'arr' may contain duplicate elements.
*/

// Approach-1 : Binary Search
// Time : O(logN)
#include <vector>
using namespace std;
int firstOcc(vector<int> &arr, int n, int key)
{

    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;
    int ans = -1;
    while (s <= e)
    {

        if (arr[mid] == key)
        {
            ans = mid;
            e = mid - 1; // Different than the last occurence point
        }
        else if (key > arr[mid])
        {
            s = mid + 1;
        }
        else if (key < arr[mid])
        {
            e = mid - 1;
        }

        mid = s + (e - s) / 2;
    }
    return ans;
}

int lastOcc(vector<int> &arr, int n, int key)
{

    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;
    int ans = -1;
    while (s <= e)
    {

        if (arr[mid] == key)
        {
            ans = mid;
            s = mid + 1; // Diifent than the first occurence point
        }
        else if (key > arr[mid])
        {
            s = mid + 1;
        }
        else if (key < arr[mid])
        {
            e = mid - 1;
        }

        mid = s + (e - s) / 2;
    }
    return ans;
}

pair<int, int> firstAndLastPosition(vector<int> &arr, int n, int k)
{
    pair<int, int> p;
    p.first = firstOcc(arr, n, k);
    p.second = lastOcc(arr, n, k);

    return p;
}

// Approach-2  : TLE
// Time : O(N)

#include <bits/stdc++.h>
pair<int, int> firstAndLastPosition(vector<int> &arr, int n, int k)
{

    int first = -1;
    int last = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == k && first == -1)
            first = i;
        if (arr[i] == k && first != -1)
            last = i;
    }

    return {first, last};
}

/*
#include<vector>
using namespace std;

//Using Recursion

int firstOcc(vector<int>& arr, int s, int e, int k,int ans) {
    if(s>e)
        return ans;

    int mid = s + (e-s)/2;

    if(arr[mid]==k)
    {
        ans=mid;
        return firstOcc(arr,s, mid-1, k,ans); //Diifent than the last occurence point
    }
    if(k < arr[mid])
        return firstOcc(arr,s, mid-1, k,ans);
    else
        return firstOcc(arr,mid+1, e, k,ans);

    return ans;
}

int lastOcc(vector<int>& arr,int s, int e, int k,int ans) {
    if(s>e)
        return ans;

    int mid = s + (e-s)/2;

    if(arr[mid]==k)
    {
        ans=mid;
        return lastOcc(arr,mid+1, e, k,ans); //Diifent than the first occurence point
    }
    if(k < arr[mid])
        return lastOcc(arr,s, mid-1, k,ans);
    else
        return lastOcc(arr,mid+1, e, k,ans);

    return ans;
}

pair<int, int> firstAndLastPosition(vector<int>& arr, int n, int k)
{
    pair<int,int> p;
    p.first = firstOcc(arr,0, n-1, k,-1);    //end = n-1
    p.second = lastOcc(arr,0, n-1, k,-1);

    return p;
}
*/
