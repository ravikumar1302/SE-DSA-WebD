/*
Check_if_strings_are_rotations_of_each_other_or_not_GFG
Rotate String Leetcode 796
Check If One String Is A Rotation Of Another String Codestudio

Given two strings s1 and s2. The task is to check if s2 is a rotated version of the string s1. The characters in the strings are in lowercase.

Example 1:
Input: geeksforgeeks, forgeeksgeeks
Output: 1
Explanation: s1 is geeksforgeeks, s2 is forgeeksgeeks. Clearly, s2 is a rotated version of s1 as s2 can be obtained by left-rotating s1 by 5 units. 

Expected Time Complexity: O(N).
Expected Space Complexity: O(N).

*/


// Brute force Approach : just left rotate s2 string one by one and compare it.
// Time : O(N^2)
 
bool areRotations(string s1,string s2)
    {
        // Your code here
        char temp;
        int n = s2.size();
        int n2 = s1.size();
        if(n != n2) 
            return false;
        
        int ln = 0;
        while(ln < n) {
            temp = s2[0];
            for(int i = 0; i+1 < n; i++) 
                s2[i] = s2[i+1];
            
            s2[n-1] = temp;
            ln++;
            if(s1 == s2)
                return true;
        }
        return false;
    }


// Approach 2 : Using concatenation of one string
// Time : O(logN), as find takes logN time

bool areRotations(string s1,string s2)
   {
       if(s1.length() != s2.length())
           return false;

       s1 = s1+s1;
       if(s1.find(s2) == -1)
            return false;
       
       return true;
   } 

