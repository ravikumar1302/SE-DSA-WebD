/*
Longest_Sub_Array_with_Sum_K_GFG

Given an array containing N integers and an integer K., Your task is to find the length of the longest Sub-Array with the sum of the elements equal to the given value K.

    Example 1:
    Input : A[] = {10, 5, 2, 7, 1, 9}, K = 15
    Output : 4
    Explanation: The sub-array is {5, 2, 7, 1}.

    Example 2:
    Input : A[] = {-1, 2, 3}, K = 6
    Output : 0
    Explanation: There is no such sub-array with sum 6.

Expected Time Complexity: O(N).
Expected Auxiliary Space: O(N).
*/


// Note : This method does not work if negative elements are there in the array.
// To deal with negative elements use : Kadane algorithm can deal with both positive and negative elements

// Will fail after 1 test case, as negative numbers are not dealt with
class Solution{
    public:
    int lenOfLongSubarr(int A[],  int N, int K) 
    { 
        int ans = 0;
        int i=0, j=0;
        int sum = 0;
        int maxi = 0;
        
        while(j < N)
        {
            sum = sum + A[j];
            
            if(sum > K)
            {
                while(sum > K)
                {
                    sum = sum - A[i];
                    i++;
                }
            }
            
            if(sum < K)
                j++;
                
            else if(sum == K)
            {
                maxi = max(maxi, j-i+1);
                j++;
            }
        }
        
        return ans;
    } 
};


// Using map : Will pass all test cases
class Solution{
    public:
    int lenOfLongSubarr(int A[],  int N, int K) 
    { 
        unordered_map<int,int> mp;
        int maxi=0, sum=0;
        
        for(int i=0; i<N; i++)
        {
            sum += A[i];
            
            // Counts the sum from starting
            if(sum == K) 
            { 
                if(i+1 > maxi) 
                    maxi = i+1;
            }
            
            // For a subarray inside the given array
            if(mp.find(sum-K) != mp.end())      
            {
                int len = i - mp[sum-K];
                maxi = max(maxi, len);
            }
            
            if(mp.find(sum) == mp.end())
                mp[sum] = i;
        }
        return maxi;
    } 
};