/*
Bubble_sort_using_recursion

With every ith pass, (n-i)th largest element get placed at it's right (last-i)th position

               3     5     8     4     1     9    -2 
pass 1         3     5     4     1     8    -2     9
pass 2         3     4     1     5    -2     8     9
pass 3         3     1     4    -2     5     8     9
pass 4         1     3    -2     4     5     8     9
pass 5         1    -2     3     4     5     8     9
pass 6        -2     1     3     4     5     8     9

*/

#include<iostream>
using namespace std;
void bubblesort(int arr[] , int size)
{
    if(size==0 || size ==1)        //base case, already sorted
    return ;

    //Solving 1st case, first larget element in last
    for(int i = 0 ; i < size-1 ; i++) 
        if(arr[i] > arr[i+1])
            swap(arr[i] , arr[i+1]);

    //Now, recusrion
    bubblesort(arr , size-1);

}
int main()
{
    int arr[]={10,8,6,4,2};
    bubblesort(arr , 5);

    for(int i = 0 ; i < 5 ; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}