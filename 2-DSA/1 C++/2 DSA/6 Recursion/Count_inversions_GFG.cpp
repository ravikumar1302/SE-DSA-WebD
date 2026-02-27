/*
Count_inversions_GFG

Given an array of integers. Find the Inversion Count in the array. 

Inversion Count: For an array, inversion count indicates how far (or close) the array is from being sorted. If array is already sorted then the inversion count is 0. If an array is sorted in the reverse order then the inversion count is the maximum. 
Formally, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j.
 
    Example 1:

    Input: N = 5, arr[] = {2, 4, 1, 3, 5}
    Output: 3
    Explanation: The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3)
*/

//Code not working for multiple test cases on GFG
long long int merge(long long int *arr, int s, long long int e)
{
    long long int mid = s + (e - s) / 2;
    long long int len1 = mid - s + 1; //left part length
    long long int len2 = e - mid;   //right part length

    long long int first[len1];
    long long int second[len2];
    //long long int *first = new long long int[len1];
    //long long int *second = new long long int[len2];

    long long int mainarrayindex = s;    //copying values from main array
    for(long long int i = 0; i<len1; i++)
        first[i] = arr[mainarrayindex++];
    
    mainarrayindex = mid+1;    //copying values from main array
    for(long long int i = 0; i<len2; i++)
        second[i] = arr[mainarrayindex++];
    
    //merge 2 sorted arrays
    long long int index1 = 0;
    long long int index2 = 0;
    mainarrayindex = s;
    long long int count=0;

    while(index1 < len1 && index2 < len2)
    {
        if(first[index1] < second[index2])
            arr[mainarrayindex++] = first[index1++];
        else
        {
            arr[mainarrayindex++] = second[index2++];
            count = count + len1-index1;
        }
    }
    while(index1 < len1)
        arr[mainarrayindex++] = first[index1++];
    while(index2 < len2)
        arr[mainarrayindex++] = second[index2++];

   // delete []first;
   // delete []second;
    return count;
}

long long int mergesort(long long int *arr, int s, long long int e)
{
    long long int count=0;
    if(s<e)
    {
        long long int mid = s + (e - s) / 2;
        count = count + mergesort(arr, s, mid);   //sorting left half
        count = count + mergesort(arr, mid+1, e);   //sorting right half
        count = count + merge(arr, s, e);
    }
    return count;
}
long long int inversionCount(long long arr[], long long N)
{
    long long int count= mergesort(arr, 0, N-1);
    return count;
}
