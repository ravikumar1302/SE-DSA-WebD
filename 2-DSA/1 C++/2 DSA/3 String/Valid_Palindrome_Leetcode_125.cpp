/*
Valid_Palindrome_Leetcode_125

A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

    Example 1:
    Input: s = "A man, a plan, a canal: Panama"
    Output: true
    Explanation: "amanaplanacanalpanama" is a palindrome.
*/

class Solution
{
private:
    bool valid(char ch)
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
        {
            return 1;
        }

        return 0;
    }
    char tolower(char ch)
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            return ch;
        else
        {
            return (ch - 'A' + 'a');
        }
    }
    bool checkpalindrome(string a)
    {
        int s = 0;
        int e = a.length() - 1;
        while (s <= e)
        {
            if (a[s] != a[e])
                return 0;
            else
            {
                s++;
                e--;
            }
        }
        return 1;
    }

public:
    bool isPalindrome(string s)
    {
        string temp = "";
        for (int i = 0; i < s.length(); i++)
            if (valid(s[i]))
                temp.push_back(s[i]); // Enterning alphabets in temp

        for (int i = 0; i < temp.length(); i++)
            temp[i] = tolower(temp[i]); // Converting everyting to lower case

        return checkpalindrome(temp); // Checking palindrome
    }
};

// Same code as above, with alnum function used

class Solution
{
private:
    bool checkpalindrome(string a)
    {
        int s = 0;
        int e = a.length() - 1;
        while (s <= e)
        {
            if (a[s] != a[e])
                return 0;

            s++;
            e--;
        }
        return 1;
    }

public:
    bool isPalindrome(string s)
    {
        string temp = "";
        for (int i = 0; i < s.length(); i++)
            if (isalnum(s[i]))
                temp.push_back(s[i]);

        for (int i = 0; i < temp.length(); i++)
            temp[i] = tolower(temp[i]);

        return checkpalindrome(temp);
    }
};

// Method-3 : Using Recursion
class Solution
{
public:
    bool help(string &str, int n, int i)
    {
        if (i >= n / 2)
            return true;
        else if (str[i] != str[n - i - 1])
            return false;

        return help(str, n, i + 1);
    }

    bool isPalindrome(string s)
    {
        string temp = "";
        for (int i = 0; i < s.length(); i++)
            if (isalnum(s[i]))
                temp.push_back(s[i]);

        for (int i = 0; i < temp.length(); i++)
            temp[i] = tolower(temp[i]);

        int n = temp.length();
        return help(temp, n, 0); // Using recurssion
    }
};