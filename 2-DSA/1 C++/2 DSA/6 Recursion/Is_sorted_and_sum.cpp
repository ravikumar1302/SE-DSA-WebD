/*
Is_sorted_and_sum

Problems solved using Recursion
1. Is array sorted
2. Sum of Array
*/

#include<iostream>
using namespace std;

int getsum(int arr[], int size)
{
    if(size==0) return 0;
    if(size==1) return arr[0];
    return arr[0]+getsum(arr+1,size-1);
}
bool issorted(int arr[], int size)
{
    if(size == 0 || size == 1)  //base case
        return true;
    
    if(arr[0]>arr[1])
        return false;
    else
        return issorted(arr+1,size-1);
}
int main()
{
    int arr[]={1,2,5,7,10};
    int size=5;
    bool ans=issorted(arr,size);
    if(ans)
        cout<<"Array  is sorted"<<endl;
    else
        cout<<"Array  is not sorted";
    
    cout<<"Sum of Array is "<<getsum(arr,size);
    return 0;
}