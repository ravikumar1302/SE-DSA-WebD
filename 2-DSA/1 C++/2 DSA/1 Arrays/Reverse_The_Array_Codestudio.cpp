/*
Reverse_The_Array_Codestudio

Given an array 'ARR' of integers and a position 'M'. You have to reverse the array after that position.
*/

// Appraoch-1
#include<bits/stdc++.h>
void reverseArray(vector<int> &arr , int m)
{
	reverse(arr.begin()+m+1,arr.end());
}


// Appraoch-2
#include <bits/stdc++.h> 
void reverseArray(vector<int> &arr , int m)
{
	int n = arr.size();
    int k = 0;
    for(int i=m+1; i<n-k; i++)
    {
        swap(arr[i], arr[n -1 -k]);
        k++;
    } 
}


// Appraoch-3
#include<bits/stdc++.h>
void reverseArray(vector<int> &arr , int m)
{
    int s=m+1;
    int e=arr.size()-1;
    while(s<=e)
    {
        swap(arr[s],arr[e]);
        s++;
        e--;
    }
}
