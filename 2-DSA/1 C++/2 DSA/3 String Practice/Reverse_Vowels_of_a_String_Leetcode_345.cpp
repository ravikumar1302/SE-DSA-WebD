/*
Reverse_Vowels_of_a_String_Leetcode_345

Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both cases.

    Example 1:
    Input: s = "hello"
    Output: "holle"
*/

class Solution {
public:
    bool isvowel(char ch)
    {
        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            return true;
        else 
            return false;
    }
    string reverseVowels(string s) {
        
        int low = 0;
        int high = s.length()-1;
        
        while(low < high)
        {
            if( isvowel( tolower(s[low] )) )
            {
                while(low < high && !isvowel(tolower(s[high])) )
                    high--;
                swap(s[low], s[high]);
                high--;
            }
            low++;
                
        }
        return s;
    }
};