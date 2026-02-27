/*
Generate_all_Parentheses_II_InterviewBit

Asked In: Facebook Microsoft
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses of length 2*n.

    For example, given n = 3, a solution set is:

    "((()))", "(()())", "(())()", "()(())", "()()()"
    Make sure the returned list of strings are sorted.
*/


void solve(int open, int close, vector<string> &ans, string &output)   {
    //base case
    if(open == 0 && close == 0)  {
        ans.push_back(output);
        return;
    }
    if(open != 0)   {
       string op1 = output;
       op1.push_back('(');
       solve(open-1, close, ans, op1); 
    }
    
    if(close > open)   {
       string op2 = output ;
       op2.push_back(')');
       solve(open, close-1, ans, op2); 
    }
    
    return;
}

vector<string> Solution::generateParenthesis(int A) {
    vector<string> ans;
    string output = "";
    
    //no of open and close brackers is equal to A
    int open = A;
    int close = A;
    
    solve(open,close, ans, output );
    return ans;
}

