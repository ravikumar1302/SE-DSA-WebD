/*
Valid_Palindrome_II_Leetcode_680

Given a string s, return true if the s can be palindrome after deleting at most one character from it.

    Example 1:
    Input: s = "aba"
    Output: true
*/

class Solution {
public:
    bool checkagain(string s, int start, int end)
    {
        while( start <= end )   
        {
            if(s[start]!=s[end])
                return 0;

            else
            {
                start++;
                end--;
            }
        }
        return 1;
    }
    
    bool validPalindrome(string s) {
        
        int start = 0;
        int end = s.length()-1;
        int flag = 1;
        while( start < end )  
        {
            if(s[start]!=s[end])
                return checkagain(s, start+1, end) || checkagain(s, start, end-1) ;
                //Because the rest of the string is checked, so just check for remaining part
            
            else    //means start and end end element are equal
            {
                start++;
                end--;
            }
        }    
        return 1;
        }

};