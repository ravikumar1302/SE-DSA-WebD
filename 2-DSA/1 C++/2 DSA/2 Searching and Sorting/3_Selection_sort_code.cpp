/*
With ith pass, the remaing array smallest element get placed at its right (left+i)th position

            3  5  8  4  1  9 -2
i = 0      -2  5  8  4  1  9  3
i = 1      -2  1  8  4  5  9  3
i = 2      -2  1  3  4  5  9  8
i = 3      -2  1  3  4  5  9  8
i = 4      -2  1  3  4  5  9  8
i = 5      -2  1  3  4  5  8  9

*/

#include<vector>
using namespace std;
void selectionSort(vector<int>& arr, int n)
{   
    for(int i = 0; i < n-1; i++ ) {
        
        int minIndex = i;   //minimum index i for each iteration
        
        for(int j = i+1; j<n; j++) {
            
            if(arr[j] < arr[minIndex]) 
                minIndex = j;
            
        }
        swap(arr[minIndex], arr[i]);
    }
}