/*
Permutations_of_a_String_Codestudio

You are given a string 'STR' consisting of lowercase English letters. Your task is to return all permutations of the given string in lexicographically increasing order.
String A is lexicographically less than string B, if either A is a prefix of B (and A ≠ B), or there exists such i (1 <= i <= min(|A|, |B|)), that A[i] < B[i], and for any j (1 <= j < i) A[i] = B[i]. Here |A| denotes the length of the string A.
For example :
If the string is “bca”, then its permutations in lexicographically increasing order are { “abc”, “acb”, “bac”, “bca”, “cab”, “cba” }. (Like dictionary, first all words starting from a, then b etc..., similrly for the 2nd letter of word)
*/

#include<bits/stdc++.h>
void solve(string str, vector<string>& ans, int index)
    {
        if(index >= str.length())  //base case
        {
            ans.push_back(str);
            return ;
        }
        
        for(int j = index; j < str.length(); j++)
        {
            swap(str[index], str[j]);
            solve(str, ans, index+1);
            swap(str[j], str[index]); //backtraking
        }
    }
vector<string> generatePermutations(string &str)
{
        vector<string> ans;
        int index = 0;
        solve(str, ans, index);
        sort(ans.begin(), ans.end());
        return ans;
}