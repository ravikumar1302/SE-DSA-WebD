
// Binary_Search_Practice


#include<iostream>
using namespace std;

bool binarysearch(int arr[], int s, int e, int key)
{
    if(s > e)             //false condition
        return false;
    int mid = s + (e - s) / 2;
    if(arr[mid] == key)   //base case
        return true;
    if(arr[mid] < key)
        return binarysearch(arr, mid+1, e, key);
    else
        return binarysearch(arr, s, mid-1, key);
}
int main()
{
    int arr[]={1, 2, 5, 7, 10};
    int size=5;
    int key=2;

    cout<<"Present "<<binarysearch(arr, 0, 4, key)<<endl;
 
    
    return 0;
}

// T.C. : O ( logN )
// S.C. : O ( logN )