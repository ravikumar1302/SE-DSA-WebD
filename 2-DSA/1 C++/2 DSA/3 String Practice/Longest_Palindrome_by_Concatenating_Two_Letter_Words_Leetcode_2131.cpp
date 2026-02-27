/*
Longest_Palindrome_by_Concatenating_Two_Letter_Words_Leetcode_2131


You are given an array of strings words. Each element of words consists of two lowercase English letters.
Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.
Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.

    Example 1:
    Input: words = ["lc","cl","gg"]
    Output: 6
    Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6. Note that "clgglc" is another longest palindrome that can be created.

    Example 2:
    Input: words = ["ab","ty","yt","lc","cl","ab"]
    Output: 8
    Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8. Note that "lcyttycl" is another longest palindrome that can be created.

    Example 3:
    Input: words = ["cc","ll","xx"]
    Output: 2
    Explanation: One longest palindrome is "cc", of length 2. Note that "ll" is another longest palindrome that can be created, and so is "xx".
*/


/*
Approach :
2 letter words can be of 2 types:
    Where both letters are same
    Where both letters are different

Based on the above information:
    If we are able to find the mirror of a word, ans += 4
    The variable unpaired is used to store the number of unpaired words with both letters same.
    Unpaired here means a word that has not found its mirror word.
    At the end if unpaired same letter words are > 0, we can use one of them as the center of the palindromic string.
*/
// Time : O(N)
// Spac : O(N)

class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        
        unordered_map<string, int> m;
        int unpaired = 0, ans = 0;
        
        for (string w: words) 
        {
            if (w[0] == w[1])   // if both letter are same
            {
                if (m[w] > 0)   // one string is avilable, like "aa"
                {
                    unpaired--;
                    m[w]--;
                    ans += 4;
                }
                else    // Not avialble
                {
                    m[w]++;
                    unpaired++;
                }
            }
            else    // if both letter are different
            {
                string rev = w;
                reverse(rev.begin(), rev.end());
                if (m[rev] > 0) 
                {
                    ans += 4;
                    m[rev]--;
                }
                else m[w]++;
            }
        }
        if (unpaired > 0)   // One of the "aa" kind string can be used as center
            ans += 2;
        
        return ans;
    }
};