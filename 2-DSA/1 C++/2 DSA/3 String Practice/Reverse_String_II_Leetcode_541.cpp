/*
Reverse_String_II_Leetcode_541

Given a string s and an integer k, reverse the first k characters for every 2k characters counting from the start of the string.

If there are fewer than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and leave the other as original.

    Example 1:
    Input: s = "abcdefg", k = 2
    Output: "bacdfeg"
*/

class Solution {
public:
    string reverseStr(string s, int k) {
        
        int len = s.length();
        for(int i = 0; i< len; i= i + 2*k)
        {
            reverse( s.begin() + i, s.begin() + min(i+k, len) );
        }
        return s;
    }
};