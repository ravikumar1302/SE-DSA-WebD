/*
Find_and_Replace_Pattern_Leetcode_890
Match specific pattern GFG

Given a list of strings words and a string pattern, return a list of words[i] that match pattern. You may return the answer in any order.

A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.

Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.

    Example 1:
    Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
    Output: ["mee","aqq"]
    Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}.  "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.

    Example 2:
    Input: words = ["a","b","c"], pattern = "a"
    Output: ["a","b","c"]

Expected Time Complexity: O(N*K) (where K is the length of the pattern).
Expected Auxiliary Space: O(N).
*/

// Youtube Link Solution : https://www.youtube.com/watch?v=V8W_Nmuruis

// Approach : Using hashmap
// If we use only one map, then the solution will return true in Example one for "ccc", so we need two map to store values both ways
// Time : O(N^2)
// Space : O(N)

class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        
        vector<string> ans;
        
        for(int i=0; i<words.size(); i++)
        {
            unordered_map<char, char> m1;
            unordered_map<char, char> m2;
            int flag = 1;
            
            // Each word
            for(int j=0; j<words[i].size(); j++)
            {
                // Word[i] = "mee", pattern = "abb"
                auto it = m1.find(pattern[j]);      // Find 'a'
                auto it2 = m2.find(words[i][j]);    // Find 'm'
                
                // For map m1
                if(it == m1.end())
                    m1[pattern[j]] = words[i][j];   // 'a' : 'm'
                else
                {
                    if(it->second != words[i][j])   // If you are trying to map 'a' : 'r' in next iteration
                    {
                        flag = 0;   // Problem
                        break;
                    }
                }
                
                // For map m2
                if(it2 == m2.end())
                    m2[words[i][j]] = pattern[j];   // 'm' : 'a'
                else
                {
                    if(it2->second != pattern[j]) 
                    {
                        flag = 0;   // Problem
                        break;
                    }
                }
            }
            
            if(flag == 1)
                ans.push_back(words[i]);
        }
        
        return ans;
    }
};


// IN GFG, words may have differnet length
// Becuase of which above code need some changes, without that the smaller string will give true, if word matches with pattern till it's length
// So we need to check the length also

// Checking size
    if(dict[i].size() != pattern.size())
    {
        flag = 0;
        break;
    }


// So, the code will be 
vector<string> findMatchedWords(vector<string> dict,string pattern)
{
   vector<string> ans;
    
    for(int i=0; i<dict.size(); i++)
    {
        unordered_map<char, char> m1;
        unordered_map<char, char> m2;
        int flag = 1;
        
        // Each word
        for(int j=0; j<dict[i].size(); j++)
        {
            // Checking size
            if(dict[i].size() != pattern.size())
            {
                flag = 0;
                break;
            }
            
            // Word[i] = "mee", pattern = "abb"
            auto it = m1.find(pattern[j]);      // Find 'a'
            auto it2 = m2.find(dict[i][j]);    // Find 'm'
            
            // For map m1
            if(it == m1.end())
                m1[pattern[j]] = dict[i][j];   // 'a' : 'm'
            else
            {
                if(it->second != dict[i][j])   // If you are trying to map 'a' : 'r' in next iteration
                {
                    flag = 0;   // Problem
                    break;
                }
            }
            
            // For map m2
            if(it2 == m2.end())
                m2[dict[i][j]] = pattern[j];   // 'm' : 'a'
            else
            {
                if(it2->second != pattern[j]) 
                {
                    flag = 0;   // Problem
                    break;
                }
            }
        }
        
        if(flag == 1)
            ans.push_back(dict[i]);
    }
    
    return ans;
}