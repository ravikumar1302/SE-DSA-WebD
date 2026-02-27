/*
Maximum_Frequency_Number_Codestudio

Ninja is given an array of integers that contain numbers in random order. He needs to write a program to find and return the number which occurs the maximum times in the given input. He needs your help to solve this problem.
If two or more elements contend for the maximum frequency, return the element which occurs in the array first i.e. whose index is lowest.
    
    For example,
    For 'arr' = [ 1, 2, 3, 1, 2]. you need to return 1.

*/

int maximumFrequency(vector<int> &arr, int n)
{
    unordered_map<int,int> m;    // First int is for element, second for frequency
    int maxFreq = 0;
    int maxAns = 0;
    
    for(auto i:arr)
    {
        m[i]++;
        maxFreq = max(maxFreq, m[i]);
    }
    
    // Traversing in vector again to check for each element, finding the first element with max frequency
    for(auto i:arr)
        if(maxFreq == m[i])
        {
            maxAns = i;
            break;
        }
    
    /* same code in int i format, if don't understand in auto i fomat
    for(int i=0; i<n; i++)
        if(maxFreq == m[arr[i]])
        {
            maxAns = arr[i];
            break;
        }
    */
return maxAns;
}
// T.C. : O(N) because of the 'for' loop. insertion and deletion in unordered map takes O(1) time