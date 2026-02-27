/*
Reverse_the_String_Codestudio

You are given a string 'STR'. The string contains [a-z] [A-Z] [0-9] [special characters]. You have to find the reverse of the string.

    For example : If the given string is: STR = "abcde". You have to print the string "edcba"
*/


//Using Recursion

void reverse(string& s, int start , int end)
{
    if(start>end)
        return ;
    swap(s[start++],s[end--]);
    return reverse(s, start, end);
 }
string reverseString(string str)
{
    reverse(str, 0, str.size()-1);
    return str;
};


/* Run time errror is coming in 2/8 cases

    //Using Recursion - More optimized than earlier submission 

void reverse(string& s, int start)
{
    if(start>s.length()-1-start)
        return ;
    swap(s[start],s[s.length()-1-start]);
    start++;
    return reverse(s, start);
 }
string reverseString(string str)
{
   
    reverse(str, 0);
    return str;
};
*/