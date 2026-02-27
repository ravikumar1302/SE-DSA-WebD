/*
Insertion_sort_using_recursion

With ith iteration, array gets sorted till ith position. 
In this, elements are shifted, not swapped.

i = 1    [ 3  8  5  4  1  9  -2 ]
i = 2    [ 3  8  5  4  1  9  -2 ]           
i = 3    [ 3  5  8  4  1  9  -2 ]              
i = 4    [ 3  4  5  8  1  9  -2 ]
i = 5    [ 1  3  4  5  8  9  -2 ]
i = 6    [ 1  3  4  5  8  9  -2 ]
         [ -2  1  3  4  5  8  9 ]

*/

#include<iostream>
using namespace std;
void insertionsort(int arr[] , int i , int size)
{
    if(i+1 > size)        //base case, already sorted
    return ;

    //Solving 1st case, first larget element in last

    int j = i -1 ;    //minimum index arr[0] for each iteration
    int temp=arr[i];    //saving value in temp

    for(; j > 0 ; j--) 
    {
        if(arr[j] > arr[temp])
                    arr[j+1] = arr[j];  //(j+1) value shifted
        else
            break;
    }
    arr[j+1] = temp;    //now putting the needed value at it's right location
        
    //Now, recusrion
    insertionsort(arr , i + 1 , size);

}
int main()
{
    int arr[]={10,8,6,4,2};
    int n = sizeof(arr) / sizeof(arr[0]);
    insertionsort(arr , 1 , n);

    for(int i = 0 ; i < 5 ; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}