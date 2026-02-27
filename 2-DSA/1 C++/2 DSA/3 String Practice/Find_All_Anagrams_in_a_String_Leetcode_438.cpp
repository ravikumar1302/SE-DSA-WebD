/*
Find_All_Anagrams_in_a_String_Leetcode_438

Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

    Example 1:

    Input: s = "cbaebabacd", p = "abc"
    Output: [0,6]
    Explanation:
    The substring with start index = 0 is "cba", which is an anagram of "abc".
    The substring with start index = 6 is "bac", which is an anagram of "abc".
*/

// Approach : Using two arrays, one for frequency of p (smaller string) and other for frequency of s in a window. Then firstly compared the first window and then reamning window
// Time and space : O(N)

class Solution {
public:

    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        int s_len = s.length();
        int p_len = p.length();
        
        if(s.size() < p.size()) return {};
        
        vector<int> freq_p(26,0);
        vector<int> window(26,0);
        
        //first window
        for(int i = 0; i < p_len; i++)
        {
            freq_p[ p[i] - 'a' ]++;
            window[ s[i] - 'a' ]++;
        }
        
        if(freq_p == window)
            ans.push_back(0);
        
        //Remaining windows
        for( int i = p_len; i < s_len; i++)
        {
            window[ s[i-p_len] - 'a' ]--;
            window[ s[i] - 'a' ]++;
            
            if(freq_p == window)
                ans.push_back( i - p_len +1 );
        }
        
        return ans;
    }
};