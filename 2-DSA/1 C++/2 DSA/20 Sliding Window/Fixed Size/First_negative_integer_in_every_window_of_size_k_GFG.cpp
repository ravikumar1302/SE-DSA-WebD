/*
First_negative_integer_in_every_window_of_size_k_GFG

Given an array A[] of size N and a positive integer K, find the first negative integer for each and every window(contiguous subarray) of size K.
Note : If a window does not contain a negative integer , then return 0 for that window.

    Example 1:
    Input : N = 5, A[] = {-8, 2, 3, -6, 10}, K = 2
    Output : -8 0 -6 -6
    Explanation : First negative integer for each window of size k 
                    {-8, 2} = -8
                    {2, 3} = 0 (does not contain a negative integer)
                    {3, -6} = -6
                    {-6, 10} = -6
    
    Example 2:
    Input : N = 8, A[] = {12, -1, -7, 8, -15, 30, 16, 28}, K = 3
    Output : -1 -1 -7 -15 -15 0 

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(K)
*/


// Approach : We have to store the negative numbers as we move forward in the array

vector<long long> printFirstNegativeInteger(long long int A[], long long int N, long long int K) {
        
        vector<long long> ans;
        queue<long long> q;
        long long i=0, j=0;
        
        while(j < N)
        {
           if(A[j] < 0)
                q.push(A[j]);
           
           if(j-i+1 < K)
           {
               j++;
           }
           else if (j-i+1 == K)
           {
                if(q.empty() == true)    // if queue is empty, means no negative no in given sub-array
                    ans.push_back(0);
                else
                    ans.push_back(q.front());
                
                if(A[i] < 0 && !q.empty())      // or if(A[i] == q.front())
                    q.pop();
                i++;
                j++;
                
           }
        }
        
        return ans;
 }