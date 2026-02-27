/*
Frequencies_of_Limited_Range_Array_Elements_GFG

Given an array A[] of N positive integers which can contain integers from 1 to P where elements can be repeated or can be absent from the array. Your task is to count the frequency of all elements from 1 to N.
Note: The elements greater than N in the array can be ignored for counting and please read your task section of the problem carefully to understand how to output the array.

    Example 1:
    Input: N = 5, arr[] = {2, 3, 2, 3, 5}, P = 5
    Output: 0 2 2 0 1
    Explanation: Counting frequencies of each array element
    We have : 1 occurring 0 times, 2 occurring 2 times, 3 occurring 2 times, 4 occurring 0 times, 5 occurring 1 time.

    Example 2:
    Input: N = 4, arr[] = {3,3,3,3}, P = 3
    Output: 0 0 4 0
    Explanation: Counting frequencies of each array element
    We have : 1 occurring 0 times, 2 occurring 0 times, S3 occurring 4 times, 4 occurring 0 times.

Your Task: modify the array itself in place to denote the frequency count of each element from 1 to N. i,e element at index 0 should represent the frequency of 1 and so on.

Note: Can you solve this problem without using extra space (O(1) Space) !
*/


class Solution{
    public:
    //Function to count the frequency of all elements from 1 to N in the array.
    void frequencyCount(vector<int>& arr,int N, int P)
    { 
        
        vector<int> freq(N+1, 0);
        for(int i=0; i<N; i++)
            if(arr[i] <= P && arr[i] <= N)
                freq[arr[i]]++;
        
        for(int i=1; i<=N; i++)
            arr[i-1] = freq[i];
    }
};
