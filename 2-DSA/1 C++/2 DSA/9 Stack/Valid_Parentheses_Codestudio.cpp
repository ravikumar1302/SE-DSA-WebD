/*
Valid_Parentheses_Codestudio
Minimum Remove to Make Valid Parentheses Leetcode_1249

You're given string ‘STR’ consisting solely of “{“, “}”, “(“, “)”, “[“ and “]” . Determine whether the parentheses are balanced.
*/

bool isValidParenthesis(string expression)
{
    stack <char> s;
    for(int i = 0; i < expression.length(); i++)
    {
        char ch = expression[i];

        // if oppening bracket, then push
        // if closing bracket, than check and pop

        if(ch == '(' || ch == '{' || ch == '[')
            s.push(ch);
        else
        {
            // for closing bracket
            if(!s.empty())
            {
                char top = s.top();
                
                if( ( ch == ')' && top == '(' ) || 
                    ( ch == '}' && top == '{' ) || 
                    ( ch == ']' && top == '[' ) )
                    s.pop();
                else
                    return false;
            }
             else    //means its empty
                 return false;
            }
        }
        if(s.empty())
            return true;
        else
            return false;
}

// T.C. : O(N)
// S.C. : O(N)


/***************************************************************************************/
// Leetcode Variation

/*
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 
    Example 1:
    Input: s = "lee(t(c)o)de)"
    Output: "lee(t(c)o)de"
    Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

    Example 2:
    Input: s = "a)b(c)d"
    Output: "ab(c)d"

    Example 3:
    Input: s = "))(("
    Output: ""
    Explanation: An empty string is also valid.
*/


// Approach : 1
// Time : O(N)
// Space : O(N), for Stack

string minRemoveToMakeValid(string s) {
        
        stack<int>st; // helper stack for finding matching parentheses
        
        for(int i=0;i<s.length();++i){
            if(s[i]=='(')        // for open parentheses push into stack
                st.push(i);
            
            else if(s[i]==')')
            {   // for closing parentheses
                // if no matching previous open parentheses found, we need to remove the index of that open parentheses from "s" so for now we are marking it with special character '#'
                if(st.empty())
                    s[i]='#';
                
                else        // if matching open parentheses found remove that from the stack
                    st.pop();
                
            }
        }

        // if stack is not empty, that means it contains open parentheses indexes which don't have any matching closing parentheses
        while(!st.empty())
        {
            s[st.top()]='#';
            st.pop();
        }
        
        string ans="";
        for(int i=0;i<s.length();++i)
        {
            if(s[i]!='#')       // append not marked character to the end of "ans"
                ans.push_back(s[i]);
        }
        
        return ans;
    }



// Aproach -2 : Optimized
// Time : O(N)
// Space : O(1)

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n=s.length();
        // Step 1 : Iterate from start
        int count=0; 
        for(int i=0;i<n;++i){
            if(s[i]=='('){ // for open bracket
                ++count;
            }
            else if(s[i]==')'){ // for close bracket
                if(count==0){  // if no. of close brackets > no. of open brackets
                    s[i]='#';
                }
                else{
                    // if matching parentheses found decrease count
                    --count;
                }
            }
        }
        
        // Step 2 : Iterate from end
        count=0;
        for(int i=n-1;i>=0;--i){
            if(s[i]==')'){ // for close bracket
                ++count;
            }
            else if(s[i]=='('){ // for open bracket
                if(count==0){ // if no. of open brackets > no. of close brackets
                    s[i]='#';
                }
                else{
                    // if matching parentheses found decrease count
                    --count;
                }
            }
        }
        
        // Step 3 : Create "ans" by ignoring the special characters '#'
        string ans="";
        for(int i=0;i<n;++i){
            if(s[i]!='#'){ 
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};