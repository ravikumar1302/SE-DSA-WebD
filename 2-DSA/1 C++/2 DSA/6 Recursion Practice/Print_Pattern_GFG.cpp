/*

Print a sequence of numbers starting with N where A[0] = N, without using loop, in which  A[i+1] = A[i] - 5,  until A[i] > 0. After that A[i+1] = A[i] + 5  repeat it until A[i] = N.

    Example 1:

    Input: N = 16
    Output: 16 11 6 1 -4 1 6 11 16
    Explaination: The value decreases until it 
    is greater than 0. After that it increases 
    and stops when it becomes 16 again.
    Example 2:

    Input: N = 10
    Output: 10 5 0 5 10
    Explaination: It follows the same logic as 
    per the above example.
    Your Task:
    You do not need to read input or print anything. Your task is to complete the function pattern() which takes N as input parameters and returns a list containing the pattern.

    Expected Time Complexity: O(N)
    Expected Auxiliary Space: O(N)

Constraints:
1 ≤ N ≤ 104 

*/


class Solution{
public:
    vector<int> ans;    // user declared, if declared inside, will print only 1 no. Other way was to declare another function and pass the array

    vector<int> pattern(int N){
        
        ans.push_back(N);
        
        if(N > 0)
            pattern(N-5);
        
        ans.push_back(N+5);
        if(ans.back() > ans[0])
            ans.pop_back();
        
        return ans;
    }
};

// Approach-2 

class Solution{
public:

    void helper(int N, vector<int> &ans)
    {
        ans.push_back(N);
        
        if(N > 0)
            helper(N-5, ans);
        
        ans.push_back(N+5);
        if(ans.back() > ans[0])
            ans.pop_back();
    }
    
    vector<int> pattern(int N){
        vector<int> ans;    // user declared
        
        helper(N, ans);
        return ans;
    }
};