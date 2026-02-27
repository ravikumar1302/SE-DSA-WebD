/*
Letter_Case_Permutation_Leetcode_784

Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.

Return a list of all possible strings we could create. Return the output in any order.

    Example 1:
    Input: s = "a1b2"
    Output: ["a1b2","a1B2","A1b2","A1B2"]
    
    Example 2:
    Input: s = "3z4"
    Output: ["3z4","3Z4"]
*/


class Solution {
public:
    void solve(string s, vector<string> &ans, string output)
    {
        //base case
        if(s.length() == 0) {
            ans.push_back(output);
            return;
        }
        
        if( isalpha(s[0]) ) {
            string op1 = output;
            string op2 = output;
            
            //add lower and upper case letters
            op1.push_back( tolower(s[0]) );
            op2.push_back( toupper(s[0]) );
            
            //now make the input small
            s.erase(s.begin() + 0);
            
            solve(s, ans, op1);
            solve(s, ans, op2);
        }
        else    {
            //not alphabat
            string op1 = output;
            op1.push_back(s[0]);
            
            s.erase(s.begin() + 0);
            solve(s, ans, op1);
        }

    }
    
    vector<string> letterCasePermutation(string s) {
        
        vector<string> ans;
        string output = "";
        
        solve(s, ans, output);
        
        return ans;
    }
}; 