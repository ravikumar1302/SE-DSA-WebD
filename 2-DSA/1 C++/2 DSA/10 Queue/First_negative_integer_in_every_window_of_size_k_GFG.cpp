/*
First_negative_integer_in_every_window_of_size_k_GFG

Given an array A[] of size N and a positive integer K, find the first negative integer for each and every window(contiguous subarray) of size K.

    Example 1:

    Input : 
    N = 5
    A[] = {-8, 2, 3, -6, 10}
    K = 2
    Output : 
    -8 0 -6 -6
    Explanation :
    First negative integer for each window of size k
    {-8, 2} = -8
    {2, 3} = 0 (does not contain a negative integer)
    {3, -6} = -6
    {-6, 10} = -6

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(K)
*/

vector<long long> printFirstNegativeInteger(long long int A[],
                                             long long int N, long long int K) {
    deque<long long int> dq;
    vector<long long> ans;
    
    //Process first window of K size
    for(int i=0; i<K; i++)
        if(A[i]<0)
            dq.push_back(i);
    
    //Store ans of first K sized window
    if(dq.size()>0)
        ans.push_back(A[dq.front()]);
    else
        ans.push_back(0);
    
    //Process for remaining windows
    for(int i=K; i<N; i++)
    {
        //Removal
        if(!dq.empty() && i - dq.front() >=K )
            dq.pop_front();
        
        //Addition
        if(A[i] < 0)
            dq.push_back(i);
        
        //ans store
        if(dq.size()>0)
            ans.push_back(A[dq.front()]);
        else
            ans.push_back(0);
    }
    return ans;
 }