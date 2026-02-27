/*
Quick_sort_using_Recursion

Like Merge Sort, QuickSort is a Divide and Conquer algorithm. It picks an element as pivot and partitions the given array around the picked pivot. 

There are many different versions of quickSort that pick pivot in different ways. 
    Always pick first element as pivot.
    Always pick last element as pivot (implemented below)
    Pick a random element as pivot.
    Pick median as pivot.

The key process in quickSort is partition(). Target of partitions is, given an array and an element x of array as pivot, 
put x at its correct position in sorted array and put all smaller elements (smaller than x) before x, and put all greater elements (greater than x) after x. 
All this should be done in linear time.
*/

#include<iostream>
using namespace std;

int partition(int* arr, int s, int e)
{
    int pivot = arr[s];
    int count = 0;
    for(int i = s+1; i <= e; i++)
        if(arr[i] <= pivot)         //countng element smaller than pivot
            count++;
    
    int pivotindex = s + count;     //to place pivot at right position
    swap(arr[s], arr[pivotindex]);

    //to change left and right side
    int i=s, j=e;
    while(i < pivotindex && j > pivotindex)
    {
        while(arr[i] <= pivot)
            i++;
        while(arr[j] > pivot)
            j--;
        if(i < pivotindex && j > pivotindex)
            swap(arr[i++], arr[j--]);
    }
    return pivotindex;
}

void quicksort(int* arr, int s, int e)
{
    if(s >= e)      //base case
        return ;
    int p = partition(arr, s, e);   //creating partition

    quicksort(arr,s,p-1);   //left part
    quicksort(arr,p+1,e);   //right part
}

int main()
{
    int arr[]={10, 3, 2, 5, 5, 7, 60, 9, 0, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    quicksort(arr , 0 , n-1);

    for(int i = 0 ; i < n ; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}