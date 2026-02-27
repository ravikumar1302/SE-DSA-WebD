/*
Permutation_in_String_Leetcode_567

Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
In other words, return true if one of s1's permutations is the substring of s2.
*/

class Solution {
    private:
    bool checkequal(int a[26], int b[26])
    {
        for(int i=0; i<26; i++)
        {
            if(a[i] != b[i])
                return 0; 
        }
        return 1;
    }
    public:
    bool checkInclusion(string s1, string s2) {
        int count1[26]={0};
        for(int i=0;i<s1.length();i++)  //Count the charactetr array in s1, s1 is small string
        {
            int index=s1[i]-'a';
            count1[index]++;
        }
        
        int i=0;
        int windowsize=s1.length();
        int count2[26]={0};
        
        while(i<windowsize && i<s2.length()) //counting for 1st window
        {
            int index=s2[i]-'a';
            count2[index]++;
            i++;
        }
        
        if(checkequal(count1,count2))
            return 1;
        
        //else check for remaining windows
        while(i<s2.length())       //Checking for remaining window
        {
            char newchar=s2[i];
            int index=s2[i]-'a';
            count2[index]++;
            
            char oldchar=s2[i-windowsize];
            index=oldchar-'a';
            count2[index]--;
            
            i++;
            
            if(checkequal(count1,count2))
                return 1;
        }
        return 0;
    }
};