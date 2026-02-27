/*
Reverse_String_Leetcode

Write a function that reverses a string. The input string is given as an array of characters s.
You must do this by modifying the input array in-place with O(1) extra memory.

    Example 1:
    Input: s = ["h","e","l","l","o"]
    Output: ["o","l","l","e","h"]
*/

class Solution {
public:
    void reverseString(vector<char>& s) {
        int start=0, end=s.size()-1;
        while(start<end)
        {
            
            swap(s[start++],s[end--]);
        }
    }
};

/*
class Solution {
public:
    
    //Using Recursion
    
    void reverse(vector<char>& s, int start , int end)
    {
        if(start>end)
            return ;
        swap(s[start++],s[end--]);
        return reverse(s, start, end);
    }
    void reverseString(vector<char>& s) {
        
        int start=0, end=s.size()-1;
        reverse(s, start, end);
        }
};
*/