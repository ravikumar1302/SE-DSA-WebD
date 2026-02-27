/*
Repeated_DNA_Sequences_Leetcode_187

The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.

For example, "ACGAATTCCG" is a DNA sequence.
When studying DNA, it is useful to identify repeated sequences within the DNA.

Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.

    Example 1:
    Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
    Output: ["AAAAACCCCC","CCCCCAAAAA"]

    Example 2:
    Input: s = "AAAAAAAAAAAAA"
    Output: ["AAAAAAAAAA"]
*/


class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        
        unordered_map<string, int> counter;
        vector<string> res;
        
        // Base case : we have to return 10-letter-long strings
        if (s.size() < 10) 
            return res;
        
        // Starting from first letter to size-9, we are storing all 10 letter long string
        for (int i=0; i<s.size()-9; i++)
            counter[s.substr(i, 10)]++;
        
        // Finding if any string is more than once
        for (auto a:counter)
            if (a.second > 1)
                res.push_back(a.first);
        
        return res;
    }
};