/*
K-th_Largest_Sum_Subarray_Codestudio

You have been given an array/list of ‘N’ integers. Now you are supposed to find the K-th largest sum of the subarray.
Please note that a subarray is the sequence of consecutive elements of the array

    Sample Input 1 :
    2
    3 3
    3 -2 5
    2 2
    4 1
    Sample output 1 :
    3
    4
    Explanation of Sample output 1 :
    For the first test case, 
    Sum of [0, 0] = 3
    Sum of [0, 1] = 1
    Sum of [0, 2] = 6
    Sum of [1, 1] = -2
    Sum of [1, 2] = 3
    Sum of [2, 2] = 5
    All sum of subarrays are {6, 5, 3, 3, 1, -2} where the third largest element is 3.

    For the second test case, 
    Sum of [0, 0] = 4
    Sum of [0, 1] = 5
    Sum of [1, 1] = 1
    All sum of subarrays are {5, 4, 1} where the second largest element is 4.
*/

#include<queue>
int getKthLargest(vector<int> &arr, int k)
{
    // Approach: find all sums and then remove (k-1) elements from max heap
    // Or you can use vector to store all sum, sort it and return (size -k)th element
    
	priority_queue<int> sum;

    int size = arr.size();
    
    for(int i=0; i<size; i++)
    {
        int temp = 0;    // for i,i, the sum is taken as one value only
        for(int j=i; j<size; j++)
        {
            temp = temp + arr[j];
            sum.push( temp );
        } 
    }  
    
    for(int i=1; i<k; i++)
        sum.pop();
    
    return sum.top();
}
// Here O(N^2) space is being used

/***********************************************************************************************************/

// Approach 2 : O(K time)
// Here O(K) space is being used

#include<queue>
int getKthLargest(vector<int> &arr, int k)
{
    
    priority_queue<int, vector<int>, greater<int> > minheap;

    int size = arr.size();
    
    for(int i=0; i<size; i++)
    {
        int temp = 0;    // for i,i, the sum is taken as one value only
        for(int j=i; j<size; j++)
        {
            temp = temp + arr[j];
            
            if(minheap.size() < k)
                minheap.push( temp );
            
            else
            {
                if(temp > minheap.top() )
                {
                    minheap.pop();
                    minheap.push( temp ); 
                }
            } 
        } 
    }  
return minheap.top();
}