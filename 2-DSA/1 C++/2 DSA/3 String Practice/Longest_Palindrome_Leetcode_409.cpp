/*
Longest_Palindrome_Leetcode_409

Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome here.

Example 1:
Input: s = "abccccdd"
Output: 7
Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.

Example 2:
Input: s = "a"
Output: 1
Explanation: The longest palindrome that can be built is "a", whose length is 1.
 
Constraints: s consists of lowercase and/or uppercase English letters only.
*/


/* Approach: 
Count the frequency of each char, the chars appears even times can all be kept, 
however, the chars appears odd times must remove one char, then the rest instances of that char can be collected for composition. 
Finally, the middle char can be from OddGroup

Example: "abccccdd",
step 1: count freq of char before clearning:
a:1, b:1, c:4, d:2

step 2: perform clearning and prepare for palindrom composition:
a:0, b:0, c:4, d:2

answer = s.size() - 1 - 1
Step 3: make correction, if necessary (i.e., when at least one char shows odd times)
if OddGroup > 0: answer +=1
*/

class Solution {
public:
    int longestPalindrome(string s) {
        
        int freq[128]={0};
        
        for(auto c:s) 
            ++freq[c];
        
        int OddGroup = 0;   //count of uniq char which shows up odd times
        
        for(auto i:freq) 
            OddGroup += i & 1;
        
        return s.size() - OddGroup + (OddGroup > 0);   
    }
};