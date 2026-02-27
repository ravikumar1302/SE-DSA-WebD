/*
Count_and_say_Leetcode_38

The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

countAndSay(1) = "1"
countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is then converted into a different digit string.
To determine how you "say" a digit string, split it into the minimal number of substrings such that each substring contains exactly one unique digit. Then for each substring, say the number of digits, then say the digit. Finally, concatenate every said digit.

For example, the saying and conversion for digit string "3322251":

Given a positive integer n, return the nth term of the count-and-say sequence.

    Example 1:
    Input: n = 1
    Output: "1"
    Explanation: This is the base case.
*/

class Solution {
public:
    string countAndSay(int n) {
        string ans = "1";
         while(--n)
         {
             string s = "";
             for(int i =0; i < ans.size(); i++)
             {
                 char ch = ans[i];
                 int count = 1;
                 while(ans[i]==ans[i+1])
                 {
                    count++;
                     i++;
                 }
                 s = s + to_string(count);
                 s = s + ans[i];
             }
             ans = s;
         }
        return ans;
    }
};