
// Sort_012_Codestudio
// Sort An Array of 0s, 1s and 2s_Codestudio

/*
You have been given an integer array/list(ARR) of size 'N'. It only contains 0s, 1s and 2s. Write a solution to sort this array/list.

Note :
Try to solve the problem in 'Single Scan'. ' Single Scan' refers to iterating over the array/list just once or to put it in other words, you will be visiting each element in the array/list just once.
*/

#include <bits/stdc++.h>
void sort012(int *arr, int n)
{
    int left = 0, mid = 0, right = n - 1;

    while (mid <= right)
    {
        if (arr[mid] == 0)
        {
            swap(arr[mid], arr[left]);
            left++;
            mid++;
        }
        else if (arr[mid] == 1)
            mid++;
        else if (arr[mid] == 2)
        {
            swap(arr[mid], arr[right]);
            right--;
        }
    }
}