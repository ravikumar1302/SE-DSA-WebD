/*
Permutation_with_Spaces_GFG

Given a string you need to print all possible strings that can be made by placing spaces (zero or one) in between them. The output should be printed in sorted increasing order of strings

    Example 1:
    Input: S = "ABC"
    Output: (A B C)(A BC)(AB C)(ABC)
    Explanation:
    ABC
    AB C
    A BC
    A B C, These are the possible combination of "ABC".

    Example 2:
    Input: S = "AB"
    Output: (A B)(AB)

Expected Time Complexity: O(2^n)
Expected Auxiliary Space: O(1)

CONSTRAINTS: 1 <= |S| < 10, S only contains lowercase and Uppercase English letters.
*/


class Solution{
public:
    void solve(string S, vector<string> &ans, string output)
    {
        // Base Case
        if(S.size() == 0)
        {
            ans.push_back(output);
            return;
        }
        
        // Processing
        string op1 = output;
        string op2 = output;
        
        op1.push_back(' ');
        op1.push_back(S[0]);
        op2.push_back(S[0]);
        S.erase(S.begin() + 0);
        
        // Recursion
        solve(S, ans, op1);
        solve(S, ans, op2);
        return;
    }
    
    vector<string> permutation(string S){
        vector<string> ans;
        string output = "";
        
        output.push_back(S[0]);
        S.erase(S.begin() + 0);
        
        solve(S, ans, output);
        return ans;
    }

};