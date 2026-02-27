/*
Basic_Calculator_II_Leetcode_227


Given a string s which represents an expression, evaluate this expression and return its value. 
The integer division should truncate toward zero.
You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

    Example 1:
    Input: s = "3+2*2"
    Output: 7

    Example 2:
    Input: s = " 3/2 "
    Output: 1

    Example 3:
    Input: s = " 3+5 / 2 "
    Output: 5
 
Constraints:
    1 <= s.length <= 3 * 105
    s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
    s represents a valid expression.
    All the integers in the expression are non-negative integers in the range [0, 231 - 1].
    The answer is guaranteed to fit in a 32-bit integer.
*/


/*
APPROACH :

To begin with, we add '+' to the s=input string (Reason will be understood later).
We initilaize a few variables int ans=0(to store the final ans), char sign='+'(to store the previous operator), long long int curr=0 (to store the value computed until we encounter some operator) (The final ans is guaranteed to be an integer, but the values in between might exceed integer values).
While traversing the string :
    1. If we encounter an empty space, we just continue.
    2. Else if we encounter a digit/num (The string might also contain more than 1 digit numbers, so until we find any operator, we'll keep on forming the multi digit number (num = num*10 + s[i] ) ).
    3. When we encounter a sign, we stop & check the previous operator :
    ** If sign = '+' (i.e; the previous operator was +), we just push curr into the stack ('Cause this value needs to be added to ans).
    ** If sign = '-', (i.e; the previous operator was -), we toggle curr's sign and push it into the stack ('Cause this value needs to be subtracted from ans).
    ** If sign = '*', (i.e; we encountered a x sign previously), then the curr value should be multiplied with it and then added to ans, so we pop the top of the stack, multiply it with the current value and push the result into the stack.

    ** If sign = '/', i.e; we encountered a / previously, then the curr value should divide the previous value ans, so we pop the top of the stack, divide it with curr and push the result into the stack.
    4. At the end, we encounter another '+' sign, this is to push the last curr value into the stack.
    5. Finally we have obtained a stack of values all of which only need to be added to obtain the ans.
    6. So pop the values from stack one by one, add them to ans, and return the ans

*/


class Solution {
public:
    int calculate(string s) {
        
        stack<int> st;
        char prevSign = '+';
        int no = 0;
        
        for(int i=0; i<s.size(); i++)
        {
            char c = s[i];
            if(isdigit(c))          //keep forming the number, until you encounter an operator
                no = no*10 + (c - '0');   // 33 + .., so 3*10 + 3 = 33
            
            if( (c == '+' || c == '-' || c == '*' || c == '/') || i == s.length() - 1 )
            {
                if(prevSign == '+')
                    st.push(no);
                else if(prevSign == '-')
                    st.push(-no);
                else if(prevSign == '*')
                {
                    int top = st.top();
                    st.pop();
                    st.push(top*no);
                }
                else if(prevSign == '/')
                {
                    int top = st.top();
                    st.pop();
                    st.push(top/no);
                }
                no = 0;
                prevSign = c;
            }
                
        }
        int res = 0;
        while(!st.empty())
        {
            res = res + st.top();       
            st.pop();            // these two line can also be written as : res + = st.pop(), because, st.pop(), will return pop value to the expression
        }
        return res;
        
    }
};