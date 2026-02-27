/*
Insertion_sort

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

#include<vector>
using namespace std;

void insertionSort(int n, vector<int> &arr){
    
    for(int i = 1; i<n; i++) {
        int temp = arr[i];
        int j = i-1;
        for(; j>=0; j--) {
            
            if(arr[j] > temp) {
                //shift
                arr[j+1] = arr[j];
            }
            else { // ruk jao
                break;
            }
            
        }
        //copy temp value
        arr[j+1] = temp;  
    } 
}