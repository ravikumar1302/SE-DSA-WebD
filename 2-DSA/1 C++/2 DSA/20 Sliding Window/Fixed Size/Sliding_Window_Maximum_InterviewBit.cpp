/*
Sliding_Window_Maximum_InterviewBit
Sliding Window Maximum Leetcode_239

Given an array of integers A.  There is a sliding window of size B which is moving from the very left of the array to the very right. 
You can only see the w numbers in the window. Each time the sliding window moves rightwards by one position. You have to find the maximum for each window. 

    The following example will give you more clarity.
    The array A is [1 3 -1 -3 5 3 6 7], and B is 3.

    Window position	            Max
    ———————————-	            ————————-
    [1  3  -1] -3  5  3  6  7	3
    1 [3  -1  -3] 5  3  6  7	3
    1  3 [-1  -3  5] 3  6  7	5
    1  3  -1 [-3  5  3] 6  7	5
    1  3  -1  -3 [5  3  6] 7	6
    1  3  -1  -3  5 [3  6  7]	7

    Return an array C, where C[i] is the maximum value of from A[i] to A[i+B-1]. 
    Note: If B > length of the array, return 1 element with the max of the array.
    
    Ex: 2
    Input 1:
        A = [1, 3, -1, -3, 5, 3, 6, 7]
        B = 3
    Output 1:
        C = [3, 3, 5, 5, 6, 7]
*/


vector<int> Solution::slidingMaximum(const vector<int> &A, int B) {
    
    vector<int> ans;
    int n = A.size();
    deque<int> l;       // list<int> l; can also be used
    
    
    //  edge condition:  If B > length of the array, return 1 element with the max of the array
    if(B > A.size())
    {
        ans.push_back(*max_element(A.begin(),A.end()));
        return ans;
    }

    int i=0, j=0;
    while(j < n)
    {
        while(!l.empty() && l.back() < A[j])
            l.pop_back();
            
        l.push_back(A[j]);
        
        if(j-i+1 < B)
            j++;
        else if(j-i+1 == B)
        {
            ans.push_back(l.front());
            if(A[i] == l.front() )
                l.pop_front();
            
            i++;
            j++;
        }
        
    }
    
    return ans;
}
