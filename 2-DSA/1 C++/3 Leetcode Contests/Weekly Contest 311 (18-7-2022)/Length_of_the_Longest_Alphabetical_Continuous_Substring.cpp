/*
Length_of_the_Longest_Alphabetical_Continuous_Substring

An alphabetical continuous string is a string consisting of consecutive letters in the alphabet. In other words, it is any substring of the string "abcdefghijklmnopqrstuvwxyz".

For example, "abc" is an alphabetical continuous string, while "acb" and "za" are not.
Given a string s consisting of lowercase letters only, return the length of the longest alphabetical continuous substring.

Example 1:
Input: s = "abacaba"
Output: 2
Explanation: There are 4 distinct continuous substrings: "a", "b", "c" and "ab".
"ab" is the longest continuous substring.

Example 2:
Input: s = "abcde"
Output: 5
Explanation: "abcde" is the longest continuous substring.

*/

class Solution {
public:
    int longestContinuousSubstring(string s) {
        
        int max_till_now = 1;
        int len = 1;
        for(int i=1; i<s.length(); i++)
        {
            int diff = (s[i] - 'a') - (s[i-1] - 'a');
            if(diff == 1)
                len++;
            else if(diff != 1)
                len = 1;
            
            // updating ans
            max_till_now = max(max_till_now, len);
        }
        
        return max_till_now;
    }
};