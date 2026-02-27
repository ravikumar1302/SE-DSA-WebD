/*
Buuble_sort

With every ith pass, (n-i)th largest element get placed at it's right (last-i)th position

               3     5     8     4     1     9    -2 
pass 1         3     5     4     1     8    -2     9
pass 2         3     4     1     5    -2     8     9
pass 3         3     1     4    -2     5     8     9
pass 4         1     3    -2     4     5     8     9
pass 5         1    -2     3     4     5     8     9
pass 6        -2     1     3     4     5     8     9

*/
#include<vector>
using namespace std;
void bubbleSort(vector<int>& arr, int n)
{   
    for(int i = 1; i<n; i++) {
        //for round 1 to n-1
        bool swapped = false;
        
        for(int j =0; j<n-i; j++) {
            
            //process element till n-i th index
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
            
        }
        
        if(swapped == false) {
            //already sorted
            break;
        }
           
    }
}