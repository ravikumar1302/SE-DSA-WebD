/*
Minimum_Window_Substring_Leetcode_76

Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
The testcases will be generated such that the answer is unique. A substring is a contiguous sequence of characters within the string.

    Example 1:
    Input: s = "ADOBECODEBANC", t = "ABC"
    Output: "BANC"
    Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

    Example 2:
    Input: s = "a", t = "a"
    Output: "a"
    Explanation: The entire string s is the minimum window.

    Example 3:
    Input: s = "a", t = "aa"
    Output: ""
    Explanation: Both 'a's from t must be included in the window.
    Since the largest window of s only has one 'a', return empty string.
     
Constraints: s and t consist of uppercase and lowercase English letters.

Follow up: Could you find an algorithm that runs in O(m + n) time?
*/


class Solution {
public:
    string minWindow(string s, string t) {
     
        int i=0, j=0, MinL=INT_MAX, start=0;
        
        // Storing t in map
        unordered_map<char,int> mp;
        for(auto it:t)
            mp[it]++;
        int count = mp.size();
        
        if(mp.find(s[j]) != mp.end())
        {
            mp[s[j]]--;
            if(mp[s[j]] == 0)
                count--;
        }
        
        while(j < s.length())
        {
            if(count > 0)
            {
                j++;
                if(mp.find(s[j]) != mp.end())
                {
                    mp[s[j]]--;
                    if(mp[s[j]] == 0)
                        count--;
                }
            }
            else if(count == 0)
            {
                // MinL=min(MinL,j-i+1);
                if(MinL > j-i+1)
                {
                    MinL = j-i+1;
                    start = i;
                }
                while(count == 0)
                {
                    if(mp.find(s[i]) != mp.end())
                    {
                        mp[s[i]]++;
                        if(mp[s[i]] == 1) 
                        {
                            count++;
                            // MinL=min(MinL,j-i+1);
                             if(MinL > j-i+1)
                             {
                                MinL = j-i+1;
                                start = i;
                              } 
                        }
                        i++;
                    }
                    else
                        i++;
                  }
               }
            }
        string str="";
        if(MinL != INT_MAX)
            return str.append(s.substr(start,MinL));
        else
            return str;
    }
};