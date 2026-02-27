/*
Longest_K_unique_characters_substring_GFG

Given a string you need to print the size of the longest possible substring that has exactly K unique characters. If there is no possible substring then print -1.

    Example 1:
    Input: S = "aabacbebebe", K = 3
    Output: 7
    Explanation: "cbebebe" is the longest substring with K distinct characters.

    Example 2:
    Input: S = "aaaa", K = 2
    Output: -1
    Explanation: There's no substring with K distinct characters.

Expected Time Complexity: O(|S|).
Expected Auxiliary Space: O(|S|).
*/


class Solution{
  public:
    int longestKSubstr(string s, int k) {
    
        unordered_map<char, int> mp;
        int maxi = INT_MIN;
        int i=0, j=0;
        
        while(j < s.length())
        {
            mp[s[j]]++;
            
            if(mp.size() == k)      // map.size() == 3, means 3 unique characters till now
                maxi = max(maxi, j-i+1);
            
            else if(mp.size() > k)
            {
                while(mp.size() > k)
                {
                    mp[s[i]]--;       // removing first character count
                    if(mp[s[i]] == 0)
                        mp.erase(s[i]);
                    
                    ++i;
                    
                    if(mp.size() == k)     
                        maxi = max(maxi, j-i+1);
                }
            }
            
            j++;
        }
        
        if(maxi == INT_MIN)
            return -1;
            
        return maxi;
    }
};