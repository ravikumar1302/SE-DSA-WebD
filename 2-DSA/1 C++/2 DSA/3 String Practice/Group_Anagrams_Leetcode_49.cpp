/*
Group_Anagrams_Leetcode_49

Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
 
    Example 1:
    Input: strs = ["eat","tea","tan","ate","nat","bat"]
    Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

    Example 2:
    Input: strs = [""]
    Output: [[""]]

    Example 3:
    Input: strs = ["a"]
    Output: [["a"]]
*/


class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        
        vector<vector<string>> res;
        unordered_map<string, vector<string>> m;
        
        for (string s : strs) 
        {
            string t = s;
            sort(t.begin(), t.end());
            m[t].push_back(s);
        }
        
        for (auto e : m) 
            res.push_back(e.second);
        
        return res;
    }
};