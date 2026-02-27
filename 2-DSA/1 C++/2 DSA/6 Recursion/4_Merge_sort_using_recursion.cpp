/*
Merge_sort_using_recursion

Merge Sort Algorithm -
Merge sort is a Divide and Conquer based Algorithm. 
It divides the input array into two-parts, until the size of the input array is not ‘1’. 
In the return part, it will merge two sorted arrays a return a whole merged sorted array.

Merge sort is faster than bubble sort, selection sort and insertion sort
*/

#include<iostream>
using namespace std;

void merge(int *arr, int s, int e)
{
    int mid = s + (e - s) / 2;
    int len1 = mid - s + 1; //left part length
    int len2 = e - mid;   //right part length

    int *first = new int[len1];
    int *second = new int[len2];

    int mainarrayindex = s;    //copying values from main array
    for(int i = 0; i<len1; i++)
        first[i] = arr[mainarrayindex++];
    
    mainarrayindex = mid+1;    //copying values from main array
    for(int i = 0; i<len2; i++)
        second[i] = arr[mainarrayindex++];
    
    //merge 2 sorted arrays
    int index1 = 0;
    int index2 = 0;
    mainarrayindex = s;

    while(index1 < len1 && index2 < len2)
    {
        if(first[index1] < second[index2])
            arr[mainarrayindex++] = first[index1++];
        else
            arr[mainarrayindex++] = second[index2++];
    }
    while(index1 < len1)
        arr[mainarrayindex++] = first[index1++];
    while(index2 < len2)
        arr[mainarrayindex++] = second[index2++];

    delete []first;
    delete []second;
}

void mergesort(int *arr, int s, int e)
{
    if(s >= e)        //base case, already sorted
        return ;
    int mid = s + (e - s) / 2;
    mergesort(arr, s, mid);      //sorting left half
    mergesort(arr, mid+1, e);   //sorting right half
    merge(arr, s, e);
}

int main()
{
    int arr[]={2,50,3,4,5,2,66,78,89,3,8,12,12,15,0, 45};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergesort(arr, 0, n-1);

    for(int i = 0 ; i <n ; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}

// T.C. : O ( NlogN )
// S.C> : O ( N )