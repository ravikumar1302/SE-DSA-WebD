/*
Selection_sort_using_recursion

With ith pass, the remaing array smallest element get placed at its right (left+i)th position

            3  5  8  4  1  9 -2
i = 0      -2  5  8  4  1  9  3
i = 1      -2  1  8  4  5  9  3
i = 2      -2  1  3  4  5  9  8
i = 3      -2  1  3  4  5  9  8
i = 4      -2  1  3  4  5  9  8
i = 5      -2  1  3  4  5  8  9

*/

#include<iostream>
using namespace std;
void selectionsort(int arr[] , int i , int size)
{

    if(i + 1 > size)        //base case, already sorted
    return ;

    //Solving 1st case, first larget element in last

    int pos = i;    //minimum index arr[0] for each iteration
    for(int j = i+1 ; j < size ; j++) 
        if(arr[j] < arr[pos])
            pos=j;
    swap(arr[i],arr[pos]);

    //Now, recusrion
    selectionsort(arr , i + 1 , size);

}
int main()
{
    int arr[]={10,8,6,4,2};
    int n = sizeof(arr) / sizeof(arr[0]);
    selectionsort(arr , 0 , n);

    for(int i = 0 ; i < 5 ; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}