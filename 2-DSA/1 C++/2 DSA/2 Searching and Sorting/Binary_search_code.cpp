// T.C.: O(log n)
// S.C.: O(log n)

// Note: Binary search only works on Sorted data (Ascending or Descending)
/*
STL way of Binary Search:
    1. Ascending: binary_search(v.begin(), v.end(), key)
    2. Descending:binary_search(v.begin(), v.end(), key, greater<int>())
*/

#include <iostream>
using namespace std;

int binarySearch(int arr[], int size, int key)
{

    int start = 0;
    int end = size - 1;

    int mid = start + (end - start) / 2;

    while (start <= end)
    {

        if (arr[mid] == key)
        {
            return mid;
        }

        // go to right wala part
        if (key > arr[mid])
        {
            start = mid + 1;
        }
        else
        { // key < arr[mid]
            end = mid - 1;
        }

        mid = start + (end - start) / 2;
    }

    return -1;
}

int main()
{

    int even[6] = {2, 4, 6, 8, 12, 18};

    int Index = binarySearch(even, 6, 6);

    cout << " Index of 6 is " << Index << endl;

    return 0;
}

// Peak element : It is an element that is greater than or equal to its immediate neighbors. It may not be the largest element in array
int findPeak(int arr[], int n)
{

    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;

    while (s < e)
    {
        // cout<<" s " << s <<" e " << e << endl;
        if (arr[mid] < arr[mid + 1])
        {
            s = mid + 1;
        }
        else
        {
            e = mid;
        }
        mid = s + (e - s) / 2;
    }
    return s;
}