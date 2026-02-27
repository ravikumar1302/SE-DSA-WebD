/*
Max_Sum_Subarray_of_size_K_GFG

Given an array of integers Arr of size N and a number K. Return the maximum sum of a subarray of size K.

    Example 1:
    Input: N = 4, K = 2, Arr = [100, 200, 300, 400]
    Output: 700
    Explanation: Arr3  + Arr4 =700, which is maximum.
    
    Example 2:
    Input: N = 4, K = 4, Arr = [100, 200, 300, 400]
    Output: 1000
    Explanation: Arr1 + Arr2 + Arr3 + Arr4 =1000, which is maximum.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)
*/


// Brute force : Time O(N*N), using 2 for loops

// Optimized
// Time : O(N)
// Space : O(1)

class Solution{   
public:
    long maximumSumSubarray(int K, vector<int> &Arr , int N){
        
        long sum=0;
        // First window of size K
        for(int i=0; i<K; i++)
            sum += Arr[i];
        
        long temp_sum = sum;
        // Remaning windows of size K
        for(int i=K; i<N; i++)
        {
            temp_sum += Arr[i];
            temp_sum -= Arr[i-K];
            
            sum = max(sum, temp_sum);
        }
        return sum;
    }
};


// Aditya Verma Method

class Solution{   
public:
    long maximumSumSubarray(int K, vector<int> &Arr , int N){
        
        long sum=0;
        long maxi = INT_MIN;
        int i=0, j=0;
        
        while(j < N) 
        {
            sum+=Arr[j];
            if(j-i+1 < K) 
            {
              j++;
            } 
            else if(j-i+1 == K)
            {
                maxi=max(maxi,sum);
                sum=sum-Arr[i];
                j++;    
                i++;
            }
        }
        
        return maxi;;
    }
};