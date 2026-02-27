/*
Find_all_pairs_with_a_given_sum_GFG

Given two unsorted arrays A of size N and B of size M of distinct elements, the task is to find all pairs from both arrays whose sum is equal to X.

Note: All pairs should be printed in increasing order of u. For eg. for two pairs (u1,v1) and (u2,v2), if u12 then
(u1,v1) should be printed first else second.

    Example 1:
    Input: A[] = {1, 2, 4, 5, 7}, B[] = {5, 6, 3, 4, 8}, X = 9 
    Output: 
    1 8
    4 5 
    5 4
    Explanation: (1, 8), (4, 5), (5, 4) are the pairs which sum to 9.

Expected Time Complexity: O(NLog(N))
Expected Auxiliary Space: O(N)
*/

vector<pair<int,int>> allPairs(int A[], int B[], int N, int M, int X)
    {
        // Your code goes here   
        vector<pair<int, int>> ans;
        pair<int, int> temp;
        
        set<int> s;
        for(int i=0; i<N; i++)
            s.insert(A[i]);
        for(int i=0; i<M; i++)
        {
            if(s.find(X-B[i]) != s.end())
            {
                temp.first = X-B[i];
                temp.second = B[i];         // Writing temp.first = B[i] causing issue of sorting, don't know why !
                ans.push_back(temp);
            }
        }
        
        sort(ans.begin(), ans.end());
        return ans;
    }