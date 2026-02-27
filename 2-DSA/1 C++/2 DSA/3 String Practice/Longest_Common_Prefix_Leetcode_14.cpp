/*
Longest_Common_Prefix_Leetcode_14

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

    Example 1:
    Input: strs = ["flower","flow","flight"]
    Output: "fl"

*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        
        string op = "";
        
        int n = strs.size();
        int first = strs[0].size();
        
        // Edge case
        if(first == 0)
            return op;
        
        for(int i=0; i<first; i++)
        {
            char ch = strs[0][i];
            bool flag = true;
            for(int j=1; j<n; j++)
            {
                if(ch != strs[j][i])
                {
                    flag = false;
                    break;
                }       
            }
            
            if(flag == false)
                break;
            else
                op.push_back(ch);
        }
        
        return op;
    }
};

// Approach : comparing first string with other string
// Time : O(N^2)
// Space : O(1) 