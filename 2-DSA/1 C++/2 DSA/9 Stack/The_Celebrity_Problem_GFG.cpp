/*
The_Celebrity_Problem_GFG

A celebrity is a person who is known to all but does not know anyone at a party. If you go to a party of N people, find if there is a celebrity in the party or not.
A square NxN matrix M[][] is used to represent people at the party such that if an element of row i and column j  is set to 1 it means ith person knows jth person. Here M[i][i] will always be 0.
Note: Follow 0 based indexing.
 
    Example 1:

    Input : N = 3
    M[][] = {{0 1 0},
            {0 0 0}, 
            {0 1 0}}
    Output: 1
    Explanation: 0th and 2nd person both know 1. Therefore, 1 is the celebrity. 
*/

class Solution 
{
    private: 
    bool knows(vector<vector<int> >& M, int a, int b, int n)
    {
        if(M[a][b] == 1)
            return true;
        else
            return false;
    }
    
    public:
    //Function to find if there is a celebrity in the party or not.
    int celebrity(vector<vector<int> >& M, int n) 
    {
        // APPROACH -1
        // Celebrity row will be empty completely, as he don't know anyone
        // Celebrity column will be all one, except diagonal one
        // So, for every element check it's row and column
        // T.C. : O(N^2)
        
        
        // APPROACH -2 is below
        
        //Step-1 : push all elements (no of people) in stack
        stack<int> s;
        for(int i=0; i<n; i++)
            s.push(i);
        
        //Step-2 : Compare 2 people
        while(s.size() > 1)
        {
            int a = s.top();
            s.pop();
            
            int b = s.top();
            s.pop();
            
            if(knows(M,a,b,n)) //if a know b, then a is not celebrity
                s.push(b);
            else
                s.push(a);
        }
        int ans = s.top();
        //Now only one element is left, which can be a potential ans
        //Verify it
        
        int zeroCount = 0;
        for(int i = 0; i<n; i++)
            if(M[ans][i] == 0)
                zeroCount++;
        if(zeroCount != n)
            return -1;
        
        int oneCount = 0;
        for(int i = 0; i<n; i++)
            if(M[i][ans] == 1)
                oneCount++;
        if(oneCount != n-1)
            return -1;
        
        return ans;
    }
};

// T.C. : O(N)
